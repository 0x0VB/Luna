#include "stdafx.h"
#include "Font.h"

Sexy::Font::Font()
{
	CONST DWORD Function = 0x586780;
	__asm
	{
		push this
		mov eax, this
		call Function
		pop this
	}
}

Sexy::ImageFont::ImageFont()
{
	CONST DWORD Function = 0x58D010;
	__asm
	{
		push this
		call Function
		mov this, eax
	}
}