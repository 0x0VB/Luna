#include "stdafx.h"
#include "Vector2.h"

#include "LunaApi/LunaStructs/Vector3/Vector3.h"

#include "LunaApi/LunaUtil/LunaUtil.h"
#include "LunaApi/LunaIO/LunaIO.h"
#include "Luna.h"

#pragma region C++ Functions
DVector2 GetVector2(lua_State* L, int Index)
{
	AssertType(L, Index, "Vector2", "arg#" + std::to_string(Index));
	return *(DVector2*)lua_touserdata(L, Index);
}
DVector2* GetV2Self(lua_State* L) { return (DVector2*)lua_touserdata(L, 1); }
DVector2* NewVector2(lua_State* L, double X, double Y)
{
	auto New = (DVector2*)lua_newuserdata(L, sizeof(DVector2));
	LunaUtil::Local(L, "Vector2Meta");
	lua_setmetatable(L, -2);

	New->X = X;
	New->Y = Y;

	return New;
}
#pragma endregion

#pragma region Lua Functions
int Luna::Structs::Vector2::Constructor(lua_State* L)
{
	auto X = GetDouble(L, 1);
	auto Y = GetDouble(L, 2);
		NewVector2(L, X, Y);
	return 1;
}

int Luna::Structs::Vector2::SetMagnitude(lua_State* L)
{
	auto self = GetVector2(L, 1);
	auto Magnitude = GetFloat(L, 2);
	self.SetMagnitude(Magnitude);
	self.Push(L);
	return 1;
}
int Luna::Structs::Vector2::DistanceFrom(lua_State* L)
{
	auto self = GetVector2(L, 1);
	if (LunaUtil::Type(L, 2) == "Vector3")
	{
		auto Other = GetVector3(L, 2);
		lua_pushnumber(L, Other.DistanceFrom3D(self));
	}
	else
	{
		auto Other = GetVector2(L, 2);
		lua_pushnumber(L, Other.DistanceFrom(self));
	}
	return 1;
}
int Luna::Structs::Vector2::DirectionTo(lua_State* L)
{
	auto self = GetVector2(L, 1);
	if (LunaUtil::Type(L, 2) == "Vector3")
	{
		auto Other = GetVector3(L, 2);
		self.DirectionTo(Other.Project()).Push(L);
	}
	else
	{
		auto Other = GetVector2(L, 2);
		self.DirectionTo(Other).Push(L);
	}
	return 1;
}
int Luna::Structs::Vector2::Magnitude(lua_State* L)
{
	lua_pushnumber(L, GetVector2(L, 1).Magnitude());
	return 1;
}
int Luna::Structs::Vector2::Rotate(lua_State* L)
{
	(GetVector2(L, 1) % GetFloat(L, 2)).Push(L);
	return 1;
}
int Luna::Structs::Vector2::Normal(lua_State* L)
{
	(GetVector2(L, 1).Normal()).Push(L);
	return 1;
}
int Luna::Structs::Vector2::Nudge(lua_State* L)
{
	auto self = GetVector2(L, 1);
	if (LunaUtil::Type(L, 2) == "Vector3")
	{
		auto Other = GetVector3(L,  2);
		self.Nudge(Other.Project(), GetFloat(L, 3, 1));
		self.Push(L);
	}
	else
	{
		auto Other = GetVector2(L, 2);
		self.Nudge(Other, GetFloat(L, 3, 1));
		self.Push(L);
	}
	return 1;
}
int Luna::Structs::Vector2::ToInt(lua_State* L)
{
	auto self = GetV2Self(L);
	self->ToInt().Push(L);
	return 1;
}
int Luna::Structs::Vector2::Unit(lua_State* L)
{
	(GetVector2(L, 1).Unit()).Push(L);
	return 1;
}
int Luna::Structs::Vector2::Lerp(lua_State* L)
{
	auto self = GetVector2(L, 1);
	if (LunaUtil::Type(L, 2) == "Vector3")
	{
		auto Other = GetVector3(L, 2);
		self.Lerp(Other.Project(), GetFloat(L, 3, 0.5));
		self.Push(L);
	}
	else
	{
		auto Other = GetVector2(L, 2);
		self.Lerp(Other, GetFloat(L, 3, 0.5));
		self.Push(L);
	}
	return 1;
}
int Luna::Structs::Vector2::To3D(lua_State* L)
{
	auto self = GetV2Self(L);
	NewVector3(L, (float)self->X, (float)self->Y, 0);
	return 1;
}
#pragma endregion

