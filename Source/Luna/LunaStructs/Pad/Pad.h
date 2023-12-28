#pragma once
namespace LunaStruct::Pad
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

Pad GetPad(int Idx);
Pad* NewPad(int L, int T, int R, int B);
Pad* NewPad(int H, int V);
Pad* NewPad(int P);
Pad* GetPadSelf();