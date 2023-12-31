#include "stdafx.h"
#include "LunaClass.h"

#include "LunaApi/LunaUtil/LunaUtil.h"
#include "LunaApi/LunaStructs/LunaStructs.h"
#include "LunaApi/LunaIO/LunaIO.h"
#include "Luna.h"

namespace Luna::Class {
	std::map<void*, bool> CLASS_VALIDATE = {};
	CONST SIZE_T MAX_FIELD_CAPACITY = 1000;
	SIZE_T FIELDS_USED = 0;
	Base::LunaField* FIELDS = nullptr;
}

using namespace Luna::Class::Base;

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
int LunaClass::__call(lua_State* L) { LunaIO::ThrowError(std::string("Unable to call a ") + Name + "."); return 0; }
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
LunaInstance* LunaClass::New(lua_State* L, void* Param)
{
	int T = lua_gettop(L);
	auto self = (LunaInstance*)lua_newuserdata(L, sizeof(LunaInstance));
	self->Base = Param;
	self->Class = this;

	LunaUtil::Local("ClassRef");

	lua_pushlightuserdata(L, self);
	lua_pushvalue(L, T + 1);
	lua_settable(L, T + 2);

	lua_pushlightuserdata(L, Param);
	lua_pushvalue(L, T + 1);
	lua_settable(L, T + 2);
	lua_settop(L, T + 1);

	LunaUtil::Local("ClassMeta");
	lua_setmetatable(L, T + 1);
	CLASS_VALIDATE[self] = true;

	if (!AllowsInjection) return self;
	LunaUtil::Local("Injected");
	lua_pushvalue(L, T + 1);
	lua_newtable(L);
	lua_settable(L, -3);
	lua_settop(L, T + 1);

	return self;
}
void LunaClass::PushInjected(lua_State* L)
{
	LunaUtil::Local("Injected");
	lua_pushvalue(L, 1);
	lua_gettable(L, -2);
}
void LunaClass::GetInjected(lua_State* L)
{
	PushInjected(L);
	lua_pushvalue(L, 2);
	lua_gettable(L, -2);
}
void LunaClass::Inject(lua_State* L)
{
	PushInjected(L);
	lua_pushvalue(L, 2);
	lua_pushvalue(L, 3);
	lua_settable(L, -3);
}
#pragma endregion

#pragma region LunaField
void LunaField::__newindex(lua_State* L) { LunaIO::ThrowError(std::string(Name) + " is read-only."); }
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
	return self->Class->__call(L);
}

int Luna::Class::__index(lua_State* L)
{
	auto self = GetAndAssert(L);
	auto Field = GetString(2);
	auto Class = self->Class;

	if (!lua_isstring(L, 2)) LunaIO::ThrowError("Expected a string field, got " + LunaUtil::Type(2));// Only string fields allowed
	else if (Class->Methods.contains(Field)) lua_pushcclosure(L, Class->Methods[Field], 0);// Get Method
	else if (Class->Fields.contains(Field)) Class->Fields[Field]->__index(L);// Get Field
	else if (!Class->AllowsInjection) LunaIO::ThrowError(Field + " is not a valid member of " + Class->Name);// Check if Field Injection is allowed
	else Class->GetInjected(L);// Get Injected Field
	return 1;
}

int Luna::Class::__newindex(lua_State* L)
{
	auto self = GetAndAssert(L);
	auto Field = GetString(2);
	auto Class = self->Class;

	if (!lua_isstring(L, 2)) LunaIO::ThrowError("Expected a string field, got " + LunaUtil::Type(2));// Only string fields allowed
	else if (Class->Methods.contains(Field)) LunaIO::ThrowError(Field + " is read-only.");// Error: Methods are read-only.
	else if (Class->Fields.contains(Field)) Class->Fields[Field]->__newindex(L);// Set Field
	else if (!Class->AllowsInjection) LunaIO::ThrowError(Field + " is not a valid member of " + Class->Name);// Check Injection
	else Class->Inject(L);// Inject a new field
	return 0;
}

int Luna::Class::__tostring(lua_State* L)
{
	auto self = GetAndAssert(L);
	self->Class->__tostring(L);
	return 1;
}
#pragma endregion

#pragma region LunaFields
void  Luna::Class::Fields::WindTitle::__index(lua_State* L)
{
	lua_pushstring(L, Luna::App->Title);
}
void Luna::Class::Fields::WindTitle::__newindex(lua_State* L)
{
	auto Value = GetString(3);
	AssertType(3, "string", Name);
	App->Title = Value;
	if (App->MainWindowHandle) SetWindowTextA(App->MainWindowHandle, Value.c_str());
}

void Luna::Class::Fields::WindBounds::__index(lua_State* L)
{
	App->WindowBounds.Push();
}
void Luna::Class::Fields::WindBounds::__newindex(lua_State* L)
{
	AssertType(3, "Rect", Name);
	auto Value = GetRect(3);
	App->WindowBounds = Value;
	if (App->MainWindowHandle) GetWindowRect(App->MainWindowHandle, Value.ToLPRECT());
}

