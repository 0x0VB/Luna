#include "stdafx.h"
#include "UIContainerClass.h"

#include "LunaApi/LunaIO/LunaIO.h"
#include "LunaApi/LunaUtil/LunaUtil.h"
#include "PvZ/UIElement.h"
#include "PvZ/UIRoot.h"
#include "Luna.h"

#include "LunaBase.h"
#include "UIRootClass.h"
#include "UIElementClass.h"
#include "UIButtonClass.h"
#include "StoneButtonClass.h"

using namespace Luna::Class;
using namespace Fields;

void CreateUIObject(lua_State* L, void* At)
{
	auto VTable = *(DWORD*)At;
	auto ClassDefined = UI_VTABLES.contains(VTable);
	auto Class = ClassDefined ? UI_VTABLES[VTable] : LunaUIElement::Source;
	if (VTable == NULL) { lua_pushnil(L); return; }
	Class = (Class != NULL) ? Class : LunaUIElement::Source;
	if ((Luna::DebugMode && !ClassDefined) || Class == NULL)
	{
		UI_VTABLES[VTable] = Class;
		LunaIO::Print("Undefined UI Class at [", LunaIO::Warning, false);
		std::cout << (void*)VTable << "], cast to a generic UIElement.\n";
	}
	Class->New(L, At);
}
LunaInstance* GetUIObject(lua_State* L, int Index, std::string ParamName, bool AcceptNil)
{
	if (AcceptNil && lua_isnil(L, Index)) return NULL;
	ParamName = (ParamName == "NO_PARAM_NAME") ? std::string("arg#") + std::to_string(Index) : ParamName;
	auto self = AssertIsA(L, Index, "UIBase", ParamName);
	return self;
}

void UIObjectField::__index(lua_State* L)
{
	auto self = GetSelf(L);
	auto Base = GetBase(self);
	if (Base == NULL)
		lua_pushnil(L);
	else
		CreateUIObject(L, *(void**)Base);
}
void UIObjectField::__newindex(lua_State* L)
{
	auto self = GetSelf(L);
	auto Base = GetBase(self);
	auto Value = GetUIObject(L, 3, Name);
	*(void**)Base = Value->Class->GetBase(Value);
}

namespace
{
	class ParentField : public UIObjectField
	{
	public:
		virtual void __newindex(lua_State* L) override
		{
			auto Proxy = GetSelf(L);
			auto Value = GetUIObject(L, 3, "Parent", true);
			auto self = (Sexy::UIElement*)Proxy->GetBase();
			auto Parent = (Sexy::UIContainer*)(Value->GetBase());

			if (self->Parent == Parent) return;
			if (self->Parent != NULL)
				self->Parent->RemoveChild(self);

			if (Parent == NULL)
				self->Parent = NULL;
			else
				Parent->AddChild(self);
		}
		DefNewField(ParentField)
	};
	class AbsolutePositionField : public Luna::Class::LunaField
	{
	public:
		virtual void __index(lua_State* L) override
		{
			auto self = GetSelf(L);
			auto Base = (Sexy::UIElement*)self->GetBase();
			IVector2 AbsPos;
			Base->GetAbsPos(&AbsPos);
			AbsPos.Push(L);
		}
		DefNewField(AbsolutePositionField);
	};

