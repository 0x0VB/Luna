#pragma once

#include "Discord/discord.h"

namespace Luna::Discord
{
	extern discord::Core* core;
	void Setup();
	void Tick();
}