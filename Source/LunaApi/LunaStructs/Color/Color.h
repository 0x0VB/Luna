#pragma once
#include "PvZ/Definitions.h"

namespace Luna::Structs::Color
{
    int RGBConstructor(lua_State* L);
    int HSVConstructor(lua_State* L);
    int HexConstructor(lua_State* L);

    int __index(lua_State* L);
    int __newindex(lua_State* L);
    int __tostring(lua_State* L);

    int __add(lua_State* L);
    int __sub(lua_State* L);
    int __unm(lua_State* L);
    int __eq(lua_State* L);
    int __gc(lua_State* L);

    int Lerp(lua_State* L);
    int GetHex(lua_State* L);
    int Negate(lua_State* L);
    int GetHSVA(lua_State* L);
    int ShiftHue(lua_State* L);
    int Desaturate(lua_State* L);

    int Init(lua_State* L);
}

Color GetColor(int Idx);
Color* NewRGB(int R = 0, int G = 0, int B = 0, int A = 255);
Color* NewHSV(int H = 0, int S = 0, int V = 0, int A = 255);
Color* NewHex(std::string Hex);
Color* GetColorSelf();