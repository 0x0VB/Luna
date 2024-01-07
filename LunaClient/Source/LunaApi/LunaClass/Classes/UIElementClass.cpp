#include "stdafx.h"
#include "UIElementClass.h"

#include "LunaApi/LunaStructs/Color/Color.h"
#include "LunaApi/LunaUtil/LunaUtil.h"
#include "LunaApi/LunaIO/LunaIO.h"

#include "PvZ/UIElement.h"
#include "PvZ/UIRoot.h"
#include "PvZ/DialogButton.h"
#include "Luna.h"

#include "LunaBase.h"
#include "UIContainerClass.h"
#include "StoneButtonClass.h"
#include "UIButtonClass.h"

using namespace Luna::Class;
using namespace Luna::Event;
using namespace Fields;

namespace
{
	int UI_GetColors(lua_State* L)
	{
		auto self = (Sexy::UIElement*)AssertIsA(L, 1, "UIElement")->GetBase();
		
		lua_newtable(L);
		auto Colors = self->Colors.Vector;
		unsigned int ColCount = Colors.size();
		for (int i = 0; i < ColCount; i++)
		{
			lua_pushinteger(L, i + 1);
			Colors[i].Push(L);
			lua_settable(L, -3);
		}
		return 1;
	}
	int UI_GetColor(lua_State* L)
	{
		auto self = (Sexy::UIElement*)AssertIsA(L, 1, "UIElement")->GetBase();
		auto Idx = GetInt(L, 2, 1);
		auto Colors = self->Colors.Vector;

		if (Colors.size() < Idx || Idx < 1)
			LunaIO::ThrowError(L, std::string("Invalid color index: ") + std::to_string(Idx));
		Colors[Idx - 1].Push(L);
		return 1;
	}
	int UI_SetColor(lua_State* L)
	{
		auto self = (Sexy::UIElement*)AssertIsA(L, 1, "UIElement")->GetBase();
		auto Idx = GetInt(L, 2, 1);
		auto Color = GetColor(L, 3, "Value");
		auto Colors = self->Colors.Vector;
		Colors[Idx] = Color;
		return 0;
	}
	// TODO: Implement these functions after implementing the lua wrapper for the Graphics class
	int UI_DrawText(lua_State* L)
	{

	}
	int UI_DrawCenteredText(lua_State* L)
	{
			
	}
	int UI_DrawWrappedText(lua_State* L)
	{

	}
	int UI_DrawDigitsFromStrip(lua_State* L)
	{

	}
}

namespace
{
	std::vector<DWORD> MouseDownEntries = { 0x539487 };
	LunaEventRef OnMouseDown;

	DWORD __stdcall MouseDownCaller(Sexy::UIElement* self, int X, int Y, int ClickCode)
	{
		lua_State* L = LUNA_STATE;
		int T = lua_gettop(L);
		bool DoCall = true;

		CreateUIObject(L, self);
		auto Proxy = (LunaInstance*)lua_touserdata(L, T + 1);
		if (Proxy->Associations[0] == 0) goto Exit;
		lua_getref(L, Proxy->Associations[0]);
		lua_pushvalue(L, T + 1);
		lua_pushinteger(L, X);
		lua_pushinteger(L, Y);
		switch (ClickCode)
		{
		case -2:
			lua_pushinteger(L, 2);
			lua_pushboolean(L, true);
			break;
		case -1:
			lua_pushinteger(L, 2);
			lua_pushboolean(L, false);
			break;
		case 1:
			lua_pushinteger(L, 1);
			lua_pushboolean(L, false);
			break;
		case 2:
			lua_pushinteger(L, 1);
			lua_pushboolean(L, true);
			break;
		default:
			lua_pushinteger(L, 3);
			lua_pushboolean(L, false);
			break;
		}

		if (lua_pcall(L, 5, 1, 0) != LUA_OK)
			LunaIO::Print(lua_tostring(L, -1), LunaIO::Error);
		else
			DoCall = lua_toboolean(L, -1);

	Exit:
		lua_settop(LUNA_STATE, T);
		if (DoCall)
			self->MouseDown(X, Y, ClickCode);

		return 0x53948E;
	}
	void __declspec(naked) MouseDownHandler()
	{
		__asm
		{
			push ebx
			push ecx
			push edx
			push esi
			call MouseDownCaller
			jmp eax
		}
	}
}

std::map<std::string, lua_CFunction> UIConst = {};
int UINew(lua_State* L)
{
	auto ClassName = GetString(L, 1, "EMPTY_CLASS");
	if (!UIConst.contains(ClassName))
		LunaIO::ThrowError(L, "Unable to create class of type " + ClassName + ".");
	return UIConst[ClassName](L);
}

LunaClass* LunaUIElement::Source = new LunaClass();
int LunaUIElement::Init(lua_State* L)
{
	UIConst["StoneButton"] = LunaStoneButton::Constructor;
	UIConst["UIButton"] = LunaUIButton::Constructor;

	Source->AllowsInjection = true;
	Source->SetName("UIElement");
	Source->Inherit(LunaUIContainer::Source);

	BlnField::New("Visible", 0x54, Source);
	BlnField::New("MouseVisible", 0x55, Source);
	BlnField::New("Disabled", 0x56, Source);
	BlnField::New("HasFocus", 0x57, Source);
	BlnField::New("IsDown", 0x58, Source);
	BlnField::New("Hovered", 0x59, Source);
	PadField::New("Padding", 0x6C, Source);
	BlnField::New("Clickable", 0x7C, Source);
	BlnField::New("WantsFocus", 0x7D, Source);
	UIObjectField::New("TabPrev", 0x80, Source);
	UIObjectField::New("TabNext", 0x84, Source);
	
	FunctionField::New("OnMouseDown", 0, Source);

	Source->Methods["GetColors"] = UI_GetColors;
	Source->Methods["GetColor"] = UI_GetColor;
	Source->Methods["SetColor"] = UI_SetColor;

	OnMouseDown = LunaEvent::New("OnMouseDown", MouseDownHandler, MouseDownEntries, true);

	lua_newtable(L);
	lua_pushstring(L, "New");
	lua_pushcclosure(L, UINew, "UI.New", 0);
	lua_settable(L, -3);
	lua_setglobal(L, "UI");

	return 0;
}