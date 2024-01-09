#include "stdafx.h"
#include "Zombie.h"

void __declspec(naked) __thiscall Zombie::DieNoLoot()
{
	__asm
	{
		mov eax, 0x530510
		call eax
		ret
	}
}

void __declspec(naked) __thiscall Zombie::DieWithLoot()
{
	__asm
	{
		mov eax, 0x5302F0
		call eax
		ret
	}
}