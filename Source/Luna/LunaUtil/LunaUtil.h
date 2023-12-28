#pragma once
#define LunaUtil Luna::Util
#define LunaInit(Library) LunaUtil::Initiate(Library::Init)

#define AssertType LunaUtil::AssertLuaType
#define GetString LunaUtil::GetLuaString
#define GetDouble LunaUtil::GetLuaDouble
#define GetFloat LunaUtil::GetLuaFloat
#define GetInt LunaUtil::GetLuaInt
#define PCall LunaUtil::FPCall

DWORD JMP_TARGET;
#define svreg __asm{push eax}\
	__asm{push ecx}\
	__asm{push edx}
#define ldreg __asm{pop edx}\
	__asm{pop ecx}\
	__asm{pop eax}
#define jmp(Addr) JMP_TARGET = Addr; __asm{jmp JMP_TARGET}

namespace Luna::Util
{
	void Local(const char* LocalName, int ValueIndex, bool Pop = true);// Store the value at the given index in a local with the given name.
	void Local(const char* LocalName);// Retrieve the value with the given name.

	void SaveRegisters();
	void LoadRegisters();

	std::string Type(int Index = -1);

	int GetLuaInt(int Idx, int Default = 0);
	float GetLuaFloat(int Idx, float Default = 0);
	double GetLuaDouble(int Idx, double Default = 0);
	std::string GetLuaString(int Idx, std::string Default = "");

	void AssertLuaType(int Index, std::string Type, std::string ParamName);

	void Initiate(lua_CFunction InitFunc)
	{
		lua_pushcclosure(L, InitFunc, 0);
		if (lua_pcall(L, 0, 0, 0) == LUA_OK) return;
		LunaIO::Print(lua_tostring(L, -1), LunaIO::Error);
	}

	void FPCall(lua_CFunction Func)
	{
		lua_pushcclosure(L, Func, 0);
		if (lua_pcall(L, 0, 0, 0) != LUA_OK) LunaIO::Print(lua_tostring(L, -1), LunaIO::Error);
	}

	int lua_Sleep(lua_State* L);
	int lua_Wait(lua_State* L);
	int lua_type(lua_State* L);

	int Init(lua_State* L);
}