	int GetChildren(lua_State* L)
	{
		auto self = GetUIObject(L, 1, "self");
		auto Element = (Sexy::UIContainer*)self->Class->GetBase(self);
		int T = lua_gettop(L);

		lua_newtable(L);// T + 1
		int Count = 0;
		for (auto const& Child : Element->Children.List)
		{
			Count++;
			lua_pushinteger(L, Count);
			CreateUIObject(L, Child);
			lua_settable(L, T + 1);
		}
		return 1;
	}
	int Destroy(lua_State* L)
	{
		auto self = GetUIObject(L, 1, "self");
		auto DeleteChildren = lua_toboolean(L, 2);
		auto Element = (Sexy::UIContainer*)self->Class->GetBase(self);
		if (DeleteChildren) Element->ClearChildren(true, true);
		if (Element->Parent != NULL) Element->Parent->RemoveChild((Sexy::UIElement*)Element);
		Element->~UIContainer();
		return 0;
	}
	int GetBounds(lua_State* L)
	{
		auto self = GetUIObject(L, 1, "self");
		auto Element = (Sexy::UIContainer*)self->GetBase();
		IRect Out;
		Element->GetRect(&Out);
		Out.Push(L);
		return 1;
	}
	int Intersects(lua_State* L)
	{
		auto self = GetUIObject(L, 1, "self");
		auto Element = (Sexy::UIContainer*)self->GetBase();
		auto Other = (Sexy::UIContainer*)GetUIObject(L, 2, "Other")->GetBase();
		lua_pushboolean(L, Element->Intersects(Other));
		return 1;
	}
	int HasChild(lua_State* L)
	{
		auto self = GetUIObject(L, 1, "self");
		auto Element = (Sexy::UIContainer*)self->GetBase();
		auto Child = (Sexy::UIElement*)GetUIObject(L, 2, "Other")->GetBase();
		lua_pushboolean(L, Element->HasChild(Child));
		return 1;
	}
	int IsBelow(lua_State* L)
	{
		auto self = (Sexy::UIElement*)GetUIObject(L, 1, "self")->GetBase();
		auto Other = (Sexy::UIElement*)GetUIObject(L, 2, "Other")->GetBase();
		if (self->Parent != Other->Parent)
			LunaIO::ThrowError(L, "IsBelow can only be used if the 2 UIElements share the same parent.");
		else if (self->Parent == NULL)
			LunaIO::ThrowError(L, "IsBelow cannot be used on UIElements with a nil parent.");
		else
			lua_pushboolean(L, self->Parent->IsBelow(self, Other));
		return 1;
	}
	int BringToFront(lua_State* L)
	{
		auto self = (Sexy::UIElement*)GetUIObject(L, 1, "self")->GetBase();
		if (self->Parent == NULL)
			LunaIO::ThrowError(L, "BringToFront cannot be used on UIElements with a nil parent.");
		else
			self->Parent->BringToFront(self);
		return 0;
	}
	int BringToBack(lua_State* L)
	{
		auto self = (Sexy::UIElement*)GetUIObject(L, 1, "self")->GetBase();
		if (self->Parent == NULL)
			LunaIO::ThrowError(L, "BringToBack cannot be used on UIElements with a nil parent.");
		else
			self->Parent->BringToBack(self);
		return 0;
	}
	int PutInFront(lua_State* L)
	{
		auto self = (Sexy::UIElement*)GetUIObject(L, 1, "self")->GetBase();
		auto Other = (Sexy::UIElement*)GetUIObject(L, 2, "Other")->GetBase();

		if (self->Parent == NULL)
			LunaIO::ThrowError(L, "PutInFront cannot be used on UIElements with a nil parent.");
		else if (self->Parent != Other->Parent)
			LunaIO::ThrowError(L, "PutInFront can only be used on UIElements that share the same parent.");
		else
			self->Parent->PutInFront(self, Other);
		return 0;
	}
	int PutBehind(lua_State* L)
	{
		auto self = (Sexy::UIElement*)GetUIObject(L, 1, "self")->GetBase();
		auto Other = (Sexy::UIElement*)GetUIObject(L, 2, "Other")->GetBase();

		if (self->Parent == NULL)
			LunaIO::ThrowError(L, "PutBehind cannot be used on UIElements with a nil parent.");
		else if (self->Parent != Other->Parent)
			LunaIO::ThrowError(L, "PutBehind can only be used on UIElements that share the same parent.");
		else
			self->Parent->PutBehind(self, Other);
		return 0;
	}
	int IsMouseOn(lua_State* L)
	{
		auto self = (Sexy::UIElement*)GetUIObject(L, 1, "self")->GetBase();
		auto App = LawnApp::GetApp();
		auto Root = App->UIRoot;
		if (!Root->MouseIn)
		{
			lua_pushboolean(L, false);
			return 1;
		}

		IRect Bounds;
		self->GetRect(&Bounds);
		lua_pushboolean(L, Bounds.Contains(Root->LastMousePos));
		return 1;
	}
	int IsMouseDown(lua_State* L)
	{
		auto self = (Sexy::UIElement*)GetUIObject(L, 1, "self")->GetBase();
		auto Button = GetInt(L, 2, 1);
		if (Button < 1 || Button > 3)
			LunaIO::ThrowError(L, "Expected a MouseButton, got " + LunaUtil::Type(L, 2));
		Button = 1 << (Button - 1);

		auto App = LawnApp::GetApp();
		auto Root = App->UIRoot;
		if (!Root->MouseIn)
		{
			lua_pushboolean(L, false);
			return 1;
		}

		IRect Bounds;
		self->GetRect(&Bounds);
		bool IsDown = Root->ActualDownButtons & Button;
		bool IsOn = Bounds.Contains(Root->LastMousePos);
		lua_pushboolean(L, IsOn && IsDown);
		return 1;
	}
}

