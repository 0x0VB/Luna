#include <corecrt_math_defines.h>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <thread>
#include <cmath>
#include <list>
#include <map>
#include <set>
#include <format>
#include <filesystem>

// Including Libraries
#include "Include/lua.hpp"
#include "Enums/Enums.h"
#include "PvZUtil/include.h" // LawnApp* App;

// Luna core
lua_State* L = nullptr;		// lua_State* L; must be defined before including Luna.h because it's used as global state...
LawnApp* App = nullptr;		// LawnApp* App; must be defined before including Luna.h because it's used as global variable...
#include "Luna/include.h"		

// Luna Globals
CONST BOOL LUNA_DEBUG_MODE = TRUE;
BOOL LUNA_STATE_INIT = FALSE;

std::filesystem::path ModsPath = "./Mods";
size_t LOADED_MODS = 0;
size_t FOUND_MODS = 0;

void DebugMain();
void LoadMods();

void InitiateLunaState()
{
	if (LUNA_STATE_INIT) lua_close(L);
	L = luaL_newstate();
	luaL_openlibs(L);

	LUNA_STATE_INIT = TRUE;
}

void Setup()
{
	InitiateLunaState();		// Create Lua State at L
	App = LawnApp::GetApp();	// Get LawnApp
	if (LUNA_DEBUG_MODE)
		DebugMain();			// Run DebugMain

	if (std::filesystem::is_directory(ModsPath))
		LoadMods();
}

void LoadMods()
{
	for (const auto& entry : std::filesystem::directory_iterator(ModsPath))
	{
		const std::filesystem::path ModPath = ModsPath / entry.path().filename();
		if (ModPath.extension() != ".lua")
			continue;
		FOUND_MODS++;

		if (luaL_loadfile(L, ModPath.string().c_str()) == LUA_ERRFILE)
		{
			std::cout << "LUA_ERRFILE on " << ModPath.string() << "\n";
			LunaIO::Print(lua_tostring(L, -1), LunaIO::Error);
			return;
		}

		if (lua_pcall(L, 0, 0, 0) != LUA_OK)
		{
			std::string ErrorMsg = std::format("[{}] ERROR MESSAGE:", ModPath.filename().string());
			LunaIO::Print(ErrorMsg.c_str(), LunaIO::Error);
			LunaIO::Print(lua_tostring(L, -1), LunaIO::Error);
			App->Popup(
				std::format("There was an error while executing {} the mod! Please send the error message to the mod creator.", ModsPath.filename().string())
			);
		}
		else
			LOADED_MODS++;
	}
}

BOOL APIENTRY DllMain
(
	HMODULE ModHandle,
	DWORD  CallReason,
	LPVOID Reserved
)
{
	switch (CallReason)
	{
	case DLL_PROCESS_ATTACH:
	{
		Setup();
		return TRUE;
	}
	default:
		return TRUE;
	}
}

#pragma region LunaDebugIO
std::ofstream LUNA_BYTECODE;
int ModWriter(lua_State* L, const void* Buffer, size_t Size, void* Data)
{
	LUNA_BYTECODE.write((const char*)Buffer, Size); return 0;
}

void DebugMain()
{
	LunaIO::AllocateConsole();
	SetConsoleTitleA("LunaDebugIO");

	if (luaL_loadfile(L, "LunaDev/Mod.lua") == LUA_ERRFILE)
	{
		std::cout << "LUA_ERRFILE" << "\n";
		LunaIO::Print(lua_tostring(L, -1), LunaIO::Error);
		return;
	}

	// Load Mod.lua (Lua file)
	std::cout << "LawnApp: " << App << "\n";
	LunaInit(LunaIO); std::cout << "LunaIO Loaded.\n";			// Responsible for print/warn/info functions.
	LunaInit(LunaUtil); std::cout << "LunaUtil Loaded.\n";		// General-purpose lua functions that make dealing with lua easier.
	LunaInit(LunaStruct); std::cout << "LunaStruct Loaded.\n";	// Contains structs like Vector2, Rect, Color, etc.
	LunaInit(Luna::Event); std::cout << "LunaEvent Loaded.\n";	// Ports events onto lua, is also the main hooking lib.
	LunaInit(Luna::Class); std::cout << "LunaClass Loaded.\n";	// Wraps C++ classes into lua, allowing user interaction.

	// Dump Mod.luna (LuaC file 
	std::remove("Mod.luna");// Delete the old bytecode.
	LUNA_BYTECODE = std::ofstream("Mod.luna", std::ios::app | std::ios::binary);
	if (LUNA_BYTECODE.good()) { 
		LUNA_BYTECODE.flush();
		lua_dump(L, ModWriter, NULL, true);
		LUNA_BYTECODE.close();
	}
	else LunaIO::Print("Unable to write to Mod.luna. Debug information not stripped.", LunaIO::Error);

	std::cout << "Mod Function Loaded." << "\n"; // system("cls");
	std::cout << "Luna Developer Mode Loaded\t\tV0.2.2\n\n";
	if (lua_pcall(L, 0, 0, 0) != LUA_OK)
	{
		LunaIO::Print("ERROR MESSAGE:", LunaIO::Error);
		LunaIO::Print(lua_tostring(L, -1), LunaIO::Error);
		App->Popup("There was an error while executing the mod! Please send the error message to the mod creator.");
	}

	std::cout << "[MOD]: Execution has halted!" << std::endl;
}


/*
class LunaListener : public Sexy::ButtonListener
{
	virtual void ButtonClick(int ID, int ClickType)
	{

	}
};
*/
#pragma endregion