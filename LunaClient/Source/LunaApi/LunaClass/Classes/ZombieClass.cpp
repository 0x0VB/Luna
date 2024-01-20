#include "stdafx.h"
#include "ZombieClass.h"
#include "PvZ/GridItem.h"
#include "PvZ/Zombie.h"
#include "LunaApi/LunaUtil/LunaUtil.h"
#include "UIContainerClass.h"
#include "PlantDefClass.h"
#include "GridItemClass.h"

using namespace Luna::Event;
using namespace Luna::Class;
using namespace Luna::Enum;
using namespace Fields;
Zombie* GetZombie(lua_State* L, int I, std::string ParamName, bool AcceptNil)
{
	auto self = AssertIsA(L, I, "Zombie", ParamName, AcceptNil);
	if (self == NULL && AcceptNil) return NULL;
	return (Zombie*)self->GetBase();
}

namespace
{
	EnumList* Enums;
}

namespace
{
	int Kill(lua_State* L)
	{
		auto self = GetZombie(L);
		auto DropLoot = GetBool(L, 2);
		if (DropLoot) self->DieWithLoot();
		else self->DieNoLoot();
		return 0;
	}

	int RiseFromGrave(lua_State* L)
	{
		auto self = GetZombie(L);
		auto Grave = GetGridItem(L, 2, "Grave", true);

		if (Grave == NULL)
		{
			self->Rise(5, self->Lane);
		}
		else
		{
			self->Rise(Grave->Column, Grave->Lane);
		}
		return 0;
	}
}

LunaZombie* LunaZombie::Source = new LunaZombie();
int LunaZombie::Init(lua_State* L)
{
	Enums = Enum::GetEnums(L);
	Source->AllowsInjection = true;
	Source->SetName("Zombie");
	Source->AddSubClass("GameObject");
	Source->CustomBase = true;

	UIObjectField::New("Lawn", 0x4, Source);
	UIObjectField::New("Game", 0x4, Source);

	RctField::New("Hitbox", 0x8, Source);
	BlnField::New("Visible", 0x18, Source);
	IntField::New("Row", 0x1C, Source);
	IntField::New("Lane", 0x1C, Source);
	IntField::New("Layer", 0x20, Source);

	IntField::New("Type", 0x24, Source);
	IntField::New("Phase", 0x28, Source);
	FV2Field::New("Position", 0x2C, Source);
	FltField::New("Speed", 0x34, Source);
	IntField::New("GroanTimer", 0x3C, Source);
	IntField::New("Frame", 0x48, Source, true);
	BytField::New("Variant", 0x50, Source);
	BlnField::New("IsEating", 0x51, Source);
	IntField::New("DamageTimer", 0x54, Source);
	IntField::New("ShieldDamageTimer", 0x58, Source);
	IntField::New("ShieldRecoilTimer", 0x5C, Source);
	IntField::New("Age", 0x60, Source);
	IntField::New("HeightType", 0x64, Source);
	IntField::New("PhaseTimer", 0x68, Source);
	IntField::New("FromWave", 0x6C, Source);
	BlnField::New("DroppedLoot", 0x70, Source);
	IntField::New("FadeTimer", 0x74, Source);
	BlnField::New("TiresPopped", 0x78, Source);
	IntField::New("LadderUsedAt", 0x7C, Source);
	IntField::New("TargetColumn", 0x80, Source);
	FltField::New("Altitude", 0x84, Source);
	BlnField::New("HitUmbrella", 0x88, Source);
	RctField::New("ZombieHitbox", 0x8C, Source);
	RctField::New("AttackHitbox", 0x9C, Source);
	IntField::New("ChilledTimer", 0xAC, Source);
	IntField::New("ButterTimer", 0xB0, Source);
	IntField::New("FrozenTimer", 0xB4, Source);
	BlnField::New("Hypnotized", 0xB8, Source);
	BlnField::New("BlownAway", 0xB9, Source);
	BlnField::New("HasHead", 0xBA, Source);
	BlnField::New("HasArm", 0xBB, Source);
	BlnField::New("HasObject", 0xBC, Source);
	BlnField::New("InPool", 0xBD, Source);
	BlnField::New("OnHighGround", 0xBE, Source);
	BlnField::New("YuckyFace", 0xBF, Source);
	IntField::New("YuckyFaceTimer", 0xC0, Source);
	IntField::New("HelmetType", 0xC4, Source);
	IntField::New("Health", 0xC8, Source);
	IntField::New("MaxHealth", 0xCC, Source);
	IntField::New("HelmetHealth", 0xD0, Source);
	IntField::New("MaxHelmetHealth", 0xD4, Source);
	IntField::New("ShieldType", 0xD8, Source);
	IntField::New("ShieldHealth", 0xDC, Source);
	IntField::New("MaxShieldHealth", 0xE0, Source);
	IntField::New("FlyingHealth", 0xE4, Source);
	IntField::New("MaxFlyingHealth", 0xE8, Source);
	BlnField::New("Dead", 0xEC, Source);

	Source->Methods["Kill"] = Kill;
	Source->Methods["Rise"] = RiseFromGrave;

	return 0;
}

void* LunaZombie::GetBase(LunaInstance* self)
{
	auto L = LUNA_STATE;
	auto Array = (DataArray<Zombie>*)self->Base;
	auto GameID = self->Data[1];
	auto ID = self->Data[0];
	int T = lua_gettop(L);
	void* Result;
	if (GameID == 0) return self->Base;

	lua_pushinteger(L, self->Data[1]);
	lua_gettable(L, LUA_REGISTRYINDEX);

	if (lua_isnil(L, -1))
		Result = NULL;
	else
		Result = Array->TryToGet(ID);

	lua_settop(L, T);
	return Result;
}

void LunaZombie::New(lua_State* L, void* Param)
{
	auto NewPlant = (DataArrayItem<Zombie>*)Param;
	auto ID = NewPlant->ID;
	auto Game = NewPlant->Item.MyLawn;
	auto NoGame = Game == NULL;
	auto GameID = (NoGame) ? 0 : (Game->GameID);

	int T = lua_gettop(L);
	lua_pushinteger(L, GameID);
	lua_gettable(L, LUA_REGISTRYINDEX);// T + 1: GameRef
	lua_pushstring(L, "Zombies");// T + 2: PlantRef
	if (!lua_istable(L, T + 1))
	{
		lua_settop(L, T);
		lua_pushnil(L);
		return;
	}
	lua_gettable(L, T + 1);

	lua_pushinteger(L, ID);
	lua_gettable(L, -2);// T + 3: Plant Proxy?
	if (!lua_isnil(L, -1))
	{
		lua_replace(L, T + 1);
		lua_settop(L, T + 1);
		return;
	}

	auto self = (LunaInstance*)lua_newuserdata(L, sizeof(LunaInstance));// T + 4: Plant Proxy
	self->Base = (NoGame) ? Param : &(Game->Zombies);
	self->Class = this;
	self->Data[0] = ID;
	self->Data[1] = GameID;

	lua_newtable(L);
	self->InjectedRef = lua_ref(L, -1);
	lua_settop(L, T + 4);

	LunaUtil::GetRegKey(L, "ClassMeta");
	lua_setmetatable(L, T + 4);
	lua_pushinteger(L, ID);
	lua_pushvalue(L, T + 4);
	lua_settable(L, T + 2);
	lua_replace(L, T + 1);
	lua_settop(L, T + 1);
	return;
}