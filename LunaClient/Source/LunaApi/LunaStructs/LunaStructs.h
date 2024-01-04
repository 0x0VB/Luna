#pragma once
#include "Luau/lua.h"

#define LunaStruct Luna::Structs
namespace LunaStruct {
	int Init(lua_State* L);
};

#include "Vector2/Vector2.h"
#include "Vector3/Vector3.h"
#include "Color/Color.h"
#include "Rect/Rect.h"
#include "Pad/Pad.h"