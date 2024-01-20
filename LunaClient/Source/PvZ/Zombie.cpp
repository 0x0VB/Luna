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

void __declspec(naked) __thiscall Zombie::Rise(int Col, int Row)
{
	__asm
	{
		push ebx
		mov edx, 0x531C90
		push [esp+0xC]
		mov eax, [esp+0xC]
		mov ebx, ecx
		call edx
		pop ebx
		ret 0x8
	}
}