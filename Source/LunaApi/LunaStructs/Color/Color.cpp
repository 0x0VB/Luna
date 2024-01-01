#include "stdafx.h"
#include "Color.h"

#include "LunaApi/LunaUtil/LunaUtil.h"
#include "LunaApi/LunaIO/LunaIO.h"
#include "Luna.h"

#pragma region Struct Functions
void Color::Push() { NewRGB(R, G, B, A); }
#pragma endregion

#pragma region C++ Functions
Color GetColor(int Idx)
{
	AssertType(Idx, "Color", "arg#" + std::to_string(Idx));
	return *(Color*)lua_touserdata(LUNA_STATE, Idx);
}
Color* NewRGB(int R, int G, int B, int A)
{
	auto New = (Color*)lua_newuserdata(LUNA_STATE, sizeof(Color));
	LunaUtil::Local("ColorMeta");
	lua_setmetatable(LUNA_STATE, -2);

	New->R = R;
	New->G = G;
	New->B = B;
	New->A = A;

	return New;
}
Color* NewHSV(int H, int S, int V, int A)
{
	auto RGBA = Color::FromHSVA(H, S, V, 0);
	auto New = (Color*)lua_newuserdata(LUNA_STATE, sizeof(Color));
	LunaUtil::Local("ColorMeta");
	lua_setmetatable(LUNA_STATE, -2);

	New->R = RGBA.R;
	New->G = RGBA.G;
	New->B = RGBA.B;
	New->A = A;

	return New;
}
Color* NewHex(std::string Hex)
{
	auto RGBA = Color::FromHex(Hex);
	auto New = (Color*)lua_newuserdata(LUNA_STATE, sizeof(Color));
	LunaUtil::Local("ColorMeta");
	lua_setmetatable(LUNA_STATE, -2);

	New->R = RGBA.R;
	New->G = RGBA.G;
	New->B = RGBA.B;
	New->A = RGBA.A;

	return New;
}
Color* GetColorSelf() { return (Color*)lua_touserdata(LUNA_STATE, 1); }
#pragma endregion

#pragma region Lua Functions
int Luna::Structs::Color::RGBConstructor(lua_State* L)
{
	auto R = GetInt(1, 0);
	auto G = GetInt(2, 0);
	auto B = GetInt(3, 0);
	auto A = GetInt(4, 255);
	NewRGB(R, G, B, A);
	return 1;
}
int Luna::Structs::Color::HSVConstructor(lua_State* L)
{
	auto H = GetInt(1, 0);
	auto S = GetInt(2, 0);
	auto V = GetInt(3, 0);
	auto A = GetInt(4, 255);
	NewHSV(H, S, V, A);
	return 1;
}
int Luna::Structs::Color::HexConstructor(lua_State* L)
{
	auto Hex = GetString(1, "#000");
	NewHex(Hex);
	return 1;
}

int Luna::Structs::Color::Lerp(lua_State* L)
{
	auto self = GetColor(1);
	auto Other = GetColor(2);
	auto Alpha = GetFloat(3, 0.5);
	self.Lerp(Other, Alpha).Push();
	return 1;
}
int Luna::Structs::Color::GetHex(lua_State* L)
{
	auto self = GetColor(1);
	lua_pushstring(L, self.GetHex().c_str());
	return 1;
}
int Luna::Structs::Color::Negate(lua_State* L)
{
	auto self = GetColor(1);
	self.Negate().Push();
	return 1;
}
int Luna::Structs::Color::GetHSVA(lua_State* L)
{
	auto self = GetColor(1);
	auto HSVA = self.GetHSVA();
	lua_pushinteger(L, HSVA.R);
	lua_pushinteger(L, HSVA.G);
	lua_pushinteger(L, HSVA.B);
	lua_pushinteger(L, HSVA.A);
	return 4;
}
int Luna::Structs::Color::ShiftHue(lua_State* L)
{
	auto self = GetColor(1);
	auto Amount = GetInt(2);
	self.ShiftHue(Amount).Push();
	return 1;
}
int Luna::Structs::Color::Desaturate(lua_State* L)
{
	auto self = GetColor(1);
	self.Desaturate().Push();
	return 1;
}
#pragma endregion


#pragma region Meta Methods
int Luna::Structs::Color::__index(lua_State* L)
{
	auto self = GetColorSelf();
	auto Field = GetString(2);

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
		LunaIO::ThrowError(Field + " is not a valid member of Color.");
	}
FIDX:
	LunaUtil::Local("ColorMeta");
	lua_pushvalue(L, 2);
	lua_gettable(L, -2);
	if (lua_isnil(L, -1)) LunaIO::ThrowError(Field + " is not a valid member of Color.");
	return 1;
}
int Luna::Structs::Color::__newindex(lua_State* L)
{
	if (!lua_isnumber(L, 3)) LunaIO::ThrowError("Color only accepts number fields.");
	auto self = GetColorSelf();
	auto Field = GetString(2);
	auto Value = GetInt(3);
	if (Field.length() != 1) LunaIO::ThrowError(Field + " is not a valid member of Color or is read-only.");
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
		LunaIO::ThrowError("HSV values are read-only.");
	}
	LunaIO::ThrowError(Field + " is not a valid member of Color or is read-only.");
	return 0;
}
int Luna::Structs::Color::__tostring(lua_State* L)
{
	auto self = GetColorSelf();
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
	auto OType = LunaUtil::Type(2);
	if (OType != "Color") LunaIO::ThrowError("Unable to add Color and " + OType + ".");

	auto self = GetColor(1);
	auto Other = GetColor(2);
	(self + Other).Push();
	return 1;
}
int Luna::Structs::Color::__sub(lua_State* L)
{
	auto OType = LunaUtil::Type(2);
	if (OType != "Color") LunaIO::ThrowError("Unable to subtract " + OType + " from Color.");

	auto self = GetColor(1);
	auto Other = GetColor(2);
	(self - Other).Push();
	return 1;
}
int Luna::Structs::Color::__unm(lua_State* L)
{
	auto self = GetColorSelf();
	self->Negate().Push();
	return 1;
}
int Luna::Structs::Color::__eq(lua_State* L)
{
	if (LunaUtil::Type(2) != "Color") { lua_pushboolean(L, false); return 1; }

	auto self = GetColor(1);
	auto Other = GetColor(2);
	lua_pushboolean(L, self == Other);
	return 1;
}
int Luna::Structs::Color::__gc(lua_State* L)
{
	auto self = GetColorSelf();
	delete self;
	return 0;
}
#pragma endregion

int Luna::Structs::Color::Init(lua_State* L)
{
#define SetMeta(Function) lua_pushstring(L, #Function); lua_pushcclosure(L, Function, 0); lua_settable(L, -3)
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

	LunaUtil::Local("ColorMeta", -1);
	lua_register(L, "Color", RGBConstructor);
	lua_register(L, "RGB", RGBConstructor);
	lua_register(L, "HSV", HSVConstructor);
	lua_register(L, "Hex", HexConstructor);

	return 0;
}