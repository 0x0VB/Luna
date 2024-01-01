#pragma once
#include "Luau/lua.h"
#include "PvZ/Definitions.h"

namespace Luna::Structs::Rect
{
	int Constructor(lua_State* L);

	int __index(lua_State* L);
	int __newindex(lua_State* L);
	int __tostring(lua_State* L);

	int __add(lua_State* L);
	int __sub(lua_State* L);
	int __mul(lua_State* L);
	int __div(lua_State* L);
	int __unm(lua_State* L);
	int __eq(lua_State* L);
	int __gc(lua_State* L);

	int GetIntersection(lua_State* L);
	int SetPosition(lua_State* L);
	int Intersects(lua_State* L);
	int GetCenter(lua_State* L);
	int SetCenter(lua_State* L);
	int Contains(lua_State* L);
	int SetSize(lua_State* L);
	int GetArea(lua_State*);
	int Lerp(lua_State* L);
	
	int Init(lua_State* L);
};

IRect GetRect(int Idx);
IRect* NewRect(int X = 0, int Y = 0, int W = 0, int H = 0);
IRect* GetRectSelf();