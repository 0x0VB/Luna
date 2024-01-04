#include "stdafx.h"
#include "LunaClass.h"

#include "LunaApi/LunaUtil/LunaUtil.h"
#include "LunaApi/LunaStructs/LunaStructs.h"
#include "LunaApi/LunaIO/LunaIO.h"
#include "Luna.h"


using namespace Luna::Class;

namespace Luna::Class
{
	std::map<void*, bool> CLASS_VALIDATE = {};
	CONST SIZE_T MAX_FIELD_CAPACITY = 1000;
	SIZE_T FIELDS_USED = 0;
	LunaField* FIELDS = nullptr;
}

#pragma region LunaClass
void LunaClass::SetName(const char* NewName)
{
	int Length = strlen(NewName);
	memcpy(Name, NewName, Length);
	Name[Length] = 0;
	AddSubClass(NewName);
}
void LunaClass::AddSubClass(LunaClass* SubClass) { SubClasses[std::string(SubClass->Name)] = SubClass; }
void LunaClass::AddSubClass(const char* ClassName) { SubClasses[std::string(ClassName)] = NULL; }
void LunaClass::__tostring(lua_State* L) { lua_pushstring(L, Name); }
int LunaClass::__call(lua_State* L) { LunaIO::ThrowError(L, std::string("Unable to call a ") + Name + "."); return 0; }
bool LunaClass::IsA(std::string SubClass) { return SubClasses.contains(SubClass); }
void LunaClass::Inherit(LunaClass* Other)
{
	for (const auto& [K, V] : Other->SubClasses) { SubClasses[K] = V; }
	for (const auto& [K, V] : Other->Fields)
	{
		if (Fields.contains(K)) continue;
		Fields[K] = V;
	}

	for (const auto& [K, V] : Other->Methods)
	{
		if (Methods.contains(K)) continue;
		Methods[K] = V;
	}

}
void LunaClass::New(lua_State* L, void* Param)
{
	int T = lua_gettop(L);
	LunaUtil::Local(L, "ClassRef");
	lua_pushlightuserdata(L, Param);
	lua_gettable(L, -2);
	if (!lua_isnil(L, -1))
	{
		auto self = (LunaInstance*)lua_touserdata(L, -1);
		self->Class = this;
		lua_replace(L, T + 1);
		lua_settop(L, T + 1);
		return;
	}
	lua_settop(L, T);

	auto self = (LunaInstance*)lua_newuserdata(L, sizeof(LunaInstance));
	self->Base = Param;
	self->Class = this;

	LunaUtil::Local(L, "ClassRef");

	lua_pushlightuserdata(L, self);
	lua_pushvalue(L, T + 1);
	lua_settable(L, T + 2);

	lua_pushlightuserdata(L, Param);
	lua_pushvalue(L, T + 1);
	lua_settable(L, T + 2);
	lua_settop(L, T + 1);

	LunaUtil::Local(L, "ClassMeta");
	lua_setmetatable(L, T + 1);
	CLASS_VALIDATE[self] = true;

	if (!AllowsInjection)
		return;

	LunaUtil::Local(L, "Injected");
	lua_pushvalue(L, T + 1);
	lua_newtable(L);
	lua_settable(L, -3);
	lua_pop(L, 1);
}
void LunaClass::PushInjected(lua_State* L)
{
	LunaUtil::Local(L, "Injected");
	lua_pushvalue(L, 1);
	lua_gettable(L, -2);
	lua_replace(L, -2);
}
void LunaClass::GetInjected(lua_State* L)
{
	PushInjected(L);
	lua_pushvalue(L, 2);
	lua_gettable(L, -2);
	lua_replace(L, -2);
}
void LunaClass::Inject(lua_State* L)
{
	int T = lua_gettop(L);
	PushInjected(L);
	lua_pushvalue(L, 2);
	lua_pushvalue(L, 3);
	lua_settable(L, -3);
	lua_settop(L, T);
}
#pragma endregion

#pragma region LunaField
void LunaField::__newindex(lua_State* L) { LunaIO::ThrowError(L, std::string(Name) + " is read-only."); }
void LunaField::SetName(const char* NewName)
{
	int Length = strlen(NewName);
	memcpy(Name, NewName, Length);
	Name[Length] = 0;
}
void LunaField::AddToClass(LunaClass* Class) { Class->Fields[Name] = this; }
#pragma endregion

#pragma region MetaMethods
int Luna::Class::__type(lua_State* L)
{
	auto self = GetAndAssert(L);
	lua_pushstring(L, self->Class->Name);
	return 1;
}

int Luna::Class::__call(lua_State* L)
{
	auto self = GetAndAssert(L);
	if (self->Base == NULL) LunaIO::ThrowError(L, "This object has been destroyed.");
	return self->Class->__call(L);
}

