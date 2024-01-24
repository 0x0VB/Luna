#include "stdafx.h"

#include "Definitions.h"
#include "LawnApp.h"

__declspec(naked) ParticleSystem* LawnApp::AddParticles(ParticleEffect Effect, float X, float Y, int Layer)
{
	__asm
	{
		push 0x453C80
		push esi

		push[esp + 0x14]
		push[esp + 0x14]
		mov esi, ecx
		mov ecx, [esp + 0x20]
		mov eax, [esp + 0x14]
		mov edx, esi
		call[esp + 0x0C]

		pop esi
		pop edx
		ret 0x10
	}
}