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

void LunaUtil::Initiate(lua_CFunction InitFunc, const char* LibName)
{
	LunaIO::AllocateConsole();
	lua_pushcclosure(LUNA_STATE, InitFunc, "InitFunc", 0);
	if (lua_pcall(LUNA_STATE, 0, 0, 0) == LUA_OK)
		return;
	LunaIO::Print("[LUNA_CORE_ERROR]: ", LunaIO::Error, false);
	std::cout << LibName << "\n" << lua_tostring(LUNA_STATE, -1) << "\n";
}

void LunaUtil::FPCall(lua_CFunction Func)
{
	lua_pushcclosure(GlobalLState, Func, "FPCall", 0);
	if (lua_pcall(GlobalLState, 0, 0, 0) != LUA_OK)
		LunaIO::Print(lua_tostring(GlobalLState, -1), LunaIO::Error);
}

int LunaUtil::GetParamIndex(lua_State* L, int Index)
{ return (Index > 0) ? Index : lua_gettop(L) + Index + 1; }

void LunaUtil::SetRegKey(lua_State* L, const char* LocalName, int Index, bool Pop)
{
	// Save indexes and L->Top
	Index = GetParamIndex(L, Index);
	int T = lua_gettop(L);

	// Set the value
	lua_pushstring(L, LocalName);
	lua_pushvalue(L, Index);
	lua_settable(L, LUA_REGISTRYINDEX);

	// Pop the value if Pop is true
	if (Pop && Index == -1)
		lua_pop(L, 1);
	else if (Pop)
		lua_remove(L, Index);
}

void LunaUtil::GetRegKey(lua_State* L, const char* LocalName)
{
	lua_pushstring(L, LocalName);
	lua_gettable(L, LUA_REGISTRYINDEX);
}

void LunaUtil::PrintStack(lua_State* L)
{
	int T = lua_gettop(L);
	lua_getglobal(L, "print");
	for (int i = 1; i <= T; i++) lua_pushvalue(L, i);
	lua_call(L, T, 0);
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

std::string LunaUtil::Type(lua_State* L, int Index)
{
	int T = lua_gettop(L);
	Index = (Index > 0) ? Index : T + Index;
	std::string Type;

	lua_getmetatable(L, Index);
	if (lua_istable(L, -1))
	{
		// __type valid
		lua_pushstring(L, "__type");
		lua_gettable(L, -2);
		if (lua_isstring(L, -1))
		{
			Type = lua_tostring(L, -1);
			lua_settop(L, T);
			return Type;
		}
		else if (lua_isfunction(L, -1))
		{
			lua_pushvalue(L, Index);
			lua_call(L, 1, 1);
			Type = lua_tostring(L, -1);
			lua_settop(L, T);
			return Type;
		}
	}

	GetRegKey(L, "Type");
	lua_pushvalue(L, Index);
	lua_call(L, 1, 1);
	Type = lua_tostring(L, -1);
	lua_settop(L, T);
	return Type;
}
#pragma endregion

#pragma region lua_f lib
LunaUtil::lua_f::lua_f(lua_State* L, int Idx)
{
	Idx = GetParamIndex(L, Idx);
	if (!lua_isfunction(L, Idx)) LunaIO::ThrowError(L, "Function expected. Unable to construct lua_f.");
	Pointer = (void*)lua_topointer(L, Idx);
	GetRegKey(L, "LuaFunctions");
	lua_pushlightuserdata(L, Pointer);
	lua_pushvalue(L, Idx);
	lua_settable(L, -3);
	lua_pop(L, 1);
}
	
void LunaUtil::lua_f::Push(lua_State* L)
{
	GetRegKey(L, "LuaFunctions");
	lua_pushlightuserdata(L, Pointer);
	lua_gettable(L, -2);
	lua_replace(L, -2);
}
#pragma endregion


#pragma region Quick Cast Functions
int LunaUtil::GetLuaInt(lua_State* L, int I, int D)
{
	if (!lua_isnumber(L, I)) return D;
	return (int)lua_tonumber(L, I);
}
float LunaUtil::GetLuaFloat(lua_State* L, int I, float D)
{
	if (!lua_isnumber(L, I)) return D;
	return (float)lua_tonumber(L, I);
}
double LunaUtil::GetLuaDouble(lua_State* L, int I, double D)
{
	if (!lua_isnumber(L, I)) return D;
	return (double)lua_tonumber(L, I);
}
std::string LunaUtil::GetLuaString(lua_State* L, int I, std::string D)
{
	if (!lua_isstring(L, I)) return D;
	return std::string(lua_tostring(L, I));
}
void LunaUtil::AssertLuaType(lua_State* L, int Index, std::string WantedType, std::string ParamName)
{
	std::string ValueType = Type(L, Index);
	if (WantedType == ValueType) return;
	LunaIO::ThrowError(L, "Expected a " + WantedType + " for " + ParamName + ", got " + ValueType + ".");
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
	GetRegKey(L, "Type");
	lua_pushvalue(L, 1);
	lua_call(L, 1, 1);
	return 1;
}

int LunaUtil::lua_Sleep(lua_State* L) { Sleep(GetInt(L, 1, 1)); return 0; }
int LunaUtil::lua_Wait(lua_State* L) { Sleep(GetInt(L, 1, 1) * 1000); return 0; }

luaL_Reg UtilFuncs[] = {
	{ "Sleep", LunaUtil::lua_Sleep },
	{ "Wait",  LunaUtil::lua_Wait },
	{ "Type",  LunaUtil::lua_type }, // TODO: check how luau type and typeof work and in case replace this accordingly
	{ NULL, NULL }
};

namespace
{
	int PromptDiscordInvite(lua_State* L)
	{
		auto InviteCode = GetString(L, 2, "PvZLuna");
		if (InviteCode.length() > 12)
			LunaIO::ThrowError(L, "Illegal invite code. Please only copy the invite code, not the link (i.e without discord.gg/).");
		InviteCode = "start discord://-/invite/" + InviteCode;
		bool Success = system(InviteCode.c_str());
		lua_pushboolean(L, !Success);
		return 1;
	}
}

int LunaUtil::Init(lua_State* L)
{
	lua_newtable(L);
	SetRegKey(L, "LuaFunctions", -1);// Create the function table

	lua_getglobal(L, "type");// Save type function
	SetRegKey(L, "Type", -1);

	luaL_register(L, "_G", UtilFuncs);
	lua_pushcclosure(L, lua_type, "Type", 0);
	lua_setglobal(L, "type");

	lua_newtable(L);
	
	lua_pushstring(L, "PromptDiscordInvite");
	lua_pushcclosure(L, PromptDiscordInvite, "PromptDiscordInvite", 0);
	lua_settable(L, -3);

	lua_setglobal(L, "Luna");

	return 0;
}
#pragma endregion