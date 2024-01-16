#include "stdafx.h"

#include "LunaApi/LunaClass/LunaClass.h"
#include "LunaApi/LunaUtil/LunaUtil.h"
#include "LunaEnum.h"
#include "Luna.h"

using namespace Luna::Enum;

#pragma region EnumLib Member Functions
bool EnumLib::Contains(std::string Name) { return Items.contains(Name); }
bool EnumLib::Contains(EnumItem* Item) { return Items.contains(Item->Name); }
bool EnumLib::Contains(int Value) { return Values.contains(Value); }

void EnumLib::Add(EnumItem* Item)
{
	Item->Library = this;
	Items[Item->Name] = Item;
	Values[Item->Value] = Item;
}

void EnumLib::Add(lua_State* L, std::string ItemName, int Value)
{
	auto Item = EnumItem::New(L, this, ItemName, Value);
}

int EnumLib::AssertEnum(lua_State* L, int Index, std::string ParamName)
{
	int T = lua_gettop(L);
	
	if (lua_isuserdata(L, Index))
	{
		lua_getmetatable(L, Index);
		LunaUtil::GetRegKey(L, "EnumItemMeta");
		if (lua_equal(L, -2, -1))
		{
			lua_settop(L, T);
			auto self = *(EnumItem**)lua_touserdata(L, Index);
			return self->Value;
		}
	}
	else if (lua_isnumber(L, Index))
	{
		int Value = GetInt(L, Index);
		if (Contains(Value)) return Value;
	}
	else if (lua_isstring(L, Index))
	{
		auto ItemName = GetString(L, Index);
		if (Contains(ItemName)) return Items[ItemName]->Value;
	}
	LunaIO::ThrowError(L, "Expected a " + Name + " for " + ParamName + ", got " + LunaUtil::Type(L, Index));
}

EnumLib* EnumLib::New(lua_State* L, std::string LibName)
{
	int T = lua_gettop(L);
	auto Proxy = (EnumLib**)lua_newuserdata(L, 4);
	*Proxy = new EnumLib(LibName);

	LunaUtil::GetRegKey(L, "EnumLibMeta");
	lua_setmetatable(L, -2);
	(*Proxy)->Reference = lua_ref(L, -1);
	lua_settop(L, T);

	return *Proxy;
}
#pragma endregion

#pragma region EnumItem Member Functions
EnumItem* EnumItem::New(lua_State* L, EnumLib* Lib, std::string ItemName, int Value)
{
	int T = lua_gettop(L);
	auto Proxy = (EnumItem**)lua_newuserdata(L, 4);
	*Proxy = new EnumItem(ItemName, Lib, Value);

	LunaUtil::GetRegKey(L, "EnumItemMeta");
	lua_setmetatable(L, -2);
	(*Proxy)->Reference = lua_ref(L, -1);
	lua_settop(L, T);

	return *Proxy;
}
#pragma endregion

#pragma region EnumLib Meta
int EnumLib::__type(lua_State* L)
{
	lua_pushstring(L, "EnumLibrary");
	return 1;
}

int EnumLib::__index(lua_State* L)
{
	auto self = *(EnumLib**)lua_touserdata(L, 1);
	auto Field = GetField(L);
	if (Field == "Name") lua_pushstring(L, self->Name.c_str());
	else if (self->Contains(Field)) lua_getref(L, self->Items[Field]->Reference);
	else LunaIO::ThrowError(L, Field + " is not a valid member of EnumLibrary.");

	return 1;
}

int EnumLib::__newindex(lua_State* L) { LunaIO::ThrowError(L, "EnumLibraries are read-only."); }
int EnumLib::__tostring(lua_State* L)
{
	auto self = *(EnumLib**)lua_touserdata(L, 1);
	lua_pushstring(L, ("Enum." + self->Name).c_str());
	return 1;
}
#pragma endregion

#pragma region EnumItem Meta
int EnumItem::__type(lua_State* L)
{
	lua_pushstring(L, "EnumItem");
	return 1;
}

