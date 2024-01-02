#include "stdafx.h"
#include "Color.h"

#include "LunaApi/LunaUtil/LunaUtil.h"
#include "LunaApi/LunaIO/LunaIO.h"
#include "Luna.h"

#pragma region Struct Functions
void Color::Push(lua_State* L) { NewRGB(L, R, G, B, A); }
#pragma endregion

#pragma region C++ Functions
Color GetColor(lua_State* L, int Idx)
{
	AssertType(L, Idx, "Color", "arg#" + std::to_string(Idx));
	return *(Color*)lua_touserdata(L, Idx);
}
Color* NewRGB(lua_State* L, int R, int G, int B, int A)
{
	auto New = (Color*)lua_newuserdata(LUNA_STATE, sizeof(Color));
	LunaUtil::Local(L, "ColorMeta");
	lua_setmetatable(LUNA_STATE, -2);

	New->R = R;
	New->G = G;
	New->B = B;
	New->A = A;

	return New;
}
Color* NewHSV(lua_State* L, int H, int S, int V, int A)
{
	auto RGBA = Color::FromHSVA(H, S, V, 0);
	auto New = (Color*)lua_newuserdata(L, sizeof(Color));
	LunaUtil::Local(L, "ColorMeta");
	lua_setmetatable(L, -2);

	New->R = RGBA.R;
	New->G = RGBA.G;
	New->B = RGBA.B;
	New->A = A;

	return New;
}
Color* NewHex(lua_State* L, std::string Hex)
{
	auto RGBA = Color::FromHex(Hex);
	auto New = (Color*)lua_newuserdata(L, sizeof(Color));
	LunaUtil::Local(L, "ColorMeta");
	lua_setmetatable(L, -2);

	New->R = RGBA.R;
	New->G = RGBA.G;
	New->B = RGBA.B;
	New->A = RGBA.A;

	return New;
}
Color* GetColorSelf(lua_State* L) { return (Color*)lua_touserdata(L, 1); }
#pragma endregion

#pragma region Lua Functions
int Luna::Structs::Color::RGBConstructor(lua_State* L)
{
	auto R = GetInt(L, 1, 0);
	auto G = GetInt(L, 2, 0);
	auto B = GetInt(L, 3, 0);
	auto A = GetInt(L, 4, 255);
	NewRGB(L, R, G, B, A);
	return 1;
}
int Luna::Structs::Color::HSVConstructor(lua_State* L)
{
	auto H = GetInt(L, 1, 0);
	auto S = GetInt(L, 2, 0);
	auto V = GetInt(L, 3, 0);
	auto A = GetInt(L, 4, 255);
	NewHSV(L, H, S, V, A);
	return 1;
}
int Luna::Structs::Color::HexConstructor(lua_State* L)
{
	auto Hex = GetString(L, 1, "000");
	NewHex(L, Hex);
	return 1;
}

int Luna::Structs::Color::Lerp(lua_State* L)
{
	auto self = GetColor(L, 1);
	auto Other = GetColor(L, 2);
	auto Alpha = GetFloat(L, 3, 0.5);
	self.Lerp(Other, Alpha).Push(L);
	return 1;
}
int Luna::Structs::Color::GetHex(lua_State* L)
{
	auto self = GetColor(L, 1);
	lua_pushstring(L, self.GetHex().c_str());
	return 1;
}
int Luna::Structs::Color::Negate(lua_State* L)
{
	auto self = GetColor(L, 1);
	self.Negate().Push(L);
	return 1;
}
int Luna::Structs::Color::GetHSVA(lua_State* L)
{
	auto self = GetColor(L, 1);
	auto HSVA = self.GetHSVA();
	lua_pushinteger(L, HSVA.R);
	lua_pushinteger(L, HSVA.G);
	lua_pushinteger(L, HSVA.B);
	lua_pushinteger(L, HSVA.A);
	return 4;
}
int Luna::Structs::Color::ShiftHue(lua_State* L)
{
	auto self = GetColor(L, 1);
	auto Amount = GetInt(L, 2);
	self.ShiftHue(Amount).Push(L);
	return 1;
}
int Luna::Structs::Color::Desaturate(lua_State* L)
{
	auto self = GetColor(L, 1);
	self.Desaturate().Push(L);
	return 1;
}
#pragma endregion


