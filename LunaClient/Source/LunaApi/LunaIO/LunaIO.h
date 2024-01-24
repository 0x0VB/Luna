#pragma once
#include "framework.h"

#define LunaIO Luna::IO

namespace LunaIO
{
	enum IOColor { Error = 0x4, Information = 0x1, Warning = 0x6, Success = 0x2, Core = 0x5, None = 0x7 };
	
	extern HANDLE CONSOLE_HANDLE;
	extern BOOL CONSOLE_ALLOCATED;
	extern BOOL PRINT_OVERRIDE;

	void AllocateConsole();
	void SetColor(IOColor = None);

	void Print(const char* Text, IOColor = None, bool NewLine = true);
	__inline void Print(std::string Text, IOColor Color = None, bool NewLine = true) { Print(Text.c_str(), Color, NewLine); }

	void ThrowError(lua_State* L, std::string ErrorText, bool AppendTraceback = true, int Level = 1);
	void ThrowError(lua_State* L, int StringCount = 1, int Level = 1);

	int lua_print(lua_State* L);
	int lua_warn(lua_State* L);
	int lua_info(lua_State* L);
	int lua_core(lua_State* L);

	int Init(lua_State* L);
}