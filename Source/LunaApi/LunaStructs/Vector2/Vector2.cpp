#include "stdafx.h"
#include "Vector2.h"

#include "LunaApi/LunaStructs/Vector3/Vector3.h"

#include "LunaApi/LunaUtil/LunaUtil.h"
#include "LunaApi/LunaIO/LunaIO.h"
#include "Luna.h"

#pragma region C++ Functions
DVector2 GetVector2(int Index)
{
	AssertType(Index, "Vector2", "arg#" + std::to_string(Index));
	return *(DVector2*)lua_touserdata(Luna::GlobalLState, Index);
}
DVector2* GetV2Self() { return (DVector2*)lua_touserdata(Luna::GlobalLState, 1); }
DVector2* NewVector2(double X, double Y)
{
	auto New = (DVector2*)lua_newuserdata(Luna::GlobalLState, sizeof(DVector2));
	LunaUtil::Local("Vector2Meta");
	lua_setmetatable(Luna::GlobalLState, -2);

	New->X = X;
	New->Y = Y;

	return New;
}
#pragma endregion

#pragma region Lua Functions
int Luna::Structs::Vector2::Constructor(lua_State* L)
{
	auto X = GetDouble(1);
	auto Y = GetDouble(2);
	NewVector2(X, Y);
	return 1;
}

int Luna::Structs::Vector2::SetMagnitude(lua_State* L)
{
	auto self = GetVector2(1);
	auto Magnitude = GetFloat(2);
	self.SetMagnitude(Magnitude);
	self.Push();
	return 1;
}
int Luna::Structs::Vector2::DistanceFrom(lua_State* L)
{
	auto self = GetVector2(1);
	if (LunaUtil::Type(2) == "Vector3")
	{
		auto Other = GetVector3(2);
		lua_pushnumber(L, Other.DistanceFrom3D(self));
	}
	else
	{
		auto Other = GetVector2(2);
		lua_pushnumber(L, Other.DistanceFrom(self));
	}
	return 1;
}
int Luna::Structs::Vector2::DirectionTo(lua_State* L)
{
	auto self = GetVector2(1);
	if (LunaUtil::Type(2) == "Vector3")
	{
		auto Other = GetVector3(2);
		self.DirectionTo(Other.Project()).Push();
	}
	else
	{
		auto Other = GetVector2(2);
		self.DirectionTo(Other).Push();
	}
	return 1;
}
int Luna::Structs::Vector2::Magnitude(lua_State* L)
{
	lua_pushnumber(L, GetVector2(1).Magnitude());
	return 1;
}
int Luna::Structs::Vector2::Rotate(lua_State* L)
{
	(GetVector2(1) % GetFloat(2)).Push();
	return 1;
}
int Luna::Structs::Vector2::Normal(lua_State* L)
{
	(GetVector2(1).Normal()).Push();
	return 1;
}
int Luna::Structs::Vector2::Nudge(lua_State* L)
{
	auto self = GetVector2(1);
	if (LunaUtil::Type(2) == "Vector3")
	{
		auto Other = GetVector3(2);
		self.Nudge(Other.Project(), GetFloat(3, 1));
		self.Push();
	}
	else
	{
		auto Other = GetVector2(2);
		self.Nudge(Other, GetFloat(3, 1));
		self.Push();
	}
	return 1;
}
int Luna::Structs::Vector2::ToInt(lua_State* L)
{
	auto self = GetV2Self();
	self->ToInt().Push();
	return 1;
}
int Luna::Structs::Vector2::Unit(lua_State* L)
{
	(GetVector2(1).Unit()).Push();
	return 1;
}
int Luna::Structs::Vector2::Lerp(lua_State* L)
{
	auto self = GetVector2(1);
	if (LunaUtil::Type(2) == "Vector3")
	{
		auto Other = GetVector3(2);
		self.Lerp(Other.Project(), GetFloat(3, 0.5));
		self.Push();
	}
	else
	{
		auto Other = GetVector2(2);
		self.Lerp(Other, GetFloat(3, 0.5));
		self.Push();
	}
	return 1;
}
int Luna::Structs::Vector2::To3D(lua_State* L)
{
	auto self = GetV2Self();
	NewVector3((float)self->X, (float)self->Y, 0);
	return 1;
}
#pragma endregion

