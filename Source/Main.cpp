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

LawnApp* App;

BOOL Added;
CONST DWORD RetPt = 0x00538fd7;
Sexy::Graphics* G;
LawnStoneButton* Btn;
Color TC = Color::FromHex("#00F");
Sexy::Image* TestI = NULL;
const PopString& Nm =  PopString("0xVB");
void __declspec(naked) Test()
{
	__asm
	{
		pushad
		mov G, eax
	}
	if (!App->Loaded || Added) goto Exit;
	App->UIRoot->AddChild(Btn);
	Added = true;

Exit:
	__asm
	{
		popad
		mov [esp+184], 01
		jmp RetPt
	}
}

class LunaListener : public Sexy::ButtonListener
{
	virtual void ButtonClick(int ID, int ClickType)
	{
		DWORD Entry = { 0x447b00 };
		auto Event = Luna::Event::LunaEvent::New("StoneDraw", StoneButtonDrawHandler, &Entry, 1, true);
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

	LunaInit(LunaIO); std::cout << "LunaIO Loaded.\n";// Responsible for print/warn/info functions.
	LunaInit(LunaUtil); std::cout << "LunaUtil Loaded.\n";// General-purpose lua functions that make dealing with lua easier.
	LunaInit(LunaStruct); std::cout << "LunaStruct Loaded.\n";// Contains structs like Vector2, Rect, Color, etc.
	LunaInit(Luna::Event); std::cout << "LunaEvent Loaded.\n";// Ports events onto lua, is also the main hooking lib.

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
	std::cout << "Mod Function Loaded." << "\n";
	std::cout << "Luna Developer Mode Loaded\t\tV0.2.1\n";
	if (lua_pcall(L, 0, 0, 0) != LUA_OK) LunaIO::Print(lua_tostring(L, -1), LunaIO::Error);
	// Call the Mod main function and print errors.
	// uniqua: hello
	// Debugging Code Starts Here
	App->WindowBounds = IRect(0, 0, 800, 700);// Expand window bounds to test LawnApp
	Btn = LawnStoneButton::New(0, new LunaListener(), "Luna!");// Create new button (can't parent it yet because img resources to render it aren't loaded)
	Btn->Bounds = IRect(0, 0, 200, 46);// Set button size

	CONST DWORD Entries = { 0x00538fcf };
	auto Event = Luna::Event::LunaEvent::New("Update", Test, &Entries, 1, true);// Connect the Test function to the LawnApp update function
	// This uses the LunaEvent lib to create a hook at 0x00538fcf
	
	return TRUE;
}