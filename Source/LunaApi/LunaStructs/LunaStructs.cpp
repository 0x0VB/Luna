#include "stdafx.h"
#include "LunaStructs.h"

#include "LunaApi/LunaUtil/LunaUtil.h"

int LunaStruct::Init(lua_State* L)
{
	LunaInit(Vector2);
	LunaInit(Vector3);
	LunaInit(Color);
	LunaInit(Rect);
	LunaInit(Pad);

	return 0;
}