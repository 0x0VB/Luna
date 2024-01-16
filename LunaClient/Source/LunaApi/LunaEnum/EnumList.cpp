#include "stdafx.h"
#include "EnumList.h"
#include "PvZ/Plant.h"

using namespace Enums;
void lua_PlantState(lua_State* L)
{
	auto Lib = EnumLib::New(L, "PlantState");
	L_PlantState = Lib;
	SetEnum(L, Lib);

	Lib->Add(L, "NotReady", STATE_NOTREADY);
	Lib->Add(L, "Ready", STATE_READY);
	Lib->Add(L, "DoingSpecial", STATE_DOINGSPECIAL);
	Lib->Add(L, "SquashLook", STATE_SQUASH_LOOK);
	Lib->Add(L, "SquashPreLaunch", STATE_SQUASH_PRE_LAUNCH);
	Lib->Add(L, "SquashRising", STATE_SQUASH_RISING);
	Lib->Add(L, "SquashFalling", STATE_SQUASH_FALLING);
	Lib->Add(L, "SquashDoneFalling", STATE_SQUASH_DONE_FALLING);
	Lib->Add(L, "GravebusterLanding", STATE_GRAVEBUSTER_LANDING);
	Lib->Add(L, "GravebusterEating", STATE_GRAVEBUSTER_EATING);
	Lib->Add(L, "ChomperBiting", STATE_CHOMPER_BITING);
	Lib->Add(L, "ChomperBitingGotOne", STATE_CHOMPER_BITING_GOT_ONE);
	Lib->Add(L, "ChomperBitingMissed", STATE_CHOMPER_BITING_MISSED);
	Lib->Add(L, "ChomperDigesting", STATE_CHOMPER_DIGESTING);
	Lib->Add(L, "ChomperSwallowing", STATE_CHOMPER_SWALLOWING);
	Lib->Add(L, "PotatoRising", STATE_POTATO_RISING);
	Lib->Add(L, "PotatoArmed", STATE_POTATO_ARMED);
	Lib->Add(L, "PotatoMashed", STATE_POTATO_MASHED);
	Lib->Add(L, "SpikeweedAttacking", STATE_SPIKEWEED_ATTACKING);
	Lib->Add(L, "SpikeweedAttacking2", STATE_SPIKEWEED_ATTACKING_2);
	Lib->Add(L, "ScaredyshroomLowering", STATE_SCAREDYSHROOM_LOWERING);
	Lib->Add(L, "ScaredyshroomScared", STATE_SCAREDYSHROOM_SCARED);
	Lib->Add(L, "ScaredyshroomRaising", STATE_SCAREDYSHROOM_RAISING);
	Lib->Add(L, "SunshroomSmall", STATE_SUNSHROOM_SMALL);
	Lib->Add(L, "SunshroomGrowing", STATE_SUNSHROOM_GROWING);
	Lib->Add(L, "SunshroomBig", STATE_SUNSHROOM_BIG);
	Lib->Add(L, "MagnetshroomSucking", STATE_MAGNETSHROOM_SUCKING);
	Lib->Add(L, "MagnetshroomCharging", STATE_MAGNETSHROOM_CHARGING);
	Lib->Add(L, "BowlingUp", STATE_BOWLING_UP);
	Lib->Add(L, "BowlingDown", STATE_BOWLING_DOWN);
	Lib->Add(L, "CactusLow", STATE_CACTUS_LOW);
	Lib->Add(L, "CactusRising", STATE_CACTUS_RISING);
	Lib->Add(L, "CactusHigh", STATE_CACTUS_HIGH);
	Lib->Add(L, "CactusLowering", STATE_CACTUS_LOWERING);
	Lib->Add(L, "TanglekelpGrabbing", STATE_TANGLEKELP_GRABBING);
	Lib->Add(L, "CobcannonArming", STATE_COBCANNON_ARMING);
	Lib->Add(L, "CobcannonLoading", STATE_COBCANNON_LOADING);
	Lib->Add(L, "CobcannonReady", STATE_COBCANNON_READY);
	Lib->Add(L, "CobcannonFiring", STATE_COBCANNON_FIRING);
	Lib->Add(L, "KernelpultButter", STATE_KERNELPULT_BUTTER);
	Lib->Add(L, "UmbrellaTriggered", STATE_UMBRELLA_TRIGGERED);
	Lib->Add(L, "UmbrellaReflecting", STATE_UMBRELLA_REFLECTING);
	Lib->Add(L, "ImitaterMorphing", STATE_IMITATER_MORPHING);
	Lib->Add(L, "ZenGardenWatered", STATE_ZEN_GARDEN_WATERED);
	Lib->Add(L, "ZenGardenNeedy", STATE_ZEN_GARDEN_NEEDY);
	Lib->Add(L, "ZenGardenHappy", STATE_ZEN_GARDEN_HAPPY);
	Lib->Add(L, "MarigoldEnding", STATE_MARIGOLD_ENDING);
	Lib->Add(L, "FlowerpotInvulnerable", STATE_FLOWERPOT_INVULNERABLE);
	Lib->Add(L, "LilypadInvulnerable", STATE_LILYPAD_INVULNERABLE);
}
void lua_PlantBungeeState(lua_State* L)
{
	auto Lib = EnumLib::New(L, "PlantBungeeState");
	L_PlantBungeeState = Lib;
	SetEnum(L, Lib);

	Lib->Add(L, "None", NOT_ON_BUNGEE);
	Lib->Add(L, "Grabbing", GETTING_GRABBED_BY_BUNGEE);
	Lib->Add(L, "Rising", RISING_WITH_BUNGEE);
}

int Enums::Init(lua_State* L)
{
	lua_PlantState(L);
	lua_PlantBungeeState(L);
}