#pragma region Meta Methods
int Luna::Structs::Color::__index(lua_State* L)
{
	auto self = GetColorSelf(L);
	auto Field = GetString(L, 2);

	if (Field.length() != 1) goto FIDX;
	switch (Field[0])
	{
	case 'R':
		lua_pushinteger(L, self->R);
		return 1;
	case 'G':
		lua_pushinteger(L, self->G);
		return 1;
	case 'B':
		lua_pushinteger(L, self->B);
		return 1;
	case 'A':
		lua_pushinteger(L, self->A);
		return 1;
	case 'H':
		lua_pushinteger(L, self->GetHue());
		return 1;
	case 'S':
		lua_pushinteger(L, self->GetSaturation());
		return 1;
	case 'V':
		lua_pushinteger(L, self->GetValue());
		return 1;
	default:
		LunaIO::ThrowError(L, Field + " is not a valid member of Color.");
	}
FIDX:
	LunaUtil::Local(L, "ColorMeta");
	lua_pushvalue(L, 2);
	lua_gettable(L, -2);
	if (lua_isnil(L, -1)) LunaIO::ThrowError(L, Field + " is not a valid member of Color.");
	return 1;
}
int Luna::Structs::Color::__newindex(lua_State* L)
{
	if (!lua_isnumber(L, 3)) LunaIO::ThrowError(L, "Color only accepts number fields.");
	auto self = GetColorSelf(L);
	auto Field = GetString(L, 2);
	auto Value = GetInt(L, 3);
	if (Field.length() != 1) LunaIO::ThrowError(L,  Field + " is not a valid member of Color or is read-only.");
	switch (Field[0])
	{
	case 'R':
		self->R = Value;
		return 0;
	case 'G':
		self->G = Value;
		return 0;
	case 'B':
		self->B = Value;
		return 0;
	case 'A':
		self->A = Value;
		return 0;
	case 'H':
	case 'S':
	case 'V':
		LunaIO::ThrowError(L, "HSV values are read-only.");
	}
	LunaIO::ThrowError(L, Field + " is not a valid member of Color or is read-only.");
	return 0;
}
int Luna::Structs::Color::__tostring(lua_State* L)
{
	auto self = GetColorSelf(L);
	std::string ToStr =
		"Color(" + std::to_string(self->R) + ", " +
		std::to_string(self->G) + ", " +
		std::to_string(self->B) + ", " +
		std::to_string(self->A) + ")";
	lua_pushstring(L, ToStr.c_str());
	return 1;
}

int Luna::Structs::Color::__add(lua_State* L)
{
	auto OType = LunaUtil::Type(L, 2);
	if (OType != "Color") LunaIO::ThrowError(L, "Unable to add Color and " + OType + ".");

	auto self = GetColor(L, 1);
	auto Other = GetColor(L, 2);
	(self + Other).Push(L);
	return 1;
}
int Luna::Structs::Color::__sub(lua_State* L)
{
	auto OType = LunaUtil::Type(L, 2);
	if (OType != "Color") LunaIO::ThrowError(L, "Unable to subtract " + OType + " from Color.");

	auto self = GetColor(L, 1);
	auto Other = GetColor(L, 2);
	(self - Other).Push(L);
	return 1;
}
int Luna::Structs::Color::__unm(lua_State* L)
{
	auto self = GetColorSelf(L);
	self->Negate().Push(L);
	return 1;
}
int Luna::Structs::Color::__eq(lua_State* L)
{
	if (LunaUtil::Type(L, 2) != "Color") { lua_pushboolean(L, false); return 1; }

	auto self = GetColor(L, 1);
	auto Other = GetColor(L, 2);
	lua_pushboolean(L, self == Other);
	return 1;
}
int Luna::Structs::Color::__gc(lua_State* L)
{
	auto self = GetColorSelf(L);
	delete self;
	return 0;
}
#pragma endregion

int Luna::Structs::Color::Init(lua_State* L)
{
	lua_newtable(L);

	lua_pushstring(L, "__type");
	lua_pushstring(L, "Color");
	lua_settable(L, -3);

	SetMeta(__index);
	SetMeta(__newindex);
	SetMeta(__tostring);

	SetMeta(__add);
	SetMeta(__sub);
	SetMeta(__unm);
	SetMeta(__eq);

	SetMeta(Lerp);
	SetMeta(GetHex);
	SetMeta(Negate);
	SetMeta(GetHSVA);
	SetMeta(ShiftHue);
	SetMeta(Desaturate);

	LunaUtil::Local(L, "ColorMeta", -1);

	return 0;
}