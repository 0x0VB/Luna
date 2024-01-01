#include "stdafx.h"
#include "LunaStructs.h"

#include "LunaApi/LunaUtil/LunaUtil.h"

const luaL_Reg StructFunc[] = {
	{"Color", LunaStruct::Color::RGBConstructor},
	{"ColorRGB", LunaStruct::Color::RGBConstructor},
	{"ColorHSV", LunaStruct::Color::HSVConstructor},
	{"ColorHex", LunaStruct::Color::HexConstructor},

	{"Rect",	LunaStruct::Rect::Constructor},
	{"Pad",		LunaStruct::Pad::Constructor},
	{"Vector2", LunaStruct::Vector2::Constructor},
	{"Vector3", LunaStruct::Vector3::Constructor},

    {NULL, NULL},
};

int LunaStruct::Init(lua_State* L)
{
	LunaInit(Vector2);
	LunaInit(Vector3);
	LunaInit(Color);
	LunaInit(Rect);
	LunaInit(Pad);

	luaL_register(L, "_G", StructFunc);
	return 0;
}