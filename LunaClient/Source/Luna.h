#pragma once
#include <filesystem>

#include "PvZ/LawnApp.h"

#include "Luau/Compiler.h"

#define LUNA_STATE Luna::GlobalLState

namespace Luna
{
	extern bool DebugMode;
	extern lua_State* GlobalLState;
	extern LawnApp* App;
	extern size_t FoundMods;
	extern size_t LoadedMods;
	extern Luau::CompileOptions CompileOptions;
	extern void* AbstractEnums;


	void LoadScript(lua_State* L, std::filesystem::path ScriptPath);
	void LoadLuna(lua_State* L, std::filesystem::path LunaPath);
	void LoadMods();
	
	void DebugMain();

	void InitiateLunaState();
	void InitializeCompileOptions();

	bool LoadFile(lua_State* L, std::filesystem::path ModPath);
	void Tick();

	void Setup(bool DebugMode = false);
}