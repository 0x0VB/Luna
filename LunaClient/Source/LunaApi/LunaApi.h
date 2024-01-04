#pragma once
#include "Luau/lua.h"

#define LunaApi Luna::Api

namespace LunaApi
{
	extern int GlobalsTableRef;
	int Init(lua_State* L);

	/// <summary>
	/// Pop last element from stack and set it as value at the passed field index in the real Luna table.
	/// LunaGlobalsTable[Name] = Value
	/// </summary>
	/// <param name="L"></param>
	/// <param name="Name"></param>
	void SetGlobal(lua_State* L, const char* Name);
}