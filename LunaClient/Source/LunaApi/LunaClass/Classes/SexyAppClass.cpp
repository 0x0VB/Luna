#include "stdafx.h"
#include "LunaBase.h"
#include "SexyAppClass.h"
#include "PvZ/LawnApp.h"
#include "LunaApi/LunaUtil/LunaUtil.h"
#include "LunaApi/LunaStructs/Rect/Rect.h"

#include "UIContainerClass.h"
using namespace Luna::Class;
namespace
{
	class WindTitle : public Luna::Class::LunaField
	{
	public:
		virtual void __index(lua_State* L) override
		{
			lua_pushstring(L, LawnApp::GetApp()->Title);
		}
		virtual void __newindex(lua_State* L) override
		{
			auto Value = GetString(L, 3);
			AssertType(L, 3, "string", Name);
			auto App = LawnApp::GetApp();
			App->Title = Value;
			if (App->MainWindowHandle)
				SetWindowTextA(App->MainWindowHandle, Value.c_str());
		}
		DefNewField(WindTitle)
	};
	class WindBounds : public Luna::Class::LunaField
	{
	public:
		virtual void __index(lua_State* L) override
		{
			auto App = LawnApp::GetApp();
			if (App->MainWindowHandle == NULL)
			{ App->WindowBounds.Push(L); return; }

			tagRECT OutSource = {};
			LPRECT Out = &OutSource;
			GetWindowRect(App->MainWindowHandle, Out);
			IRect(Out).Push(L);
		}
		virtual void __newindex(lua_State* L) override
		{
			AssertType(L, 3, "Rect", Name);
			auto Value = GetRect(L, 3);
			auto App = LawnApp::GetApp();
			App->WindowBounds = Value;
			App->ScreenBounds = Value;
			if (App->MainWindowHandle)
				SetWindowPos(App->MainWindowHandle, NULL, Value.X, Value.Y, Value.W, Value.H, NULL);
		}
		DefNewField(WindBounds)
	};
}

Luna::Class::LunaClass* Luna::Class::LunaAppBase::Source = new LunaClass();
int Luna::Class::LunaAppBase::Init(lua_State* L)
{
	using namespace Fields;
	Source->AllowsInjection = true;
	Source->SetName("SexyApp");
	Source->AddSubClass("SexyAppBase");
	Source->Inherit(LunaBase::Source);

	WindTitle::New("WindowTitle", 0, Source);
	WindBounds::New("WindowBounds", 0, Source);

	IntField::New("Seed", 0x8, Source);
	StrField::New("RegisteryKey", 0x80, Source);
	DblField::New("MusicVolume", 0xD0, Source);
	DblField::New("SFXVolume", 0xD8, Source);
	BlnField::New("IsBeta", 0x11C, Source);
	BlnField::New("IsWindowed", 0x343, Source);
	BlnField::New("Initialized", 0x348, Source);
	IntField::New("TimeLoaded", 0x34C, Source);
	BlnField::New("InputDisabled", 0x368, Source);
	BlnField::New("TabletPC", 0x36A, Source);
	IntField::New("FrameTime", 0x454, Source);
	BlnField::New("IsDrawing", 0x458, Source);
	IntField::New("DrawCount", 0x480, Source);
	IntField::New("UpdateCount", 0x484, Source);
	IntField::New("UpdateState", 0x488, Source);
	IntField::New("UpdateDepth", 0x48C, Source);
	DblField::New("Speed", 0x490, Source);
	BlnField::New("Paused", 0x498, Source);
	BlnField::New("MouseIn", 0x4CC, Source);
	BlnField::New("Active", 0x4CE, Source);
	BlnField::New("Minimized", 0x4CF, Source);
	BlnField::New("HasFocus", 0x4D2, Source);
	BlnField::New("Loaded", 0x4FB, Source);
	BlnField::New("CtrlDown", 0x5AE, Source);
	BlnField::New("AltDown", 0x5AF, Source);
	BlnField::New("AllowAltEnter", 0x5B0, Source);

	UIObjectField::New("UIRoot", offsetof(Sexy::SexyAppBase, UIRoot), Source);
	// TODO: register class to the lua state?

	return 0;
}