#pragma region Meta Methods
int Luna::Structs::Vector2::__index(lua_State* L)
{
	auto self = GetV2Self();
	auto Field = GetString(2);

	if (Field == "X") lua_pushnumber(L, self->X);
	else if (Field == "Y") lua_pushnumber(L, self->Y);
	else
	{
		LunaUtil::Local("Vector2Meta");
		lua_pushvalue(L, 2);
		lua_gettable(L, -2);
		if (lua_isnil(L, -1) || Field[0] == '_') LunaIO::ThrowError(Field + " is not a valid attribute of Vector2.");
	}

	return 1;
}
int Luna::Structs::Vector2::__newindex(lua_State* L)
{
	auto self = GetV2Self();
	auto Field = lua_tostring(L, 2)[0];
	auto Value = (double)lua_tonumber(L, 3);
	if (!lua_isnumber(L, 3)) LunaIO::ThrowError("Vector2 values only accept number fields.");
	if (Field == 'X') self->X = Value;
	else if (Field == 'Y') self->Y = Value;
	else LunaIO::ThrowError(std::string(lua_tostring(L, 2)) + " is not a valid attribute of Vector2 or is read-only.");
	return 0;
}
int Luna::Structs::Vector2::__tostring(lua_State* L)
{
	auto self = GetVector2(1);
	std::string ToString = "Vector2(";
	
	int IX = (int)self.X;
	int IY = (int)self.Y;
	if (self.X == IX) ToString += std::to_string(IX);
	else ToString += std::to_string(self.X);

	ToString += ", ";

	if (self.Y == IY) ToString += std::to_string(IY);
	else ToString += std::to_string(self.Y);
	lua_pushstring(L, (ToString + ")").c_str());
	return 1;
}

int Luna::Structs::Vector2::__add(lua_State* L)
{
	auto OType = LunaUtil::Type(2);
	if (OType != "Vector2") LunaIO::ThrowError("Unable to add Vector2 and " + OType + ".");

	auto self = GetVector2(1);
	auto Other = GetVector2(2);
	(self + Other).Push();
	return 1;
}
int Luna::Structs::Vector2::__sub(lua_State* L)
{
	auto OType = LunaUtil::Type(2);
	if (OType != "Vector2") LunaIO::ThrowError("Unable to subtract " + OType + " from Vector2.");

	auto self = GetVector2(1);
	auto Other = GetVector2(2);
	(self - Other).Push();
	return 1;
}
int Luna::Structs::Vector2::__mul(lua_State* L)
{
	if (!lua_isnumber(L, 2)) LunaIO::ThrowError("Unable to multiply Vector2 by " + LunaUtil::Type(2) + ".");

	auto self = GetVector2(1);
	auto Factor = (double)lua_tonumber(L, 2);
	if (!lua_isnumber(L, 2)) LunaIO::ThrowError("Cannot multiply Vector2 by " + LunaUtil::Type(2) + ".");
	(self * Factor).Push();
	return 1;
}
int Luna::Structs::Vector2::__div(lua_State* L)
{
	if (!lua_isnumber(L, 2)) LunaIO::ThrowError("Unable to divide Vector2 by " + LunaUtil::Type(2) + ".");

	auto self = GetVector2(1);
	auto Factor = (double)lua_tonumber(L, 2);
	if (!lua_isnumber(L, 2)) LunaIO::ThrowError("Cannot divide Vector2 by " + LunaUtil::Type(2) + ".");
	(self / Factor).Push();
	return 1;
}
int Luna::Structs::Vector2::__unm(lua_State* L)
{
	(-GetVector2(1)).Push();
	return 1;
}
int Luna::Structs::Vector2::__eq(lua_State* L)
{
	if (LunaUtil::Type(2) != "Vector2") { lua_pushboolean(L, 0); return 1; }
	auto self = GetVector2(1);
	auto Other = GetVector2(2);
	lua_pushboolean(L, self == Other);
	return 1;
}
int Luna::Structs::Vector2::__gc(lua_State* L)
{
	auto self = GetV2Self();
	delete self;
	return 0;
}
#pragma endregion

int Luna::Structs::Vector2::Init(lua_State* L)
{
#define SetMeta(Function) lua_pushstring(L, #Function); lua_pushcclosure(L, Function, 0); lua_settable(L, -3)
	lua_newtable(L);

	lua_pushstring(L, "__type");
	lua_pushstring(L, "Vector2");
	lua_settable(L, -3);

	SetMeta(__index);
	SetMeta(__newindex);
	SetMeta(__tostring);

	SetMeta(__add);
	SetMeta(__sub);
	SetMeta(__mul);
	SetMeta(__div);
	SetMeta(__unm);
	SetMeta(__eq);
	SetMeta(__gc);

	SetMeta(SetMagnitude);
	SetMeta(DistanceFrom);
	SetMeta(DirectionTo);
	SetMeta(Magnitude);
	SetMeta(Rotate);
	SetMeta(Normal);
	SetMeta(Nudge);
	SetMeta(ToInt);
	SetMeta(Unit);
	SetMeta(Lerp);
	SetMeta(To3D);

	LunaUtil::Local("Vector2Meta", -1);
	lua_register(L, "Vector2", Constructor);
	return 0;
}