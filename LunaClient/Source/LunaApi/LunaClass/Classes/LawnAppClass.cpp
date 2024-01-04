#include "stdafx.h"
#include "LawnAppClass.h"

#include "LunaBase.h"
#include "SexyAppClass.h"

#include "LunaApi/LunaUtil/LunaUtil.h"
#include "Luna.h"

#include "PvZ/Graphics.h"


using Luna::Event::LunaEvent;

namespace
{
	std::vector<DWORD> StoneButtonEntries = { 0x447B00 };
	LunaEvent* StoneButtonDraw;

	std::vector<DWORD> UpdateEntries = { 0x539140 };
	LunaEvent* OnUpdate;

	std::vector<DWORD> FinalDrawEntries = { 0x5390DC };
	LunaEvent* OnFinalDraw;
}

#include "LunaApi/LunaStructs/Vector2/Vector2.h"
namespace // Event Bodies
{
	DWORD __stdcall UpdateCaller()
	{
		OnUpdate->Call(LUNA_STATE, 0);
		return 0x539148;
	}

	DWORD __stdcall FinalDrawCaller(Sexy::Graphics* G)
	{

		return 0x5390E1;
	}
}

namespace // Methods
{
	int MsgBox(lua_State* L)
	{
		AssertType(L, 2, "string", "Message");
		Luna::App->MsgBox(GetString(L, 2, "Luna!"), GetString(L, 3, "Luna!"), 0);
		return 0;
	}

	void SetupEvents()
	{
		//StoneButtonDraw = LunaEvent::New("OnStoneButtonDraw", StoneButtonDrawHandler, StoneButtonEntries, true);
		//OnFinalDraw = LunaEvent::New("OnFinalDraw", FinalDrawHandler, FinalDrawEntries, true);
		OnUpdate = LunaEvent::New("OnUpdate", UpdateHandler, UpdateEntries, false);
	}
}

int Luna::Class::LunaApp::LunaInstanceRef = 0;
Luna::Class::LunaClass* Luna::Class::LunaApp::Source = new LunaClass();
int Luna::Class::LunaApp::Init(lua_State* L)
{
	Source->AllowsInjection = true;
	Source->SetName("LawnApp");
	Source->Inherit(Luna::Class::LunaAppBase::Source);

	using namespace Luna::Class::Fields;
	BlnField::New("ZombiesLoaded", 0x800, Source);
	BlnField::New("NewUser", 0x801, Source);
	IntField::New("GamePlayed", 0x804, Source);
	BlnField::New("EasyPlantingCheat", 0x814, Source);
	BlnField::New("CloseRequest", 0x834, Source);
	IntField::New("Age", 0x838, Source);

	BlnField::New("MustacheMode", 0x8B8, Source);
	BlnField::New("SuperMowerMode", 0x8B9, Source);
	BlnField::New("FutureMode", 0x8BA, Source);
	BlnField::New("PinataMode", 0x8BB, Source);
	BlnField::New("DanceMode", 0x8BC, Source);
	BlnField::New("DaisyMode", 0x8BD, Source);
	BlnField::New("SukhbirMode", 0x8BE, Source);

	SetupEvents();
	EventField::New("OnUpdate", OnUpdate, Source);

	Source->Methods["MessageBox"] = MsgBox;

	Source->New(L, LawnApp::GetApp());
	LunaInstanceRef = lua_ref(L, -1);
	lua_pop(L, 1);

	return 0;
}