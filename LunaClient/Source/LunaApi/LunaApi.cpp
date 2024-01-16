#include "stdafx.h"
#include "LunaApi.h"

#include "LunaApi/LunaIO/LunaIO.h"
#include "LunaApi/LunaUtil/LunaUtil.h"
#include "LunaApi/LunaStructs/LunaStructs.h"
#include "LunaApi/LunaEvent/LunaEvent.h"
#include "LunaApi/LunaClass/LunaClass.h"
#include "LunaApi/LunaEnum/EnumList.h"

int LunaApi::GlobalsTableRef;

int LunaApi::Init(lua_State* L)
{
	luaL_openlibs(L);				// Open Luau Standard Libraries

	lua_newuserdata(L, 0);			// Create Luna object
	lua_newtable(L);				// Create Luna table metatable

	lua_pushstring(L, "__index");
	lua_newtable(L);				// Create Luna table metatable __index
	GlobalsTableRef = lua_ref(L, -1);
	lua_settable(L, -3);			// Set Luna table metatable __index

	lua_pushstring(L, "__newindex");
	lua_pushstring(L, "Luna: Cannot modify Luna table");
	lua_settable(L, -3);			// Set Luna table metatable __newindex

	lua_pushstring(L, "__metatable");
	lua_pushstring(L, "Luna: Cannot access metatable");
	lua_settable(L, -3);			// Set Luna table metatable __metatable

	lua_setmetatable(L, -2);		// Set Luna table metatable

	lua_setglobal(L, "Luna");		// Set Luna table to global

	LunaInit(LunaIO);				// Responsible for print/warn/info functions.
	LunaInit(LunaUtil);				// General-purpose lua functions that make dealing with lua easier.
	LunaInit(LunaStruct);			// Contains structs like Vector2, Rect, Color, etc.
	LunaInit(Luna::Enum);			// Handles custom values within predefined sets.
	LunaInit(Luna::Event);			// Ports events onto lua, is also the main hooking lib.
	LunaInit(Luna::Class);			// Wraps C++ classes into lua, allowing user interaction.
	LunaInit(Enums);				// Prepares and sets all enum libraries and items.
	return 0;
}

void LunaApi::SetGlobal(lua_State* L, const char* Name)
{
	lua_getref(L, GlobalsTableRef);
	lua_pushstring(L, Name);
	lua_pushvalue(L, -3);
	lua_settable(L, -3);
	lua_pop(L, 1);
}
