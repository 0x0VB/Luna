#include "stdafx.h"
#include "Luna.h"
#include "Common.h"


BOOL APIENTRY DllMain
(
	HMODULE ModHandle,
	DWORD  CallReason,
	LPVOID Reserved
)
{
	switch (CallReason)
	{
	case DLL_PROCESS_ATTACH:
	{
		Luna::Setup(LUNA_DEBUG);
		return TRUE;
	}
	default:
		return TRUE;
	}
}