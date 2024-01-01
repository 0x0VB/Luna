#include "stdafx.h"
#include "Pad.h"

#include "LunaApi/LunaUtil/LunaUtil.h"
#include "LunaApi/LunaIO/LunaIO.h"
#include "Luna.h"

#pragma region Struct Functions
void Pad::Push() { NewPad(L, T, B, R); }
#pragma endregion

#pragma region C++ Functions
Pad GetPad(int Idx)
{
	AssertType(Idx, "Pad", "arg#" + std::to_string(Idx));
	return *(Pad*)lua_touserdata(LUNA_STATE, Idx);
}
Pad* NewPad(int X, int Y, int W, int H)
{
	auto New = (Pad*)lua_newuserdata(LUNA_STATE, sizeof(Pad));
	LunaUtil::Local("PadMeta");
	lua_setmetatable(LUNA_STATE, -2);

	New->L = X;
	New->T = Y;
	New->R = W;
	New->B = H;

	return New;
}
Pad* NewPad(int H, int V)
{
	auto New = (Pad*)lua_newuserdata(LUNA_STATE, sizeof(Pad));
	LunaUtil::Local("PadMeta");
	lua_setmetatable(LUNA_STATE, -2);

	New->L = H;
	New->T = V;
	New->R = H;
	New->B = V;

	return New;
}
Pad* NewPad(int P)
{
	auto New = (Pad*)lua_newuserdata(LUNA_STATE, sizeof(Pad));
	LunaUtil::Local("PadMeta");
	lua_setmetatable(LUNA_STATE, -2);

	New->L = P;
	New->T = P;
	New->R = P;
	New->B = P;

	return New;
}
Pad* GetPadSelf() { return (Pad*)lua_touserdata(LUNA_STATE, 1); }
#pragma endregion

#pragma region Lua Functions
int Luna::Structs::Pad::Constructor(lua_State* L)
{
	int T = lua_gettop(L);
	switch (T)
	{
	case 0:
	case 1:
		NewPad(GetInt(1));
		return 1;
	case 2:
		NewPad(GetInt(1), GetInt(2));
		return 1;
	}
	NewPad(GetInt(1), GetInt(2), GetInt(3), GetInt(4));
	return 1;
}
int Luna::Structs::Pad::Lerp(lua_State* L)
{
	auto self = GetPad(1);
	auto Other = GetPad(2);
	auto Alpha = GetFloat(3, 0.5);
	self.Lerp(Other, Alpha).Push();
	return 1;
}
#pragma endregion

#pragma region Meta Methods
int Luna::Structs::Pad::__index(lua_State* L)
{
	auto self = GetPadSelf();
	auto Field = GetString(2);

	if (Field.length() != 1) goto FIDX;
	switch (Field[0])
	{
	case 'L':
		lua_pushinteger(L, self->L);
		return 1;
	case 'T':
		lua_pushinteger(L, self->T);
		return 1;
	case 'R':
		lua_pushinteger(L, self->R);
		return 1;
	case 'B':
		lua_pushinteger(L, self->B);
		return 1;
	default:
		LunaIO::ThrowError(Field + " is not a valid member of Pad.");
	}
FIDX:
	LunaUtil::Local("PadMeta");
	lua_pushvalue(L, 2);
	lua_gettable(L, -2);
	if (lua_isnil(L, -1)) LunaIO::ThrowError(Field + " is not a valid member of Pad.");
	return 1;
}
int Luna::Structs::Pad::__newindex(lua_State* L)
{
	if (!lua_isnumber(L, 3)) LunaIO::ThrowError("Pad only accepts number fields.");
	auto self = GetPadSelf();
	auto Field = GetString(2);
	auto Value = GetInt(3);
	if (Field.length() != 1) LunaIO::ThrowError(Field + " is not a valid member of Pad or is read-only.");
	switch (Field[0])
	{
	case 'L':
		self->L = Value;
		return 0;
	case 'T':
		self->T = Value;
		return 0;
	case 'R':
		self->R = Value;
		return 0;
	case 'B':
		self->B = Value;
		return 0;
	}
	LunaIO::ThrowError(Field + " is not a valid member of Pad or is read-only.");
	return 0;
}
int Luna::Structs::Pad::__tostring(lua_State* L)
{
	auto self = GetPadSelf();
	std::string ToStr =
		"Left: " + std::to_string(self->L) + 
		" Top: " + std::to_string(self->T) +
		" Right: " + std::to_string(self->R) +
		" Bottom: " + std::to_string(self->B);
	lua_pushstring(L, ToStr.c_str());
	return 1;
}

int Luna::Structs::Pad::__add(lua_State* L)
{
	auto OType = LunaUtil::Type(2);
	if (OType != "Pad") LunaIO::ThrowError("Unable to add Pad and " + OType + ".");

	auto self = GetPad(1);
	auto Other = GetPad(2);
	(self + Other).Push();
	return 1;
}
int Luna::Structs::Pad::__sub(lua_State* L)
{
	auto OType = LunaUtil::Type(2);
	if (OType != "Pad") LunaIO::ThrowError("Unable to subtract " + OType + " from Pad.");

	auto self = GetPad(1);
	auto Other = GetPad(2);
	(self - Other).Push();
	return 1;
}
int Luna::Structs::Pad::__mul(lua_State* L)
{
	if (!lua_isnumber(L, 2)) LunaIO::ThrowError("Unable to multiply Pad by " + LunaUtil::Type(2) + ".");

	auto self = GetPad(1);
	auto Factor = (float)lua_tonumber(L, 2);
	(self * Factor).Push();
	return 1;
}
int Luna::Structs::Pad::__div(lua_State* L)
{
	if (!lua_isnumber(L, 2)) LunaIO::ThrowError("Unable to divide Pad by " + LunaUtil::Type(2) + ".");

	auto self = GetPad(1);
	auto Factor = (float)lua_tonumber(L, 2);
	(self / Factor).Push();
	return 1;
}
int Luna::Structs::Pad::__eq(lua_State* L)
{
	if (LunaUtil::Type(2) != "Pad") { lua_pushboolean(L, false); return 1; }

	auto self = GetPad(1);
	auto Other = GetPad(2);
	lua_pushboolean(L, self == Other);
	return 1;
}
int Luna::Structs::Pad::__gc(lua_State* L)
{
	auto self = GetPadSelf();
	delete self;
	return 0;
}
#pragma endregion

int Luna::Structs::Pad::Init(lua_State* L)
{
	lua_newtable(L);

	lua_pushstring(L, "__type");
	lua_pushstring(L, "Pad");
	lua_settable(L, -3);

	SetMeta(__index);
	SetMeta(__newindex);
	SetMeta(__tostring);

	SetMeta(__add);
	SetMeta(__sub);
	SetMeta(__mul);
	SetMeta(__div);
	SetMeta(__eq);
	SetMeta(Lerp);

	LunaUtil::Local("PadMeta", -1);
	return 0;
}