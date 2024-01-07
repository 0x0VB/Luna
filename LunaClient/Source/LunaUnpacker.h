#pragma once

#include "Luau/lua.h"
#include "LunaFile.h"

namespace Luna
{
	bool LoadCompressedBytecode(lua_State* L, LunaStatic::LunaFile* LunaMod, size_t Index = 0);
}