#pragma once
#pragma region Functions
void LunaUtil::Local(const char* LocalName, int Index, bool Pop)
{
	lua_pushstring(L, LocalName);
	lua_pushvalue(L, (Index > 0) ? Index : Index - 1);
	lua_settable(L, LUA_REGISTRYINDEX);

	if (Pop && Index == -1) lua_pop(L, 1);
	else if (Pop) lua_remove(L, Index);
}

void LunaUtil::Local(const char* LocalName)
{
	lua_pushstring(L, LocalName);
	lua_gettable(L, LUA_REGISTRYINDEX);
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
	int T = lua_gettop(L);
	lua_pushcclosure(L, lua_type, 0);
	lua_pushvalue(L, (Index > 0) ? Index : Index - 1);
	lua_call(L, 1, 1);
	
	auto Type = std::string(lua_tostring(L, -1));
	lua_settop(L, T);
	return Type;
}
#pragma endregion

#pragma region Quick Cast Functions
int LunaUtil::GetLuaInt(int I, int D)
{
	if (!lua_isnumber(L, I)) return D;
	return (int)lua_tonumber(L, I);
}
float LunaUtil::GetLuaFloat(int I, float D)
{
	if (!lua_isnumber(L, I)) return D;
	return (float)lua_tonumber(L, I);
}
double LunaUtil::GetLuaDouble(int I, double D)
{
	if (!lua_isnumber(L, I)) return D;
	return (double)lua_tonumber(L, I);
}
std::string LunaUtil::GetLuaString(int I, std::string D)
{
	if (!lua_isstring(L, I)) return D;
	return std::string(lua_tostring(L, I));
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