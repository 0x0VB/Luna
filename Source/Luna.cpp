#include "stdafx.h"
#include "Luna.h"

#include "LunaApi/LunaIO/LunaIO.h"
#include "LunaApi/LunaUtil/LunaUtil.h"
#include "LunaApi/LunaStructs/LunaStructs.h"
#include "LunaApi/LunaEvent/LunaEvent.h"
#include "LunaApi/LunaClass/LunaClass.h"

namespace Luna
{
	bool DebugMode = false;
	lua_State* GlobalLState = nullptr;
	LawnApp* App = nullptr;
	size_t FoundMods = 0;
	size_t LoadedMods = 0;
}

void Luna::InitiateLunaState()
{
	if (LUNA_STATE)
		lua_close(LUNA_STATE);
	LUNA_STATE = luaL_newstate();
	luaL_openlibs(LUNA_STATE);
}

std::filesystem::path ModsPath = "./Mods";

void Luna::Setup(bool DebugMode)
{
	Luna::DebugMode = DebugMode;	// Set DebugMode
	Luna::InitiateLunaState();		// Create Lua State at L
	Luna::App = LawnApp::GetApp();	// Get LawnApp

	LunaInit(LunaIO);				// Responsible for print/warn/info functions.
	LunaInit(LunaUtil);				// General-purpose lua functions that make dealing with lua easier.
	LunaInit(LunaStruct);			// Contains structs like Vector2, Rect, Color, etc.
	LunaInit(Luna::Event);			// Ports events onto lua, is also the main hooking lib.
	LunaInit(Luna::Class);			// Wraps C++ classes into lua, allowing user interaction.

	if (DebugMode)
		DebugMain();				// Run DebugMain
	if (std::filesystem::is_directory(ModsPath))
		LoadMods();
}

void Luna::LoadMods()
{
	for (const auto& entry : std::filesystem::directory_iterator(ModsPath))
	{
		const std::filesystem::path ModPath = ModsPath / entry.path().filename();
		if (ModPath.extension() != ".lua" && ModPath.extension() != ".luna")
			continue;
		Luna::FoundMods++;

		if (luaL_loadfile(LUNA_STATE, ModPath.string().c_str()) == LUA_ERRFILE)
		{
			std::cout << "LUA_ERRFILE on " << ModPath.string() << "\n";
			LunaIO::Print(lua_tostring(LUNA_STATE, -1), LunaIO::Error);
			return;
		}

		if (lua_pcall(LUNA_STATE, 0, 0, 0) != LUA_OK)
		{
			std::string ErrorMsg = std::format("[{}] ERROR MESSAGE:", ModPath.filename().string());
			LunaIO::Print(ErrorMsg.c_str(), LunaIO::Error);
			LunaIO::Print(lua_tostring(LUNA_STATE, -1), LunaIO::Error);
			Luna::App->Popup(
				std::format("There was an error while executing {} the mod! Please send the error message to the mod creator.", ModsPath.filename().string())
			);
		}
		else
			Luna::LoadedMods++;
	}
}


#pragma region LunaDebugIO
std::ofstream LUNA_BYTECODE;
int ModWriter(lua_State* L, const void* Buffer, size_t Size, void* Data)
{
	LUNA_BYTECODE.write((const char*)Buffer, Size); return 0;
}

void Luna::DebugMain()
{
	LunaIO::AllocateConsole();
	SetConsoleTitleA("LunaDebugIO");

	if (luaL_loadfile(GlobalLState, "LunaDev/Mod.lua") == LUA_ERRFILE)
	{
		std::cout << "LUA_ERRFILE" << "\n";
		LunaIO::Print(lua_tostring(GlobalLState, -1), LunaIO::Error);
		return;
	}
	
	// Dump Mod.luna (LuaC file 
	std::remove("Mod.luna");// Delete the old bytecode.
	LUNA_BYTECODE = std::ofstream("Mod.luna", std::ios::app | std::ios::binary);
	if (LUNA_BYTECODE.good()) {
		LUNA_BYTECODE.flush();
		lua_dump(GlobalLState, ModWriter, NULL, true);
		LUNA_BYTECODE.close();
	}
	else LunaIO::Print("Unable to write to Mod.luna. Debug information not stripped.", LunaIO::Error);

	std::cout << "Mod Function Loaded." << "\n";
	std::cout << "Luna Developer Mode Loaded\t\tV0.2.2\n\n";
	if (lua_pcall(LUNA_STATE, 0, 0, 0) != LUA_OK)
	{
		LunaIO::Print("ERROR MESSAGE:", LunaIO::Error);
		LunaIO::Print(lua_tostring(LUNA_STATE, -1), LunaIO::Error);
		Luna::App->Popup("There was an error while executing the mod! Please send the error message to the mod creator.");
	}
}
#pragma endregion