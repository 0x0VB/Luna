#include "stdafx.h"
#include "UIRootClass.h"

#include "LunaApi/LunaIO/LunaIO.h"
#include "LunaApi/LunaUtil/LunaUtil.h"
#include "PvZ/UIElement.h"
#include "Luna.h"

#include "LunaBase.h"
#include "UIContainerClass.h"
#include "PvZ/UIRoot.h"

using namespace Luna::Class;
using namespace Fields;

namespace
{
	int IsMouseDown(lua_State* L)
	{
		auto self = (Sexy::UIRoot*)AssertIsA(L, 1, "UIRoot")->GetBase();
		auto Button = GetInt(L, 2, 1);
		if (Button < 1 || Button > 3)
			LunaIO::ThrowError(L, "Expected a MouseButton, got " + LunaUtil::Type(L, 2));
		lua_pushboolean(L, self->ActualDownButtons & (1 << (Button - 1)));
		return 1;
	}
	int IsKeyDown(lua_State* L)
	{
		auto self = (Sexy::UIRoot*)AssertIsA(L, 1, "UIRoot")->GetBase();
		auto Key = (int)lua_tonumber(L, 2);
		if (!lua_isnumber(L, 2) || Key < 0 || Key >= 255)
			LunaIO::ThrowError(L, "Expected a KeyCode, got " + LunaUtil::Type(L, 2));
		lua_pushboolean(L, self->KeysDown[(BYTE)Key]);
		return 1;
	}
}

LunaClass* LunaUIRoot::Source = new LunaClass();
int LunaUIRoot::Init(lua_State* L)
{
	Source->AllowsInjection = true;
	Source->SetName("UIRoot");
	Source->AddSubClass("UIBase");
	Source->AddSubClass("UIManager");
	Source->Inherit(LunaUIContainer::Source);

	UIObjectField::New("LastPressedElement", 0x8C, Source);
	UIObjectField::New("FocusedElement", 0x88, Source);
	UIObjectField::New("HoveredElement", 0x90, Source);
	BlnField::New("HasFocus", 0x84, Source);
	BlnField::New("MouseIn", 0xDC, Source);
	IV2Field::New("MousePosition", 0xE0, Source);
	IntField::New("MouseX", 0xE0, Source);
	IntField::New("MouseY", 0xE4, Source);

	Source->Methods["IsMouseDown"] = IsMouseDown;
	Source->Methods["IsKeyDown"] = IsKeyDown;

	return 0;
}