#pragma region Meta Methods
int Luna::Structs::Vector2::__index(lua_State* L)
{
	auto self = GetV2Self(L);
	auto Field = GetString(L, 2);

	if (Field == "X") lua_pushnumber(L, self->X);
	else if (Field == "Y") lua_pushnumber(L, self->Y);
	else
	{
		LunaUtil::Local(L, "Vector2Meta");
		lua_pushvalue(L, 2);
		lua_gettable(L, -2);
		if (lua_isnil(L, -1) || Field[0] == '_') LunaIO::ThrowError(L, Field + " is not a valid attribute of Vector2.");
	}

	return 1;
}
int Luna::Structs::Vector2::__newindex(lua_State* L)
{
	auto self = GetV2Self(L);
	auto Field = lua_tostring(L, 2)[0];
	auto Value = (double)lua_tonumber(L, 3);
	if (!lua_isnumber(L, 3)) LunaIO::ThrowError(L, "Vector2 values only accept number fields.");
	if (Field == 'X') self->X = Value;
	else if (Field == 'Y') self->Y = Value;
	else LunaIO::ThrowError(L, std::string(lua_tostring(L, 2)) + " is not a valid attribute of Vector2 or is read-only.");
	return 0;
}
int Luna::Structs::Vector2::__tostring(lua_State* L)
{
	auto self = GetVector2(L, 1);
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
	auto OType = LunaUtil::Type(L, 2);
	if (OType != "Vector2") LunaIO::ThrowError(L, "Unable to add Vector2 and " + OType + ".");

	auto self = GetVector2(L, 1);
	auto Other = GetVector2(L, 2);
	(self + Other).Push(L);
	return 1;
}
int Luna::Structs::Vector2::__sub(lua_State* L)
{
	auto OType = LunaUtil::Type(L, 2);
	if (OType != "Vector2") LunaIO::ThrowError(L, "Unable to subtract " + OType + " from Vector2.");

	auto self = GetVector2(L, 1);
	auto Other = GetVector2(L, 2);
	(self - Other).Push(L);
	return 1;
}
int Luna::Structs::Vector2::__mul(lua_State* L)
{
	if (!lua_isnumber(L, 2)) LunaIO::ThrowError(L, "Unable to multiply Vector2 by " + LunaUtil::Type(L, 2) + ".");

	auto self = GetVector2(L, 1);
	auto Factor = (double)lua_tonumber(L, 2);
	if (!lua_isnumber(L, 2)) LunaIO::ThrowError(L, "Cannot multiply Vector2 by " + LunaUtil::Type(L, 2) + ".");
	(self * Factor).Push(L);
	return 1;
}
int Luna::Structs::Vector2::__div(lua_State* L)
{
	if (!lua_isnumber(L, 2)) LunaIO::ThrowError(L, "Unable to divide Vector2 by " + LunaUtil::Type(L, 2) + ".");

	auto self = GetVector2(L, 1);
	auto Factor = (double)lua_tonumber(L, 2);
	if (!lua_isnumber(L, 2)) LunaIO::ThrowError(L, "Cannot divide Vector2 by " + LunaUtil::Type(L, 2) + ".");
	(self / Factor).Push(L);
	return 1;
}
int Luna::Structs::Vector2::__unm(lua_State* L)
{
	(-GetVector2(L, 1)).Push(L);
	return 1;
}
int Luna::Structs::Vector2::__eq(lua_State* L)
{
	if (LunaUtil::Type(L, 2) != "Vector2") { lua_pushboolean(L, 0); return 1; }
	auto self = GetVector2(L, 1);
	auto Other = GetVector2(L, 2);
	lua_pushboolean(L, self == Other);
	return 1;
}
int Luna::Structs::Vector2::__gc(lua_State* L)
{
	auto self = GetV2Self(L);
	delete self;
	return 0;
}
#pragma endregion

int Luna::Structs::Vector2::Init(lua_State* L)
{
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

	LunaUtil::Local(L, "Vector2Meta", -1);
	return 0;
}