int EnumItem::__index(lua_State* L)
{
	auto self = *(EnumItem**)lua_touserdata(L, 1);
	auto Field = GetField(L);

	if (Field == "Name") lua_pushstring(L, self->Name.c_str());
	else if (Field == "Value") lua_pushinteger(L, self->Value);
	else if (Field == "Library") lua_getref(L, self->Library->Reference);
	else if (Field == "Type") lua_pushstring(L, self->Library->Name.c_str());
	else LunaIO::ThrowError(L, Field + " is not a valid member of EnumItem.");

	return 1;
}

int EnumItem::__newindex(lua_State* L)
{
	LunaIO::ThrowError(L, "EnumItems are read-only.");
}

int EnumItem::__tostring(lua_State* L)
{
	auto self = *(EnumItem**)lua_touserdata(L, 1);
	lua_pushstring(L, ("Enum." + self->Library->Name + "." + self->Name).c_str());
	return 1;
}
#pragma endregion

void Luna::Enum::SetEnum(lua_State* L, EnumLib* Lib)
{
	lua_getglobal(L, "Enum");
	lua_pushstring(L, Lib->Name.c_str());
	lua_getref(L, Lib->Reference);
	lua_settable(L, -3);
	lua_pop(L, 1);
}

void SetupEnums(lua_State* L)
{
	auto Lib = EnumLib::New(L, "ParticleEffects");

	Lib->Add(L, "None", PARTICLE_NONE);
	Lib->Add(L, "MelonSplash", PARTICLE_MELONSPLASH);
	Lib->Add(L, "WinterMelon", PARTICLE_WINTERMELON);
	Lib->Add(L, "FumeCloud", PARTICLE_FUMECLOUD);
	Lib->Add(L, "PopcornSplash", PARTICLE_POPCORNSPLASH);
	Lib->Add(L, "Powie", PARTICLE_POWIE);
	Lib->Add(L, "JackExplode", PARTICLE_JACKEXPLODE);
	Lib->Add(L, "ZombieHead", PARTICLE_ZOMBIE_HEAD);
	Lib->Add(L, "ZombieArm", PARTICLE_ZOMBIE_ARM);
	Lib->Add(L, "ZombieTrafficCone", PARTICLE_ZOMBIE_TRAFFIC_CONE);
	Lib->Add(L, "ZombiePail", PARTICLE_ZOMBIE_PAIL);
	Lib->Add(L, "ZombieHelmet", PARTICLE_ZOMBIE_HELMET);
	Lib->Add(L, "ZombieFlag", PARTICLE_ZOMBIE_FLAG);
	Lib->Add(L, "ZombieDoor", PARTICLE_ZOMBIE_DOOR);
	Lib->Add(L, "ZombieNewspaper", PARTICLE_ZOMBIE_NEWSPAPER);
	Lib->Add(L, "ZombieHeadlight", PARTICLE_ZOMBIE_HEADLIGHT);
	Lib->Add(L, "Powie", PARTICLE_POW);
	Lib->Add(L, "ZombiePogo", PARTICLE_ZOMBIE_POGO);
	Lib->Add(L, "ZombieNewspaperHead", PARTICLE_ZOMBIE_NEWSPAPER_HEAD);
	Lib->Add(L, "ZombieBalloonHead", PARTICLE_ZOMBIE_BALLOON_HEAD);
	Lib->Add(L, "SodRoll", PARTICLE_SOD_ROLL);
	Lib->Add(L, "GraveStoneRise", PARTICLE_GRAVE_STONE_RISE);
	Lib->Add(L, "Planting", PARTICLE_PLANTING);
	Lib->Add(L, "PlantingPool", PARTICLE_PLANTING_POOL);
	Lib->Add(L, "ZombieRise", PARTICLE_ZOMBIE_RISE);
	Lib->Add(L, "GraveBuster", PARTICLE_GRAVE_BUSTER);
	Lib->Add(L, "GraveBusterDie", PARTICLE_GRAVE_BUSTER_DIE);
	Lib->Add(L, "PoolSplash", PARTICLE_POOL_SPLASH);
	Lib->Add(L, "IceSparkle", PARTICLE_ICE_SPARKLE);
	Lib->Add(L, "SeedPacket", PARTICLE_SEED_PACKET);
	Lib->Add(L, "TallNutBlock", PARTICLE_TALL_NUT_BLOCK);
	Lib->Add(L, "Doom", PARTICLE_DOOM);
	Lib->Add(L, "DiggerRise", PARTICLE_DIGGER_RISE);
	Lib->Add(L, "DiggerTunnel", PARTICLE_DIGGER_TUNNEL);
	Lib->Add(L, "DancerRise", PARTICLE_DANCER_RISE);
	Lib->Add(L, "PoolSparkly", PARTICLE_POOL_SPARKLY);
	Lib->Add(L, "WallnutEatSmall", PARTICLE_WALLNUT_EAT_SMALL);
	Lib->Add(L, "WallnutEatLarge", PARTICLE_WALLNUT_EAT_LARGE);
	Lib->Add(L, "PeaSplat", PARTICLE_PEA_SPLAT);
	Lib->Add(L, "SpikeSplat", PARTICLE_SPIKE_SPLAT);
	Lib->Add(L, "ButterSplat", PARTICLE_BUTTER_SPLAT);
	Lib->Add(L, "CabbageSplat", PARTICLE_CABBAGE_SPLAT);
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
	Lib->Add(L, "UmbrellaReflect", PARTICLE_UMBRELLA_REFLECT);
	Lib->Add(L, "SeedPacketPick", PARTICLE_SEED_PACKET_PICK);
	Lib->Add(L, "IceTrapZombie", PARTICLE_ICE_TRAP_ZOMBIE);
	Lib->Add(L, "IceTrapRelease", PARTICLE_ICE_TRAP_RELEASE);
	Lib->Add(L, "ZamboniSmoke", PARTICLE_ZAMBONI_SMOKE);
	Lib->Add(L, "GloomCloud", PARTICLE_GLOOMCLOUD);
	Lib->Add(L, "ZombiePogoHead", PARTICLE_ZOMBIE_POGO_HEAD);
	Lib->Add(L, "ZamboniTire", PARTICLE_ZAMBONI_TIRE);
	Lib->Add(L, "ZamboniExplosion", PARTICLE_ZAMBONI_EXPLOSION);
	Lib->Add(L, "ZamboniExplosion2", PARTICLE_ZAMBONI_EXPLOSION2);
	Lib->Add(L, "CatapultExplosion", PARTICLE_CATAPULT_EXPLOSION);
	Lib->Add(L, "MowerCloud", PARTICLE_MOWER_CLOUD);
	Lib->Add(L, "BossIceBall", PARTICLE_BOSS_ICE_BALL);
	Lib->Add(L, "Blastmark", PARTICLE_BLASTMARK);
	Lib->Add(L, "CoinPickupArrow", PARTICLE_COIN_PICKUP_ARROW);
	Lib->Add(L, "PresentPickup", PARTICLE_PRESENT_PICKUP);
	Lib->Add(L, "ImitaterMorph", PARTICLE_IMITATER_MORPH);
	Lib->Add(L, "MoweredZombieHead", PARTICLE_MOWERED_ZOMBIE_HEAD);
	Lib->Add(L, "MoweredZombieArm", PARTICLE_MOWERED_ZOMBIE_ARM);
	Lib->Add(L, "ZombieHeadPool", PARTICLE_ZOMBIE_HEAD_POOL);
	Lib->Add(L, "ZombieBossFireball", PARTICLE_ZOMBIE_BOSS_FIREBALL);
	Lib->Add(L, "FireballDeath", PARTICLE_FIREBALL_DEATH);
	Lib->Add(L, "IceballDeath", PARTICLE_ICEBALL_DEATH);
	Lib->Add(L, "IceballTrail", PARTICLE_ICEBALL_TRAIL);
	Lib->Add(L, "FireballTrail", PARTICLE_FIREBALL_TRAIL);
	Lib->Add(L, "BossExplosion", PARTICLE_BOSS_EXPLOSION);
	Lib->Add(L, "ScreenFlash", PARTICLE_SCREEN_FLASH);
	Lib->Add(L, "TrophySparkle", PARTICLE_TROPHY_SPARKLE);
	Lib->Add(L, "PortalCircle", PARTICLE_PORTAL_CIRCLE);
	Lib->Add(L, "PortalSquare", PARTICLE_PORTAL_SQUARE);
	Lib->Add(L, "PottedPlantGlow", PARTICLE_POTTED_PLANT_GLOW);
	Lib->Add(L, "PottedWaterPlantGlow", PARTICLE_POTTED_WATER_PLANT_GLOW);
	Lib->Add(L, "PottedZenGlow", PARTICLE_POTTED_ZEN_GLOW);
	Lib->Add(L, "MindControl", PARTICLE_MIND_CONTROL);
	Lib->Add(L, "VaseShatter", PARTICLE_VASE_SHATTER);
	Lib->Add(L, "VaseShatterLeaf", PARTICLE_VASE_SHATTER_LEAF);
	Lib->Add(L, "VaseShatterZombie", PARTICLE_VASE_SHATTER_ZOMBIE);
	Lib->Add(L, "AwardPickupArrow", PARTICLE_AWARD_PICKUP_ARROW);
	Lib->Add(L, "ZombieSeaweed", PARTICLE_ZOMBIE_SEAWEED);
	Lib->Add(L, "ZombieMustache", PARTICLE_ZOMBIE_MUSTACHE);
	Lib->Add(L, "ZombieFutureGlasses", PARTICLE_ZOMBIE_FUTURE_GLASSES);
	Lib->Add(L, "Pinata", PARTICLE_PINATA);
	Lib->Add(L, "DustSquash", PARTICLE_DUST_SQUASH);
	Lib->Add(L, "DustFoot", PARTICLE_DUST_FOOT);
	Lib->Add(L, "Daisy", PARTICLE_DAISY);
	Lib->Add(L, "CreditStrobe", PARTICLE_CREDIT_STROBE);
	Lib->Add(L, "CreditsRayswipe", PARTICLE_CREDITS_RAYSWIPE);
	Lib->Add(L, "CreditsZombieHeadwipe", PARTICLE_CREDITS_ZOMBIEHEADWIPE);
	Lib->Add(L, "Starburst", PARTICLE_STARBURST);
	Lib->Add(L, "CreditsFog", PARTICLE_CREDITS_FOG);
}

