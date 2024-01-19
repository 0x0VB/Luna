#include "stdafx.h"
#include "LunaEnum.h"
#include "PvZ/Plant.h"

using namespace Luna::Enum;
void EnumList::lua_PlantState(lua_State* L)
{
	auto Lib = Luna::Enum::EnumLib::New(L, "PlantState");
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
void EnumList::lua_PlantBungeeState(lua_State* L)
{
	auto Lib = Luna::Enum::EnumLib::New(L, "PlantBungeeState");
	L_PlantBungeeState = Lib;
	SetEnum(L, Lib);

	Lib->Add(L, "None", NOT_ON_BUNGEE);
	Lib->Add(L, "Grabbing", GETTING_GRABBED_BY_BUNGEE);
	Lib->Add(L, "Rising", RISING_WITH_BUNGEE);
}
void EnumList::lua_ParticleEffects(lua_State* L)
{
	auto Lib = Luna::Enum::EnumLib::New(L, "ParticleEffects");
	L_ParticleEffects = Lib;
	SetEnum(L, Lib);

	Lib->Add(L, "None", PARTICLE_NONE);
	Lib->Add(L, "MelonSplash", PARTICLE_MELONSPLASH);
	Lib->Add(L, "WinterMelonSplash", PARTICLE_WINTERMELON);
	Lib->Add(L, "FumeCloud", PARTICLE_FUMECLOUD);
	Lib->Add(L, "PopcornSplash", PARTICLE_POPCORNSPLASH);
	Lib->Add(L, "CherryBomb", PARTICLE_POWIE);
	Lib->Add(L, "Powie", PARTICLE_POWIE);
	Lib->Add(L, "JackExplode", PARTICLE_JACKEXPLODE);
	Lib->Add(L, "Sproing", PARTICLE_JACKEXPLODE);
	Lib->Add(L, "ZombieHead", PARTICLE_ZOMBIE_HEAD);
	Lib->Add(L, "ZombieArm", PARTICLE_ZOMBIE_ARM);
	Lib->Add(L, "TrafficCone", PARTICLE_TRAFFIC_CONE);
	Lib->Add(L, "Bucket", PARTICLE_BUCKET);
	Lib->Add(L, "FootballHelmet", PARTICLE_FOOTBALL_HELM);
	Lib->Add(L, "Flag", PARTICLE_FLAG);
	Lib->Add(L, "ScreenDoor", PARTICLE_SCREENDOOR);
	Lib->Add(L, "Newspaper", PARTICLE_ZOMBIE_NEWSPAPER);
	Lib->Add(L, "Headlight", PARTICLE_ZOMBIE_HEADLIGHT);
	Lib->Add(L, "Pow", PARTICLE_POW);
	Lib->Add(L, "Pogo", PARTICLE_ZOMBIE_POGO);
	Lib->Add(L, "NewspaperHead", PARTICLE_ZOMBIE_NEWSPAPER_HEAD);
	Lib->Add(L, "BalloonHead", PARTICLE_ZOMBIE_BALLOON_HEAD);
	Lib->Add(L, "LaneDust", PARTICLE_LANE_DUST);
	Lib->Add(L, "GraveStoneRise", PARTICLE_GRAVE_STONE_RISE);
	Lib->Add(L, "Soil", PARTICLE_SOIL);
	Lib->Add(L, "Water", PARTICLE_WATER);
	Lib->Add(L, "ZombieRise", PARTICLE_ZOMBIE_RISE);
	Lib->Add(L, "Stone", PARTICLE_STONE);
	Lib->Add(L, "SoilSplash", PARTICLE_SOIL_SPLASH);
	Lib->Add(L, "PoolSplash", PARTICLE_POOL_SPLASH);
	Lib->Add(L, "IceSparkle", PARTICLE_ICE_SPARKLE);
	Lib->Add(L, "SeedPacket", PARTICLE_SEED_PACKET);
	Lib->Add(L, "TallNutBlock", PARTICLE_TALL_NUT_BLOCK);
	Lib->Add(L, "Doom", PARTICLE_DOOM);
	Lib->Add(L, "DiggerRise", PARTICLE_DIGGER_RISE);
	Lib->Add(L, "DiggerTunnel", PARTICLE_DIGGER_TUNNEL);
	Lib->Add(L, "DancerRise", PARTICLE_DANCER_RISE);
	Lib->Add(L, "PoolSparkle", PARTICLE_POOL_SPARKLY);
	Lib->Add(L, "WallnutSmall", PARTICLE_WALLNUT_EAT_SMALL);
	Lib->Add(L, "WallnutLarge", PARTICLE_WALLNUT_EAT_LARGE);
	Lib->Add(L, "PeaSplat", PARTICLE_PEA_SPLAT);
	Lib->Add(L, "SpikeSplat", PARTICLE_SPIKE_SPLAT);
	Lib->Add(L, "ButterSplat", PARTICLE_BUTTER_SPLAT);
	Lib->Add(L, "PuffSplat", PARTICLE_PUFF_SPLAT);
	Lib->Add(L, "StarSplat", PARTICLE_STAR_SPLAT);
	Lib->Add(L, "IceTrap", PARTICLE_ICE_TRAP);
	Lib->Add(L, "SnowPeaSplat", PARTICLE_SNOWPEA_SPLAT);
	Lib->Add(L, "SnowPeaPuff", PARTICLE_SNOWPEA_PUFF);
	Lib->Add(L, "SnowPeaTrail", PARTICLE_SNOWPEA_TRAIL);
	Lib->Add(L, "LanternShine", PARTICLE_LANTERN_SHINE);
	Lib->Add(L, "SeedPacketPickup", PARTICLE_SEED_PACKET_PICKUP);
	Lib->Add(L, "PotatoMine", PARTICLE_POTATO_MINE);
	Lib->Add(L, "PotatoMineRise", PARTICLE_POTATO_MINE_RISE);
	Lib->Add(L, "PuffshroomTrail", PARTICLE_PUFFSHROOM_TRAIL);
	Lib->Add(L, "PuffshroomMuzzle", PARTICLE_PUFFSHROOM_MUZZLE);
	Lib->Add(L, "SeedPacketFlash", PARTICLE_SEED_PACKET_FLASH);
	Lib->Add(L, "WhackAZombieRise", PARTICLE_WHACK_A_ZOMBIE_RISE);
	Lib->Add(L, "ZombieLadder", PARTICLE_ZOMBIE_LADDER);
	Lib->Add(L, "BasketballReflect", PARTICLE_UMBRELLA_REFLECT);
	Lib->Add(L, "SeedPacketPick", PARTICLE_SEED_PACKET_PICK);
	Lib->Add(L, "ZombieFreeze", PARTICLE_ICE_TRAP_ZOMBIE);
	Lib->Add(L, "ZombieThaw", PARTICLE_ICE_TRAP_RELEASE);
	Lib->Add(L, "ZamboniSmoke", PARTICLE_ZAMBONI_SMOKE);
	Lib->Add(L, "GloomCloud", PARTICLE_GLOOMCLOUD);
	Lib->Add(L, "PogoHead", PARTICLE_ZOMBIE_POGO_HEAD);
	Lib->Add(L, "ZamboniTire", PARTICLE_ZAMBONI_TIRE);
	Lib->Add(L, "ZamboniExplosion", PARTICLE_ZAMBONI_EXPLOSION);
	Lib->Add(L, "ZamboniExplosion2", PARTICLE_ZAMBONI_EXPLOSION2);
	Lib->Add(L, "CatapultExplosion", PARTICLE_CATAPULT_EXPLOSION);
	Lib->Add(L, "MowerCloud", PARTICLE_MOWER_CLOUD);
	Lib->Add(L, "IceBall", PARTICLE_BOSS_ICE_BALL);
	Lib->Add(L, "Blastmark", PARTICLE_BLASTMARK);
	Lib->Add(L, "CoinPickupArrow", PARTICLE_COIN_PICKUP_ARROW);
	Lib->Add(L, "PresentPickup", PARTICLE_PRESENT_PICKUP);
	Lib->Add(L, "ImitaterMorph", PARTICLE_IMITATER_MORPH);
	Lib->Add(L, "MoweredZombieHead", PARTICLE_MOWERED_ZOMBIE_HEAD);
	Lib->Add(L, "MoweredZombieArm", PARTICLE_MOWERED_ZOMBIE_ARM);
	Lib->Add(L, "ZombieHeadPool", PARTICLE_ZOMBIE_HEAD_POOL);
	Lib->Add(L, "Fireball", PARTICLE_ZOMBIE_BOSS_FIREBALL);
	Lib->Add(L, "FireballDeath", PARTICLE_FIREBALL_DEATH);
	Lib->Add(L, "IceballDeath", PARTICLE_ICEBALL_DEATH);
	Lib->Add(L, "IceballTrail", PARTICLE_ICEBALL_TRAIL);
	Lib->Add(L, "FireballTrail", PARTICLE_FIREBALL_TRAIL);
	Lib->Add(L, "BossExplosion", PARTICLE_BOSS_EXPLOSION);
	Lib->Add(L, "ScreenFlash", PARTICLE_SCREEN_FLASH);
	Lib->Add(L, "TrophySparkle", PARTICLE_TROPHY_SPARKLE);
	Lib->Add(L, "PortalCircle", PARTICLE_PORTAL_CIRCLE);
	Lib->Add(L, "PortalSquare", PARTICLE_PORTAL_SQUARE);
	Lib->Add(L, "PotGlow", PARTICLE_POTTED_PLANT_GLOW);
	Lib->Add(L, "WaterPlantGlow", PARTICLE_POTTED_WATER_PLANT_GLOW);
	Lib->Add(L, "ZenGlow", PARTICLE_POTTED_ZEN_GLOW);
	Lib->Add(L, "Hypnotize", PARTICLE_MIND_CONTROL);
	Lib->Add(L, "VaseShatter", PARTICLE_VASE_SHATTER);
	Lib->Add(L, "VaseShatterPlant", PARTICLE_VASE_SHATTER_LEAF);
	Lib->Add(L, "VaseShatterGarg", PARTICLE_VASE_SHATTER_ZOMBIE);
	Lib->Add(L, "AwardPickupArrow", PARTICLE_AWARD_PICKUP_ARROW);
	Lib->Add(L, "Seaweed", PARTICLE_ZOMBIE_SEAWEED);
	Lib->Add(L, "Mustache", PARTICLE_ZOMBIE_MUSTACHE);
	Lib->Add(L, "Glasses", PARTICLE_ZOMBIE_FUTURE_GLASSES);
	Lib->Add(L, "Pinata", PARTICLE_PINATA);
	Lib->Add(L, "Candy", PARTICLE_PINATA);
	Lib->Add(L, "Dust", PARTICLE_DUST_SQUASH);
	Lib->Add(L, "DustFoot", PARTICLE_DUST_FOOT);
	Lib->Add(L, "Daisy", PARTICLE_DAISY);
	Lib->Add(L, "CreditStrobe", PARTICLE_CREDIT_STROBE);
	Lib->Add(L, "CreditsRayswipe", PARTICLE_CREDITS_RAYSWIPE);
	Lib->Add(L, "CreditsZombieHeadwipe", PARTICLE_CREDITS_ZOMBIEHEADWIPE);
	Lib->Add(L, "Starburst", PARTICLE_STARBURST);
	Lib->Add(L, "CreditsFog", PARTICLE_CREDITS_FOG);
}

EnumList::EnumList(lua_State* L)
{
	lua_PlantBungeeState(L);
	lua_ParticleEffects(L);
	lua_PlantState(L);
}