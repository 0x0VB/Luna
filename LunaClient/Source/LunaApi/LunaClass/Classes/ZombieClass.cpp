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

	std::vector<DWORD> UpdateEntries = { 0x401D79, 0x401D8E, 0x413124 };
	std::map<DWORD, const char*> UpdateReason = {
		{0x413129, "Game"},
		{0x401D93, "Almanac"},
		{0x401D7E, "Almanac"}
	};
	LunaEventRef OnUpdate;

	std::vector<DWORD> DeathEntries = { 0x53051B };
	LunaEventRef OnDeath;

	std::vector<DWORD> CreatedEntries = { 0x40DE90 };
	LunaEventRef OnCreated;

	std::vector<DWORD> DamagedEntries = { 0x5317C0 };
	LunaEventRef OnDamaged;
}

namespace
{
	void __stdcall UpdateCaller(Zombie* self, DWORD Reason)
	{
		auto L = Luna::GlobalLState;
		auto T = lua_gettop(L);
		lua_newtable(L);

		LunaZombie::Source->New(L, self);
		lua_pushstring(L, UpdateReason[Reason]);
		lua_pushvalue(L, T + 1);
		OnUpdate.GetEvent()->Call(L, 3);

		lua_pushstring(L, "Skip");
		lua_gettable(L, T + 1);
		auto Skip = GetBool(L, -1);
		lua_settop(L, T);

		if (Skip) return;
		self->Update();
	}
	void __declspec(naked) UpdateHandler()
	{
		__asm
		{
			push [esp]
			push eax
			call UpdateCaller
			ret
		}
	}

	void __stdcall DeathCaller(Zombie* self)
	{
		auto L = Luna::GlobalLState;
		auto T = lua_gettop(L);

		LunaZombie::Source->New(L, self);
		OnDeath.GetEvent()->Call(L, 1);
		lua_settop(L, T);
	}
	void __declspec(naked) DeathHandler()
	{
		__asm
		{
			push [esp+04]
			call DeathCaller

			push [esp+04]
			mov eax, 0x530850
			call eax

			ret 0x4
		}
	}

	Zombie* __stdcall CreatedCaller(Zombie* self)
	{
		auto L = Luna::GlobalLState;
		auto T = lua_gettop(L);

		LunaZombie::Source->New(L, self);
		OnCreated.GetEvent()->Call(L, 1);
		lua_settop(L, T);

		return self;
	}
	void __declspec(naked) CreatedHandler()
	{
		__asm
		{
			push eax
			call CreatedCaller
			ret 0x8
		}
	}

	BOOL DAMAGE_SKIP;
	DWORD DAMAGE_AMMOUNT;
	DWORD DAMAGE_FLAGS;
	void __stdcall DamagedCaller(Zombie* self, int Damage, int DFlags)
	{
		auto L = Luna::GlobalLState;
		auto T = lua_gettop(L);
		lua_newtable(L);

		LunaZombie::Source->New(L, self);
		lua_pushinteger(L, Damage);
		lua_pushinteger(L, DFlags);
		lua_pushvalue(L, T + 1);
		OnDamaged.GetEvent()->Call(L, 4);

		lua_pushstring(L, "Skip");
		lua_gettable(L, T + 1);
		DAMAGE_SKIP = GetBool(L, -1);

		lua_pushstring(L, "Damage");
		lua_gettable(L, T + 1);
		DAMAGE_AMMOUNT = GetInt(L, -1, Damage);

		lua_pushstring(L, "Flags");
		lua_gettable(L, T + 1);
		DAMAGE_FLAGS = GetInt(L, -1, DFlags);
		lua_settop(L, T);
	}
	void __declspec(naked) DamagedHandler()
	{
		__asm
		{
			push eax
			push [esp+0x08]
			push esi
			call DamagedCaller

			cmp DAMAGE_SKIP, 01
			je Skip

			// No Skip
			mov eax, DAMAGE_FLAGS
			mov edx, DAMAGE_AMMOUNT
			mov [esp+0x4], edx

			// Vanilla Code
			push ecx
			mov ecx, [esi+0x28]
			cmp ecx, 0x10
			mov edx, 0x5317C7
			jmp edx

			Skip:
			ret 0x4
		}
	}

	void SetupEvents(lua_State* L)
	{
		OnUpdate = LunaEvent::New("Zombie.OnUpdate", UpdateHandler, UpdateEntries, true, true);
		OnDeath = LunaEvent::New("Zombie.OnDeath", DeathHandler, DeathEntries, true, true);
		OnCreated = LunaEvent::New("Zombie.OnCreated", CreatedHandler, CreatedEntries, true);
		OnDamaged = LunaEvent::New("Zombie.OnDamaged", DamagedHandler, DamagedEntries, true);
	}
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
	int SpawnGrave(lua_State* L)
	{
		auto self = GetZombie(L);
		auto Cell = self->GetCell();
		auto DoEffects = GetBool(L, 2, true);
		auto KillPlants = GetBool(L, 3, true);
		auto Grave = self->MyLawn->AddGrave(Cell.X, self->Lane, DoEffects, KillPlants);
		LunaGridItem::Source->New(L, Grave);
		return 1;
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
	Source->Methods["SpawnGrave"] = SpawnGrave;

	SetupEvents(L);
	lua_newtable(L);

	lua_pushstring(L, "OnUpdate");
	OnUpdate.Push(L);
	lua_settable(L, -3);

	lua_pushstring(L, "OnCreated");
	OnCreated.Push(L);
	lua_settable(L, -3);

	lua_pushstring(L, "OnDamaged");
	OnDamaged.Push(L);
	lua_settable(L, -3);

	lua_pushstring(L, "OnDeath");
	OnDeath.Push(L);
	lua_settable(L, -3);

	lua_setglobal(L, "Zombie");

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