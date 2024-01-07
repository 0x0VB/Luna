#include "stdafx.h"
#include "Font.h"

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