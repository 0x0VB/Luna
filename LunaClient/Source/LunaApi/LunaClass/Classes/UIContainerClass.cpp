#include "stdafx.h"
#include "UIContainerClass.h"

#include "LunaApi/LunaIO/LunaIO.h"
#include "LunaApi/LunaUtil/LunaUtil.h"
#include "PvZ/UIElement.h"
#include "Luna.h"

#include "LunaBase.h"
#include "UIRootClass.h"

using namespace Luna::Class;
using namespace Fields;

void CreateUIObject(lua_State* L, void* At)
{
	auto VTable = *(DWORD*)At;
	auto ClassDefined = UI_VTABLES.contains(VTable);
	auto Class = ClassDefined ? UI_VTABLES[VTable] : LunaUIContainer::Source;
	if (Luna::DebugMode && !ClassDefined)
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
		virtual void __index(lua_State* L) override
		{
			auto self = GetSelf(L);
			auto Base = GetBase(self);
			CreateUIObject(L, *(void**)Base);
		}
		virtual void __newindex(lua_State* L) override
		{
			auto Proxy = GetSelf(L);
			auto Value = GetUIObject(L, 3, "Parent", true);
			auto self = (Sexy::UIElement*)Proxy->GetBase();
			auto Parent = (Sexy::UIContainer*)(Value->GetBase());

			if (self->Parent != NULL)
				self->Parent->RemoveChild(self);
			if (self->Parent == Parent) return;
			if (Parent != NULL)
				Parent->AddChild(self);
			else if (self->Parent != NULL)
			{
				self->Parent->RemoveChild(self);
			}
		}
		DefNewField(ParentField)
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
		LunaBase::Flush(L);
		return 0;
	}
}

LunaClass* LunaUIContainer::Source = new LunaClass();
int LunaUIContainer::Init(lua_State* L)
{
	UI_VTABLES = std::map<DWORD, LunaClass*>();
	UI_VTABLES[0x66F934] = Source;// UIContainer
	UI_VTABLES[0x66F794] = NULL;// UIElement
	UI_VTABLES[0x66F8B4] = LunaUIRoot::Source;// UIRoot

	Source->AllowsInjection = true;
	Source->SetName("UIContainer");
	Source->AddSubClass("UIBase");
	Source->Inherit(LunaBase::Source);

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

	return 0;
}