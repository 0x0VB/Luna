#pragma once
#pragma region Main Functions
void LunaIO::AllocateConsole()
{
	if (CONSOLE_ALLOCATED) return;
	AllocConsole();

	FILE* O = nullptr;
	freopen_s(&O, "CONOUT$", "w", stdout);

	CONSOLE_ALLOCATED = true;
	CONSOLE_HANDLE = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTitleA("LunaIO");
}

void LunaIO::SetColor(IOColor Color)
{
	AllocateConsole();
	SetConsoleTextAttribute(CONSOLE_HANDLE, Color);
}

void LunaIO::Print(const char* Text, IOColor Color, bool NewLine)
{
	SetColor(Color);
	std::cout << Text;
	if (NewLine) std::cout << "\n";
}

void LunaIO::Print(std::string Text, IOColor Color, bool NewLine)
{
	SetColor(Color);
	std::cout << Text;
	if (NewLine) std::cout << "\n";
}

void LunaIO::ThrowError(std::string Text, bool AppendTraceback, int Level)
{
	if (AppendTraceback)
	{
		luaL_traceback(L, L, Text.c_str(), Level);
		lua_error(L);
	}
	else
	{
		lua_pushstring(L, Text.c_str());
		lua_error(L);
	}
}

void LunaIO::ThrowError(int StringCount, int Level)
{
	lua_concat(L, StringCount);
	luaL_traceback(L, L, lua_tostring(L, -1), Level);
	lua_error(L);
}
#pragma endregion

#pragma region Lua Functions
int LunaIO::lua_print(lua_State* L)
{
	if (PRINT_OVERRIDE) SetColor(None);
	PRINT_OVERRIDE = TRUE;

	int T = lua_gettop(L);
	if (T == 0) { std::cout << "\n"; return 0; }

	lua_getglobal(L, "tostring");// [T1]
	int ToStrI = T + 1;// Save tostring index

	// Convert params to string
	for (int i = 1; i <= T; i++)
	{
		lua_pushvalue(L, ToStrI);// Push tostring [+1]
		lua_pushvalue(L, i);// Push param [+1]
		lua_call(L, 1, 1);// Convert to string [-2] [+1]
		std::cout << lua_tostring(L, -1) << " ";
	}
	std::cout << "\n";

	return 0;
}

int LunaIO::lua_warn(lua_State* L)
{
	PRINT_OVERRIDE = FALSE;
	SetColor(Warning);
	lua_print(L);
	return 0;
}

int LunaIO::lua_info(lua_State* L)
{
	PRINT_OVERRIDE = FALSE;
	SetColor(Information);
	lua_print(L);
	return 0;
}

int LunaIO::lua_core(lua_State* L)
{
	PRINT_OVERRIDE = FALSE;
	SetColor(Core);
	lua_print(L);
	return 0;
}
#pragma endregion

int LunaIO::Init(lua_State* L)
{
	lua_register(L, "print", lua_print);
	lua_register(L, "warn", lua_warn);
	lua_register(L, "info", lua_info);
	lua_register(L, "core", lua_core);
	return 0;
}