LunaClass* LunaUIContainer::Source = new LunaClass();
int LunaUIContainer::Init(lua_State* L)
{
	UI_VTABLES = std::map<DWORD, LunaClass*>();
	UI_VTABLES[0x66F934] = Source;// UIContainer
	UI_VTABLES[0x66F794] = LunaUIContainer::Source;// UIContainer
	UI_VTABLES[0x66F8B4] = LunaUIRoot::Source;// UIRoot
	UI_VTABLES[0x658838] = LunaStoneButton::Source;// StoneButton
	UI_VTABLES[0x66DD90] = NULL;// LoadingScreen
	UI_VTABLES[0x67000C] = NULL;// Hyperlink
	UI_VTABLES[0x658710] = LunaUIButton::Source;// LawnButton (Fix this when you add LawnButton)
	UI_VTABLES[0x6555C0] = NULL;// AlmanacDialog
	UI_VTABLES[0x66FB2C] = LunaUIButton::Source;// UIButton
	UI_VTABLES[0x656CA8] = NULL;// Lawn
	UI_VTABLES[0x67026C] = NULL;// CheckBox

	Source->AllowsInjection = true;
	Source->SetName("UIContainer");
	Source->AddSubClass("UIBase");
	Source->Inherit(LunaBase::Source);

	AbsolutePositionField::New("AbsolutePosition", 0x0, Source);
	ParentField::New("Parent", 0x14, Source);
	IntField::New("Age", 0x28, Source);
	BlnField::New("Dirty", 0x2C, Source);

	RctField::New("Bounds", 0x30, Source);
	IV2Field::New("Position", 0x30, Source);
	IV2Field::New("Size", 0x38, Source);
	IntField::New("X", 0x30, Source);
	IntField::New("Y", 0x34, Source);
	IntField::New("W", 0x38, Source);
	IntField::New("H", 0x3C, Source);
	BlnField::New("Clip", 0x41, Source);

	Source->Methods["Destroy"] = Destroy;
	Source->Methods["GetChildren"] = GetChildren;
	Source->Methods["GetBounds"] = GetBounds;
	Source->Methods["Intersects"] = Intersects;
	Source->Methods["HasChild"] = HasChild;
	Source->Methods["IsBelow"] = IsBelow;
	Source->Methods["IsBehind"] = IsBelow;
	Source->Methods["BringToFront"] = BringToFront;
	Source->Methods["BringToBack"] = BringToBack;
	Source->Methods["PutInFront"] = PutInFront;
	Source->Methods["PutBehind"] = PutBehind;
	Source->Methods["IsMouseOn"] = IsMouseOn;
	Source->Methods["IsMouseDown"] = IsMouseDown;

	return 0;
}