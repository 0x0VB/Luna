#include "stdafx.h"
#include "Luna.h"

#include "LunaApi/LunaApi.h"
#include "LunaApi/LunaIO/LunaIO.h"
#include "LunaApi/LunaUtil/LunaUtil.h"

#include "Common.h"
#include "LunaFile.h"

#include "LunaUnpacker.h"

namespace Luna
{
	bool DebugMode = false;
	lua_State* GlobalLState = nullptr;
	LawnApp* App = nullptr;
	size_t FoundMods = 0;
	size_t LoadedMods = 0;
	Luau::CompileOptions CompileOptions = {};
}

std::filesystem::path ModsPath = "./Mods";
void Luna::Setup(bool DebugMode)
{
	Luna::DebugMode = DebugMode;	// Set DebugMode
	Luna::InitiateLunaState();		// Create Lua State at L
	Luna::InitializeCompileOptions();
	Luna::App = LawnApp::GetApp();	// Get LawnApp

	if (DebugMode)
		DebugMain();				// Run DebugMain
	if (std::filesystem::is_directory(ModsPath))
		LoadMods();
}

bool Luna::LoadFile(lua_State* L, std::filesystem::path ModPath)
{
	const auto Source = LunaStatic::ReadFile(ModPath);

	std::string chunkname = "=" + ModPath.filename().string();
	std::string bytecode = Luau::compile(Source.c_str(), Luna::CompileOptions);

	return luau_load(L, chunkname.c_str(), bytecode.data(), bytecode.size(), 0) == 0;
}


#include "LunaApi/LunaClass/Classes/LawnAppClass.h"
void Luna::LoadScript(lua_State* L, std::filesystem::path ScriptPath)
{
	if (!LoadFile(L, ScriptPath))
	{
		std::cout << "LUA_ERRFILE on " << ScriptPath.string() << "\n";
		LunaIO::Print(lua_tostring(L, -1), LunaIO::Error);
		return;
	}

	// register LawnApp
	lua_getref(L, Luna::Class::LunaApp::LunaInstanceRef);
	lua_setglobal(L, "LawnApp");

	if (lua_pcall(L, 0, 0, 0) != LUA_OK)
	{
		std::string ErrorMsg = std::format("[{}] ERROR MESSAGE: ", ScriptPath.filename().string());
		LunaIO::Print(ErrorMsg.c_str(), LunaIO::Error);
		LunaIO::Print(lua_tostring(L, -1), LunaIO::Error);
	}
	else
		Luna::LoadedMods++;
}

void Luna::LoadLuna(lua_State* L, std::filesystem::path LunaPath)
{
	auto LunaMod = LunaStatic::LunaFile::LoadFile(LunaPath);
	if (!LunaMod.IsValid())
	{
		std::cout << "Can't load invalid luna file on " << LunaPath.string() << "\n";
		return;
	}

	if (!LoadCompressedBytecode(L, &LunaMod))
	{
		std::cout << "Can't load bytecode on " << LunaPath.string() << "\n";
		if (lua_gettop(L) > 0)
			LunaIO::Print(lua_tostring(L, -1), LunaIO::Error);
		return;
	}

	if (lua_pcall(L, 0, 0, 0) != LUA_OK)
	{
		std::string ErrorMsg = std::format("[{}] ERROR MESSAGE: ", LunaPath.filename().string());
		LunaIO::Print(ErrorMsg.c_str(), LunaIO::Error);
		LunaIO::Print(lua_tostring(L, -1), LunaIO::Error);
	}
	else
		Luna::LoadedMods++;
}

void Luna::LoadMods()
{
	for (const auto& entry : std::filesystem::directory_iterator(ModsPath))
	{
		const std::filesystem::path ModPath = ModsPath / entry.path().filename();
		const auto Extension = ModPath.extension();
		if (Extension != ".lua" && Extension != ".luna")
			continue;

		Luna::FoundMods++;

		lua_State* L = lua_newthread(LUNA_STATE);	// module needs to run in a new thread, isolated from the rest
		luaL_sandboxthread(L);						// new thread needs to have the globals sandboxed

		if (Extension == ".lua")
		{
			LoadScript(L, ModPath);
		}
		else
		{
			LoadLuna(L, ModPath);
		}
	}
}

void Luna::InitiateLunaState()
{
	if (LUNA_STATE)
		lua_close(LUNA_STATE);
	LUNA_STATE = luaL_newstate();

	LunaInit(LunaApi);
}

void Luna::InitializeCompileOptions()
{
	if (Luna::DebugMode)
	{
		Luna::CompileOptions.debugLevel = 2;
	}
	else
	{
		Luna::CompileOptions.optimizationLevel = 0;
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
	std::cout << "Luna Developer Mode Loaded\t\tV0.2.2\n\n";

}
#pragma endregion