#include "stdafx.h"
#include "Pickup.h"

void __declspec(naked) __thiscall Pickup::Initialize(int X, int Y, PickupType Type, PickupMotion Motion)
{
	/* FUNCTION: 42FF60
	ecx: this		=> esp+04
	esp+04: X		=> esp+08
	esp+08: Y		=> esp+0C
	esp+0C: Type	=> eax
	esp+10: Motion	=> ecx
	*/
	__asm
	{
		mov eax, [esp+0x0C]
		mov edx, [esp+0x10]
		push [esp+0x08]
		push [esp+0x08]
		push ecx
		mov ecx, edx
		mov edx, 0x42FF60
		call edx
		ret 0x10
	}
}