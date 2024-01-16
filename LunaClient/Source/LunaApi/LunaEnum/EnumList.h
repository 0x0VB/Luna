#pragma once
#include "LunaEnum.h"

namespace Enums
{
	using Luna::Enum::EnumLib;
	EnumLib* L_PlantBungeeState;
	EnumLib* L_ParticleEffects;
	EnumLib* L_PlantState;

	int Init(lua_State* L);
}