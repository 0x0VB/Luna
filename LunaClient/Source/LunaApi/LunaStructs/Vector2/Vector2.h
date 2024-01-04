#include "Luau/lua.h"
#include "PvZ/Definitions.h"

namespace Luna::Structs::Vector2
{
	int Constructor(lua_State* L);// Constructs a lua version of the structure

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

	int SetMagnitude(lua_State* L);
	int DistanceFrom(lua_State* L);
	int DirectionTo(lua_State* L);
	int Magnitude(lua_State* L);
	int Rotate(lua_State* L);
	int Normal(lua_State* L);
	int ToInt(lua_State* L);
	int Nudge(lua_State* L);
	int To3D(lua_State* L);
	int Unit(lua_State* L);
	int Lerp(lua_State* L);

	int Init(lua_State* L);
};

DVector2 GetVector2(lua_State* L, int Idx);
DVector2* NewVector2(lua_State* L, double X = 0, double Y = 0);
DVector2* GetV2Self(lua_State* L);

template<typename T>
void Vector2<T>::Push(lua_State* L) { NewVector2(L, (double)X, (double)Y); }