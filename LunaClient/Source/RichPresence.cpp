#include "stdafx.h"
#include "RichPresence.h"

discord::Core* Luna::Discord::core = nullptr;

void Luna::Discord::Setup()
{
	auto result = discord::Core::Create(461618159171141643, DiscordCreateFlags_Default, &core);
	discord::Activity activity{};
	activity.SetState("Testing");
	activity.SetDetails("Fruit Loops");
	core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {});
}

void Luna::Discord::Tick()
{
	core->RunCallbacks();
}
