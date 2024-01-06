#pragma once
#include "framework.h"

#define LunaUtil Luna::Util
#define LunaInit(Library) LunaUtil::Initiate(Library::Init, #Library)

#define SetMetaByName(Function, Name) lua_pushstring(L, Name); lua_pushcclosure(L, Function, Name, 0); lua_settable(L, -3)
#define SetMeta(Function) lua_pushstring(L, #Function); lua_pushcclosure(L, Function, #Function, 0); lua_settable(L, -3)

#define AssertType LunaUtil::AssertLuaType
#define GetString LunaUtil::GetLuaString
#define GetDouble LunaUtil::GetLuaDouble
#define GetFloat LunaUtil::GetLuaFloat
#define GetInt LunaUtil::GetLuaInt
#define PCall LunaUtil::FPCall

namespace LunaUtil
{
	struct lua_f
	{
		void* Pointer;
	public:
		lua_f() { Pointer = NULL; }
		lua_f(lua_State* L, int Idx);
		void Push(lua_State* L);

		bool operator==(lua_f Other) { return Pointer == Other.Pointer; }
	};
	void SetRegKey(lua_State* L, const char* LocalName, int ValueIndex, bool Pop = true);// Store the value at the given index in a local with the given name.
	void GetRegKey(lua_State* L, const char* LocalName);// Retrieve the value with the given name.

	void SaveRegisters();
	void LoadRegisters();

	std::string Type(lua_State* L, int Index = -1);

	int GetLuaInt(lua_State* L, int Idx, int Default = 0);
	float GetLuaFloat(lua_State* L, int Idx, float Default = 0);
	double GetLuaDouble(lua_State* L, int Idx, double Default = 0);
	std::string GetLuaString(lua_State* L, int Idx, std::string Default = "");
	int GetParamIndex(lua_State* L, int Index);

	void AssertLuaType(lua_State* L, int Index, std::string Type, std::string ParamName);
	void Initiate(lua_CFunction InitFunc, const char* LibName);
	void FPCall(lua_CFunction Func);
	void PrintStack(lua_State* L);

	int lua_Sleep(lua_State* L);
	int lua_Wait(lua_State* L);
	int lua_type(lua_State* L);

	int Init(lua_State* L);
}