#pragma once
#include "PvZ/Definitions.h"
#include "PvZ/DialogButton.h"
#include "LunaApi/LunaEvent/LunaEvent.h"
#include "LunaApi/LunaClass/LunaClass.h"

namespace // Events
{
	DWORD __stdcall UpdateCaller();
	void UpdateHandler();

	DWORD __stdcall UpdateCaller();
	inline void __declspec(naked) UpdateHandler()
	{
		__asm
		{
			push ecx
			call UpdateCaller
			pop ecx
			sub esp, 0xC
			push esi
			lea esi, [esp + 04]
			jmp eax
		}
	}

	DWORD __stdcall FinalDrawCaller(Sexy::Graphics* G);
	void FinalDrawHandler();

	DWORD __stdcall FinalDrawCaller(Sexy::Graphics* G);
	inline void __declspec(naked) FinalDrawHandler()
	{
		__asm
		{
			push ecx
			push ecx
			call FinalDrawCaller
			pop ecx
			jmp eax
		}
	}

	inline void __declspec(naked) StoneButtonDrawHandler()
	{
		// Button in EDI
		__asm
		{
			push[esp + 0x1C]
			push[esp + 0x1C]
			push[esp + 0x1C]
			push[esp + 0x1C]
			push[esp + 0x1C]
			push[esp + 0x1C]
			push eax
			push[esp + 0x20]
			push edi
			call LawnStoneButton::Draw
			ret
		}
	};


	int MsgBox(lua_State* L);
	void SetupEvents();
}

class Luna::Class::LunaApp : public Luna::Class::LunaClass
{
public:
	static int LunaInstanceRef;
	static LunaClass* Source;
	static int Init(lua_State* L);
};