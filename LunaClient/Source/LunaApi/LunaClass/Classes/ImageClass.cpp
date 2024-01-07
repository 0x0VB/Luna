#include "stdafx.h"
#include "ImageClass.h"

#include "LunaApi/LunaUtil/LunaUtil.h"
#include "LunaApi/LunaIO/LunaIO.h"
#include "Luna.h"

#include "PvZ/LawnApp.h"
#include "PvZ/Image.h"

#include "LunaBase.h"

using namespace Luna::Class;
using namespace Fields;

std::map<DWORD, LunaClass*> IMAGE_VTABLES = {};
void CreateLunaImage(lua_State* L, void* At)
{
	auto VTable = *(DWORD*)At;
	auto ClassDefined = IMAGE_VTABLES.contains(VTable);
	auto Class = ClassDefined ? IMAGE_VTABLES[VTable] : LunaImage::Source;
	if (VTable == NULL) { lua_pushnil(L); return; }
	Class = (Class != NULL) ? Class : LunaImage::Source;
	if ((Luna::DebugMode && !ClassDefined) || Class == NULL)
	{
		IMAGE_VTABLES[VTable] = Class;
		LunaIO::Print("Undefined Image Class at [", LunaIO::Warning, false);
		std::cout << (void*)VTable << "], cast to a generic Image.\n";
	}
	Class->New(L, At);
}

Sexy::Image* DefaultImage = NULL;
LunaInstance* GetLunaImage(lua_State* L, int Index, std::string ParamName, bool AcceptNil, bool Substitute)
{
	if (AcceptNil && (lua_isnil(L, Index) || lua_gettop(L) < Index))
	{
		if (!Substitute)
			return NULL;
		else if (DefaultImage == NULL)
			DefaultImage = Luna::App->GetImage("images/LunaLogo", true);
		CreateLunaImage(L, DefaultImage);
		auto self = (LunaInstance*)lua_touserdata(L, -1);
		lua_pop(L, 1);
		return self;
	}
	ParamName = (ParamName == "NO_PARAM_NAME") ? std::string("arg#") + std::to_string(Index) : ParamName;
	auto self = AssertIsA(L, Index, "Image", ParamName);
	return self;
}

void ImageField::__index(lua_State* L)
{
	auto self = GetBase(GetSelf(L));
	CreateLunaImage(L, self);
}
void ImageField::__newindex(lua_State* L)
{
	CheckReadOnly(L);
	auto self = GetBase(GetSelf(L));
	auto Proxy = GetLunaImage(L, 3, Name, true);
	auto Image = (Proxy == NULL) ? NULL : Proxy->GetBase();
	*(void**)self = Image;
}

namespace
{
	int LoadImage(lua_State* L)
	{
		AssertType(L, 2, "string", "ImagePath");
		auto ImageName = GetString(L, 2);
		bool PackedMod = false;
		auto App = LawnApp::GetApp();
		std::cout << App << "\n";

		// TODO: Add packed mod handling
		auto Image = App->GetImage(ImageName, false);
		CreateLunaImage(L, Image);
		return 1;
	}
}

LunaClass* LunaImage::Source = new LunaClass();
LunaClass* LunaMemImage::Source = new LunaClass();
LunaClass* LunaDDImage::Source = new LunaClass();

int LunaImage::Init(lua_State* L)
{
	IMAGE_VTABLES[0x67245C] = Source;
	IMAGE_VTABLES[0x6724A4] = LunaMemImage::Source;
	IMAGE_VTABLES[0x67238C] = LunaDDImage::Source;

	Source->AllowsInjection = true;
	Source->SetName("Image");
	Source->Inherit(LunaBase::Source);

	StrField::New("Name", 0xC, Source);
	IV2Field::New("Size", 0x24, Source, true);
	IntField::New("RowNum", 0x2C, Source);
	IntField::New("ColNum", 0x30, Source);

	lua_getglobal(L, "Luna");
	lua_pushstring(L, "LoadImage");
	lua_pushcclosure(L, LoadImage, "LoadImage", 0);
	lua_settable(L, -3);
	lua_pop(L, 1);

	return 0;
}

int LunaMemImage::Init(lua_State* L)
{
	Source->AllowsInjection = true;
	Source->SetName("MemImage");
	Source->Inherit(LunaImage::Source);

	// Setup Methods

	return 0;
}

int LunaDDImage::Init(lua_State* L)
{
	Source->AllowsInjection = true;
	Source->SetName("DDImage");
	Source->Inherit(LunaMemImage::Source);

	// Setup Methods

	return 0;
}