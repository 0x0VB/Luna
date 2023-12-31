#include "stdafx.h"
#include "UIElement.h"

Sexy::UIContainer::UIContainer()
{
	CONST DWORD Func = 0x536F00;
	__asm
	{
		mov esi, this
		call Func
	}
}

Sexy::UIElement::UIElement()
{
	CONST DWORD Function = 0x5396F0;
	__asm
	{
		push this
		call Function
	}
}