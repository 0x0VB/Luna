#include "stdafx.h"
#include "Vector3.h"

#include "LunaApi/LunaUtil/LunaUtil.h"
#include "LunaApi/LunaIO/LunaIO.h"
#include "Luna.h"

#pragma region Strcut Functions
template <typename T>
void Vector3<T>::Push(lua_State* L) { NewVector3(L, X, Y, Z); }
#pragma endregion

#pragma region C++ Functions
FVector3 GetVector3(lua_State* L, int Idx)
{
	AssertType(L, Idx, "Vector3", "arg#" + std::to_string(Idx));
	return *(FVector3*)lua_touserdata(L, Idx);
}
FVector3* GetV3Self(lua_State* L) { return (FVector3*)lua_touserdata(L, 1); }
FVector3* NewVector3(lua_State* L, float X, float Y, float Z)
{
	auto New = (FVector3*)lua_newuserdata(L , sizeof(FVector3));
	LunaUtil::GetRegKey(L, "Vector3Meta");
	lua_setmetatable(L, -2);

	New->X = X;
	New->Y = Y;
	New->Z = Z;
	return New;
}
#pragma endregion

#pragma region Lua Functions
int Luna::Structs::Vector3::Constructor(lua_State* L)
{
	auto X = GetFloat(L, 1);
	auto Y = GetFloat(L, 2);
	auto Z = GetFloat(L, 3);
	NewVector3(L, X, Y, Z);
	return 1;
}

int Luna::Structs::Vector3::SetMagnitude(lua_State* L)
{
	auto self = GetVector3(L, 1);
	self.SetMagnitude((float)lua_tonumber(L, 2));
	self.Push(L);
	return 1;
}
int Luna::Structs::Vector3::DistanceFrom(lua_State* L)
{
	auto self = GetVector3(L, 1);
	auto Other = GetVector3(L, 2);
	lua_pushnumber(L, (self - Other).Magnitude());
	return 1;
}
int Luna::Structs::Vector3::DirectionTo(lua_State* L)
{
	auto self = GetVector3(L, 1);
	auto Other = GetVector3(L, 2);
	(self.DirectionTo(Other)).Push(L);
	return 1;
}
int Luna::Structs::Vector3::Magnitude(lua_State* L)
{
	auto self = GetVector3(L, 1);
	lua_pushnumber(L, self.Magnitude());
	return 1;
}
int Luna::Structs::Vector3::Project(lua_State* L)
{
	auto self = GetVector3(L, 1);
	self.Project().Push(L);
	return 1;
}
int Luna::Structs::Vector3::Rotate(lua_State* L)
{
	auto self = GetVector3(L, 1);
	auto Angle = GetFloat(L, 2);
	self %= Angle;
	self.Push(L);
	return 1;
}
int Luna::Structs::Vector3::Normal(lua_State* L)
{
	auto self = GetVector3(L, 1);
	self.Normal().Push(L);
	return 1;
}
int Luna::Structs::Vector3::Nudge(lua_State* L)
{
	auto self = GetVector3(L, 1);
	auto Other = GetVector3(L, 2);
	auto Amount = GetFloat(L, 3, 1);
	self.Nudge(Other, Amount);
	self.Push(L);
	return 1;
}
int Luna::Structs::Vector3::ToInt(lua_State* L)
{
	auto self = GetVector3(L, 1);
	NewVector3(L, (float)(int)self.X, (float)(int)self.Y, (float)(int)self.Z);
	return 1;
}
int Luna::Structs::Vector3::Unit(lua_State* L)
{
	auto self = GetVector3(L, 1);
	self.Unit().Push(L);
	return 1;
}
int Luna::Structs::Vector3::Lerp(lua_State* L)
{
	auto self = GetVector3(L, 1);
	auto Other = GetVector3(L, 2);
	auto Alpha = GetFloat(L, 0, 0.5);
	self.Lerp(Other, Alpha);
	self.Push(L);
	return 1;
}
int Luna::Structs::Vector3::To2D(lua_State* L)
{
	auto self = GetVector3(L, 1);
	self.To2D().Push(L);
	return 1;
}
#pragma endregion

