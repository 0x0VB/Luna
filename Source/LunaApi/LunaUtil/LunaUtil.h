#pragma once
#include "framework.h"

#define LunaUtil Luna::Util
#define LunaInit(Library) LunaUtil::Initiate(Library::Init)

#define SetMeta(Function) lua_pushstring(L, #Function); lua_pushcclosure(L, Function, #Function, 0); lua_settable(L, -3)

#define AssertType LunaUtil::AssertLuaType
#define GetString LunaUtil::GetLuaString
#define GetDouble LunaUtil::GetLuaDouble
#define GetFloat LunaUtil::GetLuaFloat
#define GetInt LunaUtil::GetLuaInt
#define PCall LunaUtil::FPCall

namespace LunaUtil
{
	std::map<std::string, int> LocalDictionary;
	lua_State* LocalState;
	struct lua_f
	{
		void* Pointer;
	public:
		lua_f() { Pointer = nullptr; }
		lua_f(lua_State* L, int Idx);
		void Push(lua_State* L);

		bool operator==(lua_f Other) { return Pointer == Other.Pointer; }
	};
	void Local(lua_State* L, std::string LocalName, int ValueIndex, bool Pop = true);// Store the value at the given index in a local with the given name.
	void Local(lua_State* L, std::string LocalName);// Retrieve the value with the given name.

	void SaveRegisters();
	void LoadRegisters();

	std::string Type(lua_State* L, int Index = -1);

	int GetLuaInt(lua_State* L, int Idx, int Default = 0);
	float GetLuaFloat(lua_State* L, int Idx, float Default = 0);
	double GetLuaDouble(lua_State* L, int Idx, double Default = 0);
	std::string GetLuaString(lua_State* L, int Idx, std::string Default = "");
	int GetParamIndex(lua_State* L, int Index);

	void AssertLuaType(lua_State* L, int Index, std::string Type, std::string ParamName);
	void Initiate(lua_CFunction InitFunc);
	void FPCall(lua_CFunction Func);

	int lua_Sleep(lua_State* L);
	int lua_Wait(lua_State* L);
	int lua_type(lua_State* L);

	int Init(lua_State* L);
}