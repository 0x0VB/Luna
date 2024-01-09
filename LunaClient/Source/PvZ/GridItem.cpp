#include "stdafx.h"
#include "GridItem.h"
void GridItem::DoGraveEffects()
{
	if (MyLawn)
		MyLawn->EnableGraveStones = true;

	DoGraveEffects_Type Function = (DoGraveEffects_Type)(0x44E090);
	Function(this);
}

void __declspec(naked) __thiscall GridItem::Die()
{
	__asm
	{
		mov esi, ecx
		mov eax, 0x44D000
		call eax
		ret
	}
}

void __declspec(naked) __thiscall GridItem::OpenPortal()
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x44E1B0
		call ecx
		ret
	}
}

void __declspec(naked) __thiscall GridItem::ClosePortal()
{
	__asm
	{
		mov esi, ecx
		mov eax, 0x44E360
		call eax
		ret
	}
}