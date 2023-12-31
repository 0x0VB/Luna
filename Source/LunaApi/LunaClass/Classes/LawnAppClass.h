#pragma once
#include "PvZ/Definitions.h"
#include "LunaApi/LunaEvent/LunaEvent.h"
#include "LunaApi/LunaClass/LunaClass.h"

namespace Disp::LunaApp
{
	using Luna::Event::LunaEvent;

	extern DWORD StoneButtonEntries[1];
	extern LunaEvent* StoneButtonDraw;

	extern DWORD UpdateEntries[1];
	extern LunaEvent* OnUpdate;

	extern DWORD FinalDrawEntries[1];
	extern LunaEvent* OnFinalDraw;
	extern Sexy::Image* MyImg;

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
			lea esi, [esp+04]
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


	int MsgBox(lua_State* L);
	void SetupEvents();
}

class Luna::Class::Classes::LunaApp : public Luna::Class::Base::LunaClass
{
public:
	static Base::LunaClass* Source;
	static int Init(lua_State* L);
};