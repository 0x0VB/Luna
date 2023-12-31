#include "stdafx.h"
#include "LunaUtil.h"

#include "LunaApi/LunaIO/LunaIO.h"
#include "Luna.h"

// TODO
// idk for what they are
DWORD JMP_TARGET;
#define svreg __asm{push eax}\
	__asm{push ecx}\
	__asm{push edx}
#define ldreg __asm{pop edx}\
	__asm{pop ecx}\
	__asm{pop eax}
#define jmp(Addr) JMP_TARGET = Addr; __asm{jmp JMP_TARGET}

#pragma region Functions

void LunaUtil::Initiate(lua_CFunction InitFunc)
{
	lua_pushcclosure(GlobalLState, InitFunc, 0);
	if (lua_pcall(GlobalLState, 0, 0, 0) == LUA_OK) return;
	LunaIO::Print(lua_tostring(GlobalLState, -1), LunaIO::Error);
}

void LunaUtil::FPCall(lua_CFunction Func)
{
	lua_pushcclosure(GlobalLState, Func, 0);
	if (lua_pcall(GlobalLState, 0, 0, 0) != LUA_OK)
		LunaIO::Print(lua_tostring(GlobalLState, -1), LunaIO::Error);
}

void LunaUtil::Local(const char* LocalName, int Index, bool Pop)
{
	lua_pushstring(GlobalLState, LocalName);
	lua_pushvalue(GlobalLState, (Index > 0) ? Index : Index - 1);
	lua_settable(GlobalLState, LUA_REGISTRYINDEX);

	if (Pop && Index == -1) lua_pop(GlobalLState, 1);
	else if (Pop) lua_remove(GlobalLState, Index);
}

void LunaUtil::Local(const char* LocalName)
{
	lua_pushstring(GlobalLState, LocalName);
	lua_gettable(GlobalLState, LUA_REGISTRYINDEX);
}

void __declspec(naked) LunaUtil::SaveRegisters()
{
	__asm
	{
		push eax
		push ecx
		push edx
		ret
	}
}

void __declspec(naked) LunaUtil::LoadRegisters()
{
	__asm
	{
		pop edx
		pop ecx
		pop eax
		ret
	}
}

std::string LunaUtil::Type(int Index)
{
	int T = lua_gettop(GlobalLState);
	lua_pushcclosure(GlobalLState, lua_type, 0);
	lua_pushvalue(GlobalLState, (Index > 0) ? Index : Index - 1);
	lua_call(GlobalLState, 1, 1);
	
	auto Type = std::string(lua_tostring(GlobalLState, -1));
	lua_settop(GlobalLState, T);
	return Type;
}
#pragma endregion

#pragma region Quick Cast Functions
int LunaUtil::GetLuaInt(int I, int D)
{
	if (!lua_isnumber(GlobalLState, I)) return D;
	return (int)lua_tonumber(GlobalLState, I);
}
float LunaUtil::GetLuaFloat(int I, float D)
{
	if (!lua_isnumber(GlobalLState, I)) return D;
	return (float)lua_tonumber(GlobalLState, I);
}
double LunaUtil::GetLuaDouble(int I, double D)
{
	if (!lua_isnumber(GlobalLState, I)) return D;
	return (double)lua_tonumber(GlobalLState, I);
}
std::string LunaUtil::GetLuaString(int I, std::string D)
{
	if (!lua_isstring(GlobalLState, I)) return D;
	return std::string(lua_tostring(GlobalLState, I));
}
void LunaUtil::AssertLuaType(int Index, std::string WantedType, std::string ParamName)
{
	std::string ValueType = Type(Index);
	if (WantedType == ValueType) return;
	LunaIO::ThrowError("Expected a " + WantedType + " for " + ParamName + ", got " + ValueType + ".");
}
#pragma endregion

#pragma region Lua Functions
int LunaUtil::lua_type(lua_State* L)
{
	lua_getmetatable(L, 1);
	if (!lua_istable(L, -1)) goto VanillaType;
	lua_pushstring(L, "__type");
	lua_gettable(L, -2);
	if (lua_isstring(L, -1)) return 1;
	else if (lua_isfunction(L, -1))
	{
		lua_pushvalue(L, 1);
		lua_call(L, 1, 1);
		return 1;
	}

VanillaType:
	Local("Type");
	lua_pushvalue(L, 1);
	lua_call(L, 1, 1);
	return 1;
}

int LunaUtil::lua_Sleep(lua_State* L) { Sleep(GetInt(1, 1)); return 0; }
int LunaUtil::lua_Wait(lua_State* L) { Sleep(GetInt(1, 1) * 1000); return 0; }

int LunaUtil::Init(lua_State* L)
{
	lua_getglobal(L, "type");
	Local("Type", -1);
	lua_register(L, "Sleep", lua_Sleep);
	lua_register(L, "Wait", lua_Wait);
	lua_register(L, "type", lua_type);

	return 0;
}
#pragma endregion