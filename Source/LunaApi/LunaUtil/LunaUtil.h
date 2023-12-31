#pragma once
#include "framework.h"
#include "Include/lua.h"

#define LunaUtil Luna::Util
#define LunaInit(Library) LunaUtil::Initiate(Library::Init)

#define AssertType LunaUtil::AssertLuaType
#define GetString LunaUtil::GetLuaString
#define GetDouble LunaUtil::GetLuaDouble
#define GetFloat LunaUtil::GetLuaFloat
#define GetInt LunaUtil::GetLuaInt
#define PCall LunaUtil::FPCall

namespace LunaUtil
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
	void Initiate(lua_CFunction InitFunc);
	void FPCall(lua_CFunction Func);

	int lua_Sleep(lua_State* L);
	int lua_Wait(lua_State* L);
	int lua_type(lua_State* L);

	int Init(lua_State* L);
}