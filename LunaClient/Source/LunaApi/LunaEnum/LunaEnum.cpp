#include "stdafx.h"

#include "LunaApi/LunaClass/LunaClass.h"
#include "LunaApi/LunaUtil/LunaUtil.h"
#include "LunaEnum.h"
#include "Luna.h"

using namespace Luna::Enum;

#pragma region EnumLib Member Functions
bool EnumLib::Contains(std::string Name) { return Items.contains(Name); }
bool EnumLib::Contains(EnumItem* Item) { return Items.contains(Item->Name); }
bool EnumLib::Contains(int Value) { return Values.contains(Value); }

void EnumLib::Add(EnumItem* Item)
{
	Item->Library = this;
	Items[Item->Name] = Item;
	Values[Item->Value] = Item;
}

void EnumLib::Add(lua_State* L, std::string ItemName, int Value)
{
	auto Item = EnumItem::New(L, this, ItemName, Value);
}

int EnumLib::AssertEnum(lua_State* L, int Index, std::string ParamName)
{
	int T = lua_gettop(L);
	
	if (lua_isuserdata(L, Index))
	{
		lua_getmetatable(L, Index);
		LunaUtil::GetRegKey(L, "EnumItemMeta");
		if (lua_equal(L, -2, -1))
		{
			lua_settop(L, T);
			auto self = *(EnumItem**)lua_touserdata(L, Index);
			return self->Value;
		}
	}
	else if (lua_isnumber(L, Index))
	{
		int Value = GetInt(L, Index);
		if (Contains(Value)) return Value;
	}
	else if (lua_isstring(L, Index))
	{
		auto ItemName = GetString(L, Index);
		if (Contains(ItemName)) return Items[ItemName]->Value;
	}
	LunaIO::ThrowError(L, "Expected a " + Name + " for " + ParamName + ", got " + LunaUtil::Type(L, Index));
}

EnumLib* EnumLib::New(lua_State* L, std::string LibName)
{
	int T = lua_gettop(L);
	auto Proxy = (EnumLib**)lua_newuserdata(L, 4);
	*Proxy = new EnumLib(LibName);

	LunaUtil::GetRegKey(L, "EnumLibMeta");
	lua_setmetatable(L, -2);
	(*Proxy)->Reference = lua_ref(L, -1);
	lua_settop(L, T);

	return *Proxy;
}
#pragma endregion

#pragma region EnumItem Member Functions
EnumItem* EnumItem::New(lua_State* L, EnumLib* Lib, std::string ItemName, int Value)
{
	int T = lua_gettop(L);
	auto Proxy = (EnumItem**)lua_newuserdata(L, 4);
	*Proxy = new EnumItem(ItemName, Lib, Value);

	LunaUtil::GetRegKey(L, "EnumItemMeta");
	lua_setmetatable(L, -2);
	(*Proxy)->Reference = lua_ref(L, -1);
	lua_settop(L, T);

	return *Proxy;
}
#pragma endregion

#pragma region EnumLib Meta
int EnumLib::__type(lua_State* L)
{
	lua_pushstring(L, "EnumLibrary");
	return 1;
}

int EnumLib::__index(lua_State* L)
{
	auto self = *(EnumLib**)lua_touserdata(L, 1);
	auto Field = GetField(L);
	if (Field == "Name") lua_pushstring(L, self->Name.c_str());
	else if (self->Contains(Field)) lua_getref(L, self->Items[Field]->Reference);
	else LunaIO::ThrowError(L, Field + " is not a valid member of EnumLibrary.");

	return 1;
}

int EnumLib::__newindex(lua_State* L) { LunaIO::ThrowError(L, "EnumLibraries are read-only."); }
int EnumLib::__tostring(lua_State* L)
{
	auto self = *(EnumLib**)lua_touserdata(L, 1);
	lua_pushstring(L, ("Enum." + self->Name).c_str());
	return 1;
}
#pragma endregion

#pragma region EnumItem Meta
int EnumItem::__type(lua_State* L)
{
	lua_pushstring(L, "EnumItem");
	return 1;
}

int EnumItem::__index(lua_State* L)
{
	auto self = *(EnumItem**)lua_touserdata(L, 1);
	auto Field = GetField(L);

	if (Field == "Name") lua_pushstring(L, self->Name.c_str());
	else if (Field == "Value") lua_pushinteger(L, self->Value);
	else if (Field == "Library") lua_getref(L, self->Library->Reference);
	else if (Field == "Type") lua_pushstring(L, self->Library->Name.c_str());
	else LunaIO::ThrowError(L, Field + " is not a valid member of EnumItem.");

	return 1;
}

int EnumItem::__newindex(lua_State* L)
{
	LunaIO::ThrowError(L, "EnumItems are read-only.");
}

int EnumItem::__tostring(lua_State* L)
{
	auto self = *(EnumItem**)lua_touserdata(L, 1);
	lua_pushstring(L, ("Enum." + self->Library->Name + "." + self->Name).c_str());
	return 1;
}
#pragma endregion

void Luna::Enum::SetEnum(lua_State* L, EnumLib* Lib)
{
	lua_getglobal(L, "Enum");
	lua_pushstring(L, Lib->Name.c_str());
	lua_getref(L, Lib->Reference);
	lua_settable(L, -3);
	lua_pop(L, 1);
}

int Luna::Enum::Init(lua_State* L)
{
	lua_newtable(L);// Enums
	lua_setglobal(L, "Enum");

	lua_newtable(L);// EnumLibrary Meta
	
	lua_pushstring(L, "__type");
	lua_pushcclosure(L, EnumLib::__type, "EnumLib::__type", 0);
	lua_settable(L, -3);

	lua_pushstring(L, "__index");
	lua_pushcclosure(L, EnumLib::__index, "EnumLib::__index", 0);
	lua_settable(L, -3);

	lua_pushstring(L, "__newindex");
	lua_pushcclosure(L, EnumLib::__newindex, "EnumLib::__newindex", 0);
	lua_settable(L, -3);

	lua_pushstring(L, "__tostring");
	lua_pushcclosure(L, EnumLib::__tostring, "EnumLib::__tostring", 0);
	lua_settable(L, -3);
	LunaUtil::SetRegKey(L, "EnumLibMeta");


	lua_newtable(L);// EnumItem Meta

	lua_pushstring(L, "__type");
	lua_pushcclosure(L, EnumItem::__type, "EnumItem::__type", 0);
	lua_settable(L, -3);

	lua_pushstring(L, "__index");
	lua_pushcclosure(L, EnumItem::__index, "EnumItem::__index", 0);
	lua_settable(L, -3);

	lua_pushstring(L, "__newindex");
	lua_pushcclosure(L, EnumItem::__newindex, "EnumItem::__newindex", 0);
	lua_settable(L, -3);

	lua_pushstring(L, "__tostring");
	lua_pushcclosure(L, EnumItem::__tostring, "EnumItem::__tostring", 0);
	lua_settable(L, -3);
	LunaUtil::SetRegKey(L, "EnumItemMeta");

	return 0;
}