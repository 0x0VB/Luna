#pragma once
namespace LunaStruct::Vector3
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

	int SetMagnitude(lua_State* L);
	int DistanceFrom(lua_State* L);
	int DirectionTo(lua_State* L);
	int Magnitude(lua_State* L);
	int Project(lua_State* L);
	int Rotate(lua_State* L);
	int Normal(lua_State* L);
	int ToInt(lua_State* L);
	int Nudge(lua_State* L);
	int To2D(lua_State* L);
	int Unit(lua_State* L);
	int Lerp(lua_State* L);

	int Init(lua_State* L);
};

FVector3 GetVector3(int Idx);
FVector3* NewVector3(float X = 0, float Y = 0, float Z = 0);
FVector3* GetV3Self();