int Luna::Class::__index(lua_State* L)
{
	auto self = GetAndAssert(L);

	if (!lua_isstring(L, 2))
		LunaIO::ThrowError(L, "Expected a string field, got " + LunaUtil::Type(L, 2));

	auto Field = GetString(L, 2);
	auto Class = self->Class;

	if (Field == "Destroyed")
	{
		if (!self->Base)
			lua_pushboolean(L, true);
		else
			lua_pushboolean(L, false);
	}
	// Get Method
	else if (Class->Methods.contains(Field))
		lua_pushcclosure(L, Class->Methods[Field], Field.c_str(), 0);
	// Get Field
	else if (Class->Fields.contains(Field))
	{
		Class->Fields[Field]->__index(L);
	}
		
	// Check if Field Injection is allowed
	else if (!Class->AllowsInjection)
		LunaIO::ThrowError(L, Field + " is not a valid member of " + Class->Name);
	// Get Injected Field
	else
		Class->GetInjected(L);
	return 1;
}

int Luna::Class::__newindex(lua_State* L)
{
	auto self = GetAndAssert(L);
	auto Field = GetString(L, 2);
	auto Class = self->Class;

	if (self->Base == NULL) LunaIO::ThrowError(L, "This object has been destroyed.");
	else if (!lua_isstring(L, 2)) LunaIO::ThrowError(L, "Expected a string field, got " + LunaUtil::Type(L, 2));// Only string fields allowed
	else if (Class->Methods.contains(Field)) LunaIO::ThrowError(L, Field + " is read-only.");// Error: Methods are read-only.
	else if (Class->Fields.contains(Field)) Class->Fields[Field]->__newindex(L);// Set Field
	else if (!Class->AllowsInjection) LunaIO::ThrowError(L, Field + " is not a valid member of " + Class->Name);// Check Injection
	else Class->Inject(L);// Inject a new field
	return 0;
}

int Luna::Class::__tostring(lua_State* L)
{
	auto self = GetAndAssert(L);
	if (self->Base == NULL) lua_pushstring(L, "[DELETED_OBJECT]");
	else self->Class->__tostring(L);
	return 1;
}

int Luna::Class::__gc(lua_State* L)
{
	auto self = GetSelf(L);
	CLASS_VALIDATE.erase(self);
	return 0;
}
#pragma endregion

#pragma region LunaFields
void Luna::Class::Fields::BytField::__index(lua_State* L)
{
	FBase(BYTE);
	lua_pushnumber(L, *Base);
}
void Luna::Class::Fields::BytField::__newindex(lua_State* L)
{
	FBase(BYTE);
	auto Value = GetInt(L, 3, -1);
	if (Value > 255 || Value < 0) LunaIO::ThrowError(L, std::string(Name) + " can only be a number between 0-255, got " + LunaUtil::Type(L, 3));
	*Base = Value;
}

void Luna::Class::Fields::BlnField::__index(lua_State* L)
{
	FBase(bool);
	lua_pushboolean(L, *Base);
}
void Luna::Class::Fields::BlnField::__newindex(lua_State* L)
{
	FBase(bool);
	AssertType(L, 3, "boolean", Name);
	*Base = (bool)lua_toboolean(L, 3);
}

void Luna::Class::Fields::IntField::__index(lua_State* L)
{
	FBase(int);
	lua_pushinteger(L, *Base);
}
void Luna::Class::Fields::IntField::__newindex(lua_State* L)
{
	FBase(int);
	if (!lua_isnumber(L, 3)) LunaIO::ThrowError(L, std::string("Expected an integer for ") + Name + ", got " + LunaUtil::Type(L, 3));
	*Base = (int)lua_tonumber(L, 3);
}

void Luna::Class::Fields::DblField::__index(lua_State* L)
{
	FBase(double);
	lua_pushnumber(L, *Base);
}
void Luna::Class::Fields::DblField::__newindex(lua_State* L)
{
	FBase(double);
	if (!lua_isnumber(L, 3)) LunaIO::ThrowError(L, std::string("Expected a number for ") + Name + ", got " + LunaUtil::Type(L, 3));
	*Base = (double)lua_tonumber(L, 3);
}

void Luna::Class::Fields::FltField::__index(lua_State* L)
{
	FBase(float);
	lua_pushnumber(L, *Base);
}
void Luna::Class::Fields::FltField::__newindex(lua_State* L)
{
	FBase(float);
	if (!lua_isnumber(L, 3)) LunaIO::ThrowError(L, std::string("Expected a number for ") + Name + ", got " + LunaUtil::Type(L, 3));
	*Base = (float)lua_tonumber(L, 3);
}

