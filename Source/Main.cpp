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
namespace Disp {}

// Lua Globals
#include "Include/lua.hpp"
lua_State* L;

// Luna Globals
CONST BOOL LUNA_DEBUG_MODE = TRUE;
BOOL LUNA_STATE_INIT = FALSE;
DWORD OLD_PROTECTION = 0;
DWORD* OLD = &OLD_PROTECTION;
std::ofstream LUNA_BYTECODE;

// Including Libraries
#include "Enums/Enums.h"
#include "PvZUtil/Main.hpp"
LawnApp* App;

#include "Luna/Luna.h"

void InitiateLunaState()
{
	if (LUNA_STATE_INIT) lua_close(L);
	L = luaL_newstate();
	luaL_openlibs(L);

	LUNA_STATE_INIT = TRUE;
}

int ModWriter(lua_State* L, const void* Buffer, size_t Size, void* Data)
{ LUNA_BYTECODE.write((const char*)Buffer, Size); return 0; }

class LunaListener : public Sexy::ButtonListener
{
	virtual void ButtonClick(int ID, int ClickType)
	{
		
	}
};

BOOL APIENTRY DllMain
(
	HMODULE ModHandle,
	DWORD  CallReason,
	LPVOID Reserved
)
{
	if (CallReason != DLL_PROCESS_ATTACH) return TRUE;
	VirtualProtect((LPVOID)0x400300, 0x1000, PAGE_EXECUTE_READWRITE, OLD);
	InitiateLunaState();// Create Lua State at L

	App = LawnApp::GetApp();// Get LawnApp

	// Load Mod.lua (Lua file)
	bool FunctionLoaded = false;
	int LoadResult = luaL_loadfile(L, "LunaDev/Mod.lua");
	if (LoadResult == LUA_OK) { FunctionLoaded = true; LunaIO::AllocateConsole(); }// If Mod.lua is found, then DevMode is enabled.
	else if (LoadResult != LUA_ERRFILE) { std::cout << "LUA_ERRFILE" << "\n"; LunaIO::Print(lua_tostring(L, -1), LunaIO::Error); return TRUE; }
	std::cout << "LawnApp: " << App << "\n";
	LunaInit(LunaIO); std::cout << "LunaIO Loaded.\n";// Responsible for print/warn/info functions.
	LunaInit(LunaUtil); std::cout << "LunaUtil Loaded.\n";// General-purpose lua functions that make dealing with lua easier.
	LunaInit(LunaStruct); std::cout << "LunaStruct Loaded.\n";// Contains structs like Vector2, Rect, Color, etc.
	LunaInit(Luna::Event); std::cout << "LunaEvent Loaded.\n";// Ports events onto lua, is also the main hooking lib.
	LunaInit(Luna::Class); std::cout << "LunaClass Loaded.\n";// Wraps C++ classes into lua, allowing user interaction.

	if (FunctionLoaded)
	{
		// Dump Mod.luna (LuaC file 
		std::remove("Mod.luna");// Delete the old bytecode.
		LUNA_BYTECODE = std::ofstream("Mod.luna", std::ios::app | std::ios::binary);
		if (LUNA_BYTECODE.good()) { LUNA_BYTECODE.flush(); lua_dump(L, ModWriter, NULL, true); LUNA_BYTECODE.close(); }
		else LunaIO::Print("Unable to write to Mod.luna. Debug information not stripped.", LunaIO::Error);
	}
	else
	{
		// Load Mod.luna
		LoadResult = luaL_loadfile(L, "Mod.luna");
		if (LoadResult != LUA_OK)
		{
			LunaIO::Print("Unable to find Mod.lua or Mod.luna.\n", LunaIO::Error);
			std::cout << lua_tostring(L, -1);
			return FALSE;
		}
	}

	std::cout << "Mod Function Loaded." << "\n"; system("cls");
	std::cout << "Luna Developer Mode Loaded\t\tV0.2.2\n\n";
	if (lua_pcall(L, 0, 0, 0) != LUA_OK)
	{
		LunaIO::Print("ERROR MESSAGE:", LunaIO::Error);
		LunaIO::Print(lua_tostring(L, -1), LunaIO::Error);
		App->Popup("There was an error while executing the mod! Please send the error message to the mod creator.");
	}

	std::cout << "[MOD]: Execution has halted!";
	return TRUE;
}