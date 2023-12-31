#pragma once
#include "Include/lua.h"
#include "PvZ/LawnApp.h"

#define LUNA_STATE Luna::GlobalLState

namespace Luna
{
	extern bool DebugMode;
	extern lua_State* GlobalLState;
	extern LawnApp* App;
	extern size_t FoundMods;
	extern size_t LoadedMods;

	void LoadMods();
	void DebugMain();

	void InitiateLunaState();

	void Setup(bool DebugMode = false);
}