void Luna::Class::Fields::StrField::__index(lua_State* L)
{
	FBase(std::string);
	lua_pushstring(L, Base->c_str());
}
void Luna::Class::Fields::StrField::__newindex(lua_State* L)
{
	FBase(std::string);
	AssertType(L, 3, "string", std::string(Name));
	Base->assign(lua_tostring(L, 3));
}

void Luna::Class::Fields::RctField::__index(lua_State* L)
{
	FBase(IRect);
	Base->Push(L);
}
void  Luna::Class::Fields::RctField::__newindex(lua_State* L)
{
	FBase(IRect);
	AssertType(L, 3, "Rect", Name);
	*Base = GetRect(L, 3);
}

void Luna::Class::Fields::IV2Field::__index(lua_State* L)
{
	FBase(IVector2);
	Base->Push(L);
}
void Luna::Class::Fields::IV2Field::__newindex(lua_State* L)
{
	FBase(IVector2);
	AssertType(L, 3, "Vector2", Name);
	*Base = (IVector2)GetVector2(L, 3);
}

void Luna::Class::Fields::FV2Field::__index(lua_State* L)
{
	FBase(FVector2);
	Base->Push(L);
}
void Luna::Class::Fields::FV2Field::__newindex(lua_State* L)
{
	FBase(FVector2);
	AssertType(L, 3, "Vector2", Name);
	*Base = (FVector2)GetVector2(L, 3);
}

void Luna::Class::Fields::FV3Field::__index(lua_State* L)
{
	FBase(FVector3);
	Base->Push(L);
}
void Luna::Class::Fields::FV3Field::__newindex(lua_State* L)
{
	FBase(FVector3);
	AssertType(L, 3, "Vector3", Name);
	*Base = GetVector3(L, 3);
}

void Luna::Class::Fields::ColField::__index(lua_State* L)
{
	FBase(Color);
	Base->Push(L);
}
void Luna::Class::Fields::ColField::__newindex(lua_State* L)
{
	FBase(Color);
	AssertType(L, 3, "Color", Name);
	*Base = GetColor(L, 3);
}

void Luna::Class::Fields::PadField::__index(lua_State* L)
{
	FBase(Pad);
	Base->Push(L);
}
void Luna::Class::Fields::PadField::__newindex(lua_State* L)
{
	FBase(Pad);
	AssertType(L, 3, "Pad", Name);
	*Base = GetPad(L, 3);
}

void Luna::Class::Fields::EventField::__index(lua_State* L)
{
	lua_getref(L, Offset);
}
Luna::Class::Fields::EventField* Luna::Class::Fields::EventField::New(const char* Name, Luna::Event::LunaEvent* Event, LunaClass* Class)
{
	return LunaField::New<Luna::Class::Fields::EventField>(Name, (DWORD)Event->EventRef, Class);
}
#pragma endregion

LunaInstance* Luna::Class::GetAndAssert(lua_State* L, int Index)
{
	void* self = lua_touserdata(L, Index);
	if (!lua_isuserdata(L, Index))
		LunaIO::ThrowError(L, "Unable to get self. This object may have been destroyed.");
	if (CLASS_VALIDATE.contains(self))
		return (LunaInstance*)self;
	LunaIO::ThrowError(L, "Self is not a valid LunaInstance.");
}

LunaInstance* Luna::Class::GetSelf(lua_State* L) { return (LunaInstance*)lua_touserdata(L, 1); }

#include "Classes/LunaBase.h"
#include "Classes/SexyAppClass.h"
#include "Classes/LawnAppClass.h"
#include "Classes/UIContainerClass.h"
#include "Classes/UIRootClass.h"

#include "LunaApi/LunaUtil/LunaUtil.h"

int Luna::Class::Init(lua_State* L)
{
	FIELDS = new LunaField[MAX_FIELD_CAPACITY];
	
	lua_newtable(L);
	LunaUtil::Local(L, "ClassRef", -1);

	lua_newtable(L);
	LunaUtil::Local(L, "Injected", -1);

	lua_newtable(L);
	lua_pushstring(L, "__mode");
	lua_pushstring(L, "k");
	lua_settable(L, -3);
	lua_setmetatable(L, -2);

	lua_newtable(L);// Luna Meta
	SetMeta(__gc);
	SetMeta(__type);
	SetMeta(__call);
	SetMeta(__index);
	SetMeta(__newindex);
	SetMeta(__tostring);

	LunaUtil::Local(L, "ClassMeta", -1);
	LunaInit(Class::LunaBase);
	LunaInit(Class::LunaAppBase);
	LunaInit(Class::LunaApp);
	LunaInit(Class::LunaUIContainer);
	LunaInit(Class::LunaUIRoot);

	return 0;
}