#pragma region Meta Methods
int Luna::Structs::Vector3::__index(lua_State* L)
{
	auto self = GetV3Self(L);
	auto Field = GetString(L, 2);
	
	if (Field == "X") lua_pushnumber(L, (float)self->X);
	else if (Field == "Y") lua_pushnumber(L, (float)self->Y);
	else if (Field == "Z") lua_pushnumber(L, (float)self->Z);
	else
	{
		LunaUtil::GetRegKey(L, "Vector3Meta");
		lua_pushvalue(L, 2);
		lua_gettable(L, -2);
		if (lua_isnil(L, -1) || Field[0] == '_') LunaIO::ThrowError(L,  Field + " is not a valid attribute of Vector3.");
	}

	return 1;
}
int Luna::Structs::Vector3::__newindex(lua_State* L)
{
	auto self = GetV3Self(L);
	auto Field = lua_tostring(L, 2)[0];
	auto Value = (float)lua_tonumber(L, 3);
	if (!lua_isnumber(L, 3)) LunaIO::ThrowError(L, "Vector3 values only accept number fields.");
	if (Field == 'X') self->X = Value;
	else if (Field == 'Y') self->Y = Value;
	else if (Field == 'Z') self->Z = Value;
	else LunaIO::ThrowError(L, std::string(lua_tostring(L, 2)) + " is not a valid attribute of Vector3 or is read-only.");
	return 0;
}
int Luna::Structs::Vector3::__tostring(lua_State* L)
{
	auto self = GetVector3(L, 1);
	std::string ToString = "Vector3(";

	int IX = (int)self.X;
	int IY = (int)self.Y;
	int IZ = (int)self.Z;
	if (self.X == IX) ToString += std::to_string(IX);
	else ToString += std::to_string(self.X);

	ToString += ", ";

	if (self.Y == IY) ToString += std::to_string(IY);
	else ToString += std::to_string(self.Y);

	ToString += ", ";

	if (self.Z == IZ) ToString += std::to_string(IZ);
	else ToString += std::to_string(self.Z);

	lua_pushstring(L, (ToString + ")").c_str());
	return 1;
}

int Luna::Structs::Vector3::__add(lua_State* L)
{
	auto OType = LunaUtil::Type(L, 2);
	if (OType != "Vector3") LunaIO::ThrowError(L, "Unable to add Vector3 and " + OType + ".");

	auto self = GetVector3(L, 1);
	auto Other = GetVector3(L, 2);
	(self + Other).Push(L);
	return 1;
}
int Luna::Structs::Vector3::__sub(lua_State* L)
{
	auto OType = LunaUtil::Type(L, 2);
	if (OType != "Vector3") LunaIO::ThrowError(L, "Unable to subtract " + OType + " from Vector3.");

	auto self = GetVector3(L, 1);
	auto Other = GetVector3(L, 2);
	(self - Other).Push(L);
	return 1;
}
int Luna::Structs::Vector3::__mul(lua_State* L)
{
	if (!lua_isnumber(L, 2)) LunaIO::ThrowError(L, "Unable to multiply Vector3 by " + LunaUtil::Type(L, 2) + ".");

	auto self = GetVector3(L, 1);
	auto Factor = GetFloat(L, 2);
	if (!lua_isnumber(L, 2)) LunaIO::ThrowError(L, "Unable to multiple Vector3 by " + LunaUtil::Type(L, 2) + ".");
	(self * Factor).Push(L);
	return 1;
}
int Luna::Structs::Vector3::__div(lua_State* L)
{
	if (!lua_isnumber(L, 2)) LunaIO::ThrowError(L,  "Unable to multiply Vector3 by " + LunaUtil::Type(L, 2) + ".");

	auto self = GetVector3(L, 1);
	auto Factor = GetFloat(L, 2);
	if (!lua_isnumber(L, 2)) LunaIO::ThrowError(L, "Unable to divide Vector3 by " + LunaUtil::Type(L, 2) + ".");
	(self / Factor).Push(L);
	return 1;
}
int Luna::Structs::Vector3::__unm(lua_State* L)
{
	auto self = GetVector3(L, 1);
	(-self).Push(L);
	return 1;
}
int Luna::Structs::Vector3::__eq(lua_State* L)
{
	if (LunaUtil::Type(L, 2) != "Vector3") { lua_pushboolean(L, 0); return 1; }
	auto self = GetVector3(L, 1);
	auto Other = GetVector3(L, 2);
	lua_pushboolean(L, self == Other);
	return 1;
}
int Luna::Structs::Vector3::__gc(lua_State* L)
{
	auto self = GetV3Self(L);
	delete self;
	return 0;
}
#pragma endregion

int Luna::Structs::Vector3::Init(lua_State* L)
{
	lua_newtable(L);

	lua_pushstring(L, "__type");
	lua_pushstring(L, "Vector3");
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
	SetMeta(Project);
	SetMeta(Rotate);
	SetMeta(Normal);
	SetMeta(Nudge);
	SetMeta(ToInt);
	SetMeta(Unit);
	SetMeta(Lerp);
	SetMeta(To2D);


	LunaUtil::SetRegKey(L, "Vector3Meta", -1);
	return 0;
}