#include "stdafx.h"
#include "Plant.h"

void __declspec(naked) __thiscall Plant::Initialize(SeedType Type, SeedType Imitater, int Lane, int Column)
{
	/* FUNCTION: 45DB60
	ecx		: this		=> esp+04
	esp+04	: Type		=> esp+08
	esp+08	: Imitater	=> esp+0C
	esp+0C	: Lane		=> eax
	esp+10	: Column	=> ecx
	*/
	__asm
	{
		mov eax, [esp+0x0C]
		mov edx, [esp+0x10]
		push [esp+8]
		push [esp+8]
		push ecx
		mov ecx, edx
		mov edx, 0x45DB60
		call edx
		ret 0x10
	}
}

void Plant::Die()
{
	((Die_Type)(0x4679B0))(this);
}

void Plant::Fire(Zombie* Target, int TargetLane, bool IsSecondary)
{
	TargetLane = (TargetLane == -1) ? Lane : TargetLane;
	((Fire_Type)(0x466E00))(this, Target, TargetLane, IsSecondary);
}