int Luna::Enum::Init(lua_State* L)
{
	lua_newtable(L);// Enums
	lua_setglobal(L, "Enum");

	lua_newtable(L);// EnumLibrary Meta
	
	lua_pushstring(L, "__type");
	lua_pushcclosure(L, EnumLib::__type, "EnumLib::__type", 0);
	lua_settable(L, -3);

	lua_pushstring(L, "__index");
	lua_pushcclosure(L, EnumLib::__index, "EnumLib::__index", 0);
	lua_settable(L, -3);

	lua_pushstring(L, "__newindex");
	lua_pushcclosure(L, EnumLib::__newindex, "EnumLib::__newindex", 0);
	lua_settable(L, -3);

	lua_pushstring(L, "__tostring");
	lua_pushcclosure(L, EnumLib::__tostring, "EnumLib::__tostring", 0);
	lua_settable(L, -3);
	LunaUtil::SetRegKey(L, "EnumLibMeta");


	lua_newtable(L);// EnumItem Meta

	lua_pushstring(L, "__type");
	lua_pushcclosure(L, EnumItem::__type, "EnumItem::__type", 0);
	lua_settable(L, -3);

	lua_pushstring(L, "__index");
	lua_pushcclosure(L, EnumItem::__index, "EnumItem::__index", 0);
	lua_settable(L, -3);

	lua_pushstring(L, "__newindex");
	lua_pushcclosure(L, EnumItem::__newindex, "EnumItem::__newindex", 0);
	lua_settable(L, -3);

	lua_pushstring(L, "__tostring");
	lua_pushcclosure(L, EnumItem::__tostring, "EnumItem::__tostring", 0);
	lua_settable(L, -3);
	LunaUtil::SetRegKey(L, "EnumItemMeta");

	return 0;
}