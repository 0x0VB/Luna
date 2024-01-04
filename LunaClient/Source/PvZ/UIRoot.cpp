#include "stdafx.h"
#include "UIRoot.h"
#include "LawnApp.h"

Sexy::UIRoot::UIRoot()
{
	{
		CONST DWORD Function = 0x5384A0;
		auto App = LawnApp::GetApp();
		__asm
		{
			push App
			push this
			call Function
		}
	}
}