void Luna::Class::Fields::BytField::__index(lua_State* L)
{
	FBase(BYTE);
	lua_pushnumber(L, *Base);
}
void Luna::Class::Fields::BytField::__newindex(lua_State* L)
{
	FBase(BYTE);
	auto Value = GetInt(3, -1);
	if (Value > 255 || Value < 0) LunaIO::ThrowError(std::string(Name) + " can only be a number between 0-255, got " + LunaUtil::Type(3));
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
	AssertType(3, "boolean", Name);
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
	if (!lua_isnumber(L, 3)) LunaIO::ThrowError(std::string("Expected an integer for ") + Name + ", got " + LunaUtil::Type(3));
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
	if (!lua_isnumber(L, 3)) LunaIO::ThrowError(std::string("Expected a number for ") + Name + ", got " + LunaUtil::Type(3));
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
	if (!lua_isnumber(L, 3)) LunaIO::ThrowError(std::string("Expected a number for ") + Name + ", got " + LunaUtil::Type(3));
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
	AssertType(3, "string", std::string(Name));
	Base->assign(lua_tostring(L, 3));
}

void Luna::Class::Fields::RctField::__index(lua_State* L)
{
	FBase(IRect);
	Base->Push();
}
void  Luna::Class::Fields::RctField::__newindex(lua_State* L)
{
	FBase(IRect);
	AssertType(3, "Rect", Name);
	*Base = GetRect(3);
}

void Luna::Class::Fields::IV2Field::__index(lua_State* L)
{
	FBase(IVector2);
	Base->Push();
}
void Luna::Class::Fields::IV2Field::__newindex(lua_State* L)
{
	FBase(IVector2);
	AssertType(3, "Vector2", Name);
	*Base = (IVector2)GetVector2(3);
}

void Luna::Class::Fields::FV2Field::__index(lua_State* L)
{
	FBase(FVector2);
	Base->Push();
}
void Luna::Class::Fields::FV2Field::__newindex(lua_State* L)
{
	FBase(FVector2);
	AssertType(3, "Vector2", Name);
	*Base = (FVector2)GetVector2(3);
}

void Luna::Class::Fields::FV3Field::__index(lua_State* L)
{
	FBase(FVector3);
	Base->Push();
}
void Luna::Class::Fields::FV3Field::__newindex(lua_State* L)
{
	FBase(FVector3);
	AssertType(3, "Vector3", Name);
	*Base = GetVector3(3);
}

void Luna::Class::Fields::ColField::__index(lua_State* L)
{
	FBase(Color);
	Base->Push();
}
void Luna::Class::Fields::ColField::__newindex(lua_State* L)
{
	FBase(Color);
	AssertType(3, "Color", Name);
	*Base = GetColor(3);
}

void Luna::Class::Fields::PadField::__index(lua_State* L)
{
	auto Event = (Luna::Event::LunaEvent*)Offset;
	Event->Push();
}
void Luna::Class::Fields::PadField::__newindex(lua_State* L)
{
	FBase(Pad);
	AssertType(3, "Pad", Name);
	*Base = GetPad(3);
}

void Luna::Class::Fields::EventField::__index(lua_State* L)
{
	auto Event = (Luna::Event::LunaEvent*)Offset;
	Event->Push();
}
#pragma endregion

LunaInstance* Luna::Class::GetAndAssert(lua_State* L)
{
	void* self = lua_touserdata(L, 1);
	if (!lua_isuserdata(L, 1)) LunaIO::ThrowError("Unable to get self.");
	if (CLASS_VALIDATE.contains(self)) return (Base::LunaInstance*)self;
	LunaIO::ThrowError("Self is not a valid LunaInstance.");
}

LunaInstance* Luna::Class::GetSelf(lua_State* L) { return (Base::LunaInstance*)lua_touserdata(L, 1); }

#include "Classes/SexyAppClass.h"
#include "Classes/LawnAppClass.h"
int Luna::Class::Init(lua_State* L)
{
	FIELDS = new Base::LunaField[MAX_FIELD_CAPACITY];
	
	lua_newtable(L);
	LunaUtil::Local("ClassRef", -1);

	lua_newtable(L);
	LunaUtil::Local("Injected", -1);

	lua_newtable(L);

	lua_pushstring(L, "__type");
	lua_pushcclosure(L, __type, 0);
	lua_settable(L, -3);

	lua_pushstring(L, "__call");
	lua_pushcclosure(L, __call, 0);
	lua_settable(L, -3);

	lua_pushstring(L, "__index");
	lua_pushcclosure(L, __index, 0);
	lua_settable(L, -3);

	lua_pushstring(L, "__newindex");
	lua_pushcclosure(L, __newindex, 0);
	lua_settable(L, -3);

	lua_pushstring(L, "__tostring");
	lua_pushcclosure(L, __tostring, 0);
	lua_settable(L, -3);

	LunaUtil::Local("ClassMeta", -1);
	LunaInit(Classes::LunaAppBase);
	LunaInit(Classes::LunaApp);

	return 0;
}