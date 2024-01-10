#pragma once

#include "Discord/discord.h"

namespace Luna::Discord
{
	extern discord::Core* Core;

	void Initialize();
	void Tick();
}