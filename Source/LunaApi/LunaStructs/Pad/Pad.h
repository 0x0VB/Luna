#pragma once
#include "Luau/lua.h"
#include "PvZ/Definitions.h"

namespace Luna::Structs::Pad
{
	int Constructor(lua_State* L);

	int __index(lua_State* L);
	int __newindex(lua_State* L);
	int __tostring(lua_State* L);

	int __add(lua_State* L);
	int __sub(lua_State* L);
	int __mul(lua_State* L);
	int __div(lua_State* L);
	int __eq(lua_State* L);
	int __gc(lua_State* L);

	int Lerp(lua_State* L);
	int Init(lua_State* L);
}

Pad GetPad(lua_State* L, int Idx);
Pad* NewPad(lua_State* L, int, int T, int R, int B);
Pad* NewPad(lua_State* L, int H, int V);
Pad* NewPad(lua_State* L, int P);
Pad* GetPadSelf(lua_State* L);