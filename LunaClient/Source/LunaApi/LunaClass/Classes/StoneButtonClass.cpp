#include "stdafx.h"
#include "StoneButtonClass.h"

#include "LunaApi/LunaUtil/LunaUtil.h"
#include "LunaApi/LunaIO/LunaIO.h"

#include "PvZ/ButtonListener.h"
#include "PvZ/DialogButton.h"
#include "PvZ/UIElement.h"
#include "PvZ/UIRoot.h"
#include "PvZ/Font.h"
#include "Luna.h"

#include "LunaBase.h"
#include "UIElementClass.h"
#include "UIContainerClass.h"

using namespace Luna::Class;
using namespace Fields;

namespace
{
	int ResizeToFit(lua_State* L)
	{
		auto self = (LawnStoneButton*)AssertIsA(L, 1, "UIStoneButton")->GetBase();
		self->ResizeToFit();
		return 0;
	}
}

Sexy::ButtonListener* LunaStoneButton::LunaListener = new Sexy::ButtonListener();
LunaClass* LunaStoneButton::Source = new LunaClass();
int LunaStoneButton::Init(lua_State* L)
{
	Source->AllowsInjection = true;
	Source->SetName("UIStoneButton");
	Source->AddSubClass("BaseButton");
	Source->Inherit(LunaUIElement::Source);

	StrField::New("Text", 0x90, Source);
	Source->Methods["ResizeToFit"] = ResizeToFit;

	return 0;
}

int LunaStoneButton::Constructor(lua_State* L)
{
	auto Parent = AssertIsA(L, 2, "UIContainer", "Parent", true);
	auto Text = GetString(L, 3, "Luna!");
	auto self = LawnStoneButton::New(0, LunaListener, Text);
	
	CreateUIObject(L, self);
	self->ResizeToFit();

	if (Parent == NULL) return 1;
	auto Element = (Sexy::UIContainer*)Parent->GetBase();
	Element->AddChild(self);
	self->Parent = Element;
	self->ResizeToFit();

	return 1;
}