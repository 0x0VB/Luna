#include "stdafx.h"

#include "LunaApi/LunaClass/LunaClass.h"
#include "LunaApi/LunaUtil/LunaUtil.h"
#include "LunaEnum.h"
#include "Luna.h"

using namespace Luna::Enum;

bool EnumLib::Contains(std::string Name)
{
	return Items.contains(Name);
}

bool EnumLib::Contains(EnumItem* Item)
{
	return Values.contains(Item->Value);
}

bool EnumLib::Contains(int Value)
{
	return Values.contains(Value);
}

void EnumLib::Add(EnumItem* Item)
{
	Values.insert(Item->Value);
	Items[Item->Name] = Item->Reference;
	Item->LibReference = Reference;
}

EnumItem* EnumLib::Add(lua_State* L, std::string ItemName, int Value)
{
	auto Item = EnumItem::New(L, this, ItemName, Value);
	Add(Item);
}

EnumLib* EnumLib::New(lua_State* L, std::string LibName)
{
	int T = lua_gettop(L);
	auto self = (EnumLib*)lua_newuserdata(L, sizeof(EnumLib));

	LunaUtil::GetRegKey(L, "EnumLibMeta");
	lua_setmetatable(L, -2);

	self->Name = std::string(LibName);
	self->Items = std::map<std::string, EnumRef>();
	self->Values = std::set<int>();
	self->Reference = lua_ref(L, -1);

	lua_settop(L, T);
	return self;
}

EnumItem* EnumItem::New(lua_State* L, EnumLib* Lib, std::string ItemName, int Value)
{
	int T = lua_gettop(L);
	auto self = (EnumItem*)lua_newuserdata(L, sizeof(EnumItem));

	LunaUtil::GetRegKey(L, "EnumItemMeta");
	lua_setmetatable(L, -2);

	self->Reference = lua_ref(L, -1);
	self->LibReference = Lib->Reference;
	self->Name = std::string(ItemName);
	self->Value = Value;

	Lib->Add(self);
	return self;
}

#pragma region MetaMethods
using namespace Luna::Class;
int EnumItem::__type(lua_State* L)
{
	lua_pushstring(L, "EnumItem");
	return 1;
}

int EnumItem::__index(lua_State* L)
{
	if (!lua_isstring(L, 2)) LunaIO::ThrowError(L, "Can only index string fields in enums.");
	auto self = (EnumItem*)lua_touserdata(L, 1);
	auto Field = GetString(L, 2);
	if (Field == "Name") lua_pushstring(L, self->Name.c_str());
	else if (Field == "Value") lua_pushinteger(L, self->Value);
	else if (Field == "Library") lua_getref(L, self->LibReference);
	else LunaIO::ThrowError(L, "Unable to index field " + Field + ".");
	return 1;
}

int EnumItem::__newindex(lua_State* L)
{
	LunaIO::ThrowError(L, "EnumItems are read-only.");
}

int EnumItem::__tostring(lua_State* L)
{
	auto self = (EnumItem*)lua_touserdata(L, 1);
	lua_pushstring(L, self->Name.c_str());
	return 1;
}

int EnumLib::__type(lua_State* L)
{
	lua_pushstring(L, "EnumLib");
	return 1;
}

int EnumLib::__index(lua_State* L)
{
	if (!lua_isstring(L, 2)) LunaIO::ThrowError(L, "Can only index string fields in enums.");
	auto self = (EnumLib*)lua_touserdata(L, 1);
	auto Field = GetString(L, 2);

	if (!self->Contains(Field)) LunaIO::ThrowError(L, "Unable to index field " + Field);
	lua_getref(L, self->Items[Field]);
	return 1;
}

int EnumLib::__newindex(lua_State* L)
{
	LunaIO::ThrowError(L, "EnumLibs are read-only.");
}

int EnumLib::__tostring(lua_State* L)
{
	auto self = (EnumLib*)lua_touserdata(L, 1);
	lua_pushstring(L, self->Name.c_str());
	std::cout << "Name: " << self->Name;
	return 1;
}
#pragma endregion

namespace
{
	void SetEnum(lua_State* L, EnumLib* Lib)
	{
		lua_getglobal(L, "Enum");
		lua_pushstring(L, Lib->Name.c_str());
		lua_getref(L, Lib->Reference);
		lua_settable(L, -3);
		lua_pop(L, 1);
	}

	void PlantState(lua_State* L)
	{
		auto Lib = EnumLib::New(L, "PlantState");

		Lib->Add(L, "NotReady", 0);
		Lib->Add(L, "Ready", 1);

		SetEnum(L, Lib);
	}

	void SetupEnums(lua_State* L)
	{
		// Plant Enums
		std::cout << "Called";

		PlantState(L);
		std::cout << "Setup Plants!";
	}
}

int Luna::Enum::Init(lua_State* L)
{
	lua_newtable(L);// EnumLib Meta
	
	lua_pushstring(L, "__type");
	lua_pushcclosure(L, EnumLib::__type, "EnumLib::__type", 0);
	lua_settable(L, 1);

	lua_pushstring(L, "__index");
	lua_pushcclosure(L, EnumLib::__index, "EnumLib::__index", 0);
	lua_settable(L, 1);

	lua_pushstring(L, "__newindex");
	lua_pushcclosure(L, EnumLib::__newindex, "EnumLib::__newindex", 0);
	lua_settable(L, 1);

	lua_pushstring(L, "__tostring");
	lua_pushcclosure(L, EnumLib::__tostring, "EnumLib::__tostring", 0);
	lua_settable(L, 1);
	LunaUtil::SetRegKey(L, "EnumLibMeta");

	lua_newtable(L);// EnumItem Meta

	lua_pushstring(L, "__type");
	lua_pushcclosure(L, EnumItem::__type, "EnumItem::__type", 0);
	lua_settable(L, 1);

	lua_pushstring(L, "__index");
	lua_pushcclosure(L, EnumItem::__index, "EnumItem::__index", 0);
	lua_settable(L, 1);

	lua_pushstring(L, "__newindex");
	lua_pushcclosure(L, EnumItem::__newindex, "EnumItem::__newindex", 0);
	lua_settable(L, 1);

	lua_pushstring(L, "__tostring");
	lua_pushcclosure(L, EnumItem::__tostring, "EnumItem::__tostring", 0);
	lua_settable(L, 1);
	LunaUtil::SetRegKey(L, "EnumItemMeta");

	lua_newtable(L);// Enums Table
	lua_setglobal(L, "Enum");

	SetupEnums(L);
	return 0;
}