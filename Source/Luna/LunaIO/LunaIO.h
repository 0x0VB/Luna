#pragma once
#define LunaIO Luna::IO
namespace Luna::IO
{
	enum IOColor { Error = 0x4, Information = 0x1, Warning = 0x6, Success = 0x2, Core = 0x5, None = 0x7 };
	HANDLE CONSOLE_HANDLE = NULL;
	BOOL CONSOLE_ALLOCATED = FALSE;
	BOOL PRINT_OVERRIDE = TRUE;

	void AllocateConsole();
	void SetColor(IOColor = None);

	void Print(const char* Text, IOColor = None, bool NewLine = true);
	void Print(std::string Text, IOColor = None, bool NewLine = true);

	void ThrowError(std::string ErrorText, bool AppendTraceback = true, int Level = 1);
	void ThrowError(int StringCount = 1, int Level = 1);

	int lua_print(lua_State* L);
	int lua_warn(lua_State* L);
	int lua_info(lua_State* L);
	int lua_core(lua_State* L);

	int Init(lua_State* L);
}