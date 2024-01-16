#include "stdafx.h"

#include "LunaApi/LunaUtil/LunaUtil.h"
#include "LunaApi/LunaEvent/LunaEvent.h"
#include "LunaApi/LunaEnum/LunaEnum.h"
#include "LunaApi/LunaEnum/EnumList.h"

#include "PvZ/DataArray.h"
#include "PvZ/Plant.h"
#include "PvZ/Lawn.h"
#include "LunaPlant.h"
#include "PlantDefClass.h"
#include "UIContainerClass.h"

using namespace Luna::Event;
using namespace Luna::Class;
using namespace Luna::Enum;
using namespace Enums;
using namespace Fields;

namespace
{
	std::vector<DWORD> UpdateEntries = { 0x463E43 };
	LunaEventRef OnUpdate;
}

namespace
{
	bool __stdcall UpdateCaller(Plant* self)
	{
		auto L = LUNA_STATE;
		int T = lua_gettop(L);
		lua_newtable(L);

		LunaPlant::Source->New(L, self);
		lua_pushvalue(L, -2);
		OnUpdate.GetEvent()->Call(L, 2);

		lua_pushstring(L, "Skip");
		lua_gettable(L, -2);
		bool Skip = lua_toboolean(L, -1);
		lua_settop(L, T);
		return Skip;
	}

	void __declspec(naked) UpdateHandler()
	{
		__asm
		{
			push ebx
			call UpdateCaller
			cmp al, 01
			je Exit

			mov dl, [ebx+0x144]
			mov eax, 0x463E49
			jmp eax

			Exit:
			pop ebx
			ret
		}
	}
}

void SetupEvents()
{
	OnUpdate = LunaEvent::New("Plant.OnUpdate", UpdateHandler, UpdateEntries, true);
}

void* LunaPlant::GetBase(LunaInstance* self)
{
	auto L = LUNA_STATE;
	auto Array = (DataArray<Plant>*)self->Base;
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

void LunaPlant::New(lua_State* L, void* Param)
{
	auto NewPlant = (DataArrayItem<Plant>*)Param;
	auto ID = NewPlant->ID;
	auto Game = NewPlant->Item.MyLawn;
	auto NoGame = Game == NULL;
	auto GameID = (NoGame) ? 0 : (Game->GameID);

	int T = lua_gettop(L);
	lua_pushinteger(L, GameID);
	lua_gettable(L, LUA_REGISTRYINDEX);// T + 1: GameRef
	lua_pushstring(L, "Plants");// T + 2: PlantRef
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
	self->Base = (NoGame) ? Param : &(Game->Plants);
	self->Class = this;
	self->Data[0] = ID;
	self->Data[1] = GameID;

	LunaUtil::GetRegKey(L, "ClassMeta");
	lua_setmetatable(L, T + 4);
	lua_pushinteger(L, ID);
	lua_pushvalue(L, T + 4);
	lua_settable(L, T + 2);
	lua_replace(L, T + 1);
	lua_settop(L, T + 1);
	return;
}

namespace // Methods
{
	// Game Objects
	int GetNearestProjectile(lua_State* L);
	int GetNearestGridItem(lua_State* L);
	int GetNearestPickup(lua_State* L);
	int GetNearestZombie(lua_State* L);
	int GetNearestPlant(lua_State* L);

	int GetProjectilesInRadius(lua_State* L);
	int GetGridItemsInRadius(lua_State* L);
	int GetPickupsInRadius(lua_State* L);
	int GetZombiesInRadius(lua_State* L);
	int GetPlantsInRadius(lua_State* L);

	int SpawnGrave(lua_State* L);
	int Fire(lua_State* L);

	// Plant Specific
	int Kill(lua_State* L);
	int Damage(lua_State* L);
	int SetSleep(lua_State* L);
	int AddParticles(lua_State* L);
	int IsOnHighGround(lua_State* L);
	int DoPiercingDamage(lua_State* L);
	int StarfruitDetect(lua_State* L);
	int IsSunProducer(lua_State* L);
	int FindSquashTarget(lua_State* L);
	int RemoveEffects(lua_State* L);
	int Squish(lua_State* L);
	int IsOnGround(lua_State* L);
	int GetProjectileOffset(lua_State* L);
	int DoSpecial(lua_State* L);
	int FindTargetZombie(lua_State* L);
}

#pragma region Methods
int AddParticles(lua_State* L)
{

	return 0;
}
#pragma endregion

LunaPlant* LunaPlant::Source = new LunaPlant();
int LunaPlant::Init(lua_State* L)
{
	Source->AllowsInjection = true;
	Source->SetName("Plant");
	Source->AddSubClass("GameObject");
	
#pragma region Fields
	// Game Object
	UIObjectField::New("Lawn", 0x4, Source);
	UIObjectField::New("Game", 0x4, Source);

	RctField::New("Bounds", 0x8, Source);
	IV2Field::New("Position", 0x8, Source);
	IntField::New("X", 0x8, Source);
	IntField::New("Y", 0xC, Source);
	IV2Field::New("Size", 0x10, Source);
	IntField::New("W", 0x10, Source);
	IntField::New("H", 0x14, Source);
	BlnField::New("Visible", 0x18, Source);
	IntField::New("Lane", 0x1C, Source);
	IntField::New("Row", 0x1C, Source);
	IntField::New("ZIndex", 0x20, Source);

	// Plant Specific
	LunaPlantDef::PlantDefField::New("Type", 0x24, Source);
	LunaPlantDef::PlantDefField::New("ImitaterType", 0x140, Source);
	EnumField::New("State", 0x3C, L_PlantState, Source);
	EnumField::New("BungeeState", 0x134, L_PlantBungeeState, Source);

	IntField::New("Column", 0x28, Source);
	IntField::New("AnimCounter", 0x2C, Source);
	BlnField::New("AnimPing", 0x30, Source);
	BlnField::New("Dead", 0x44, Source);
	BlnField::New("Squished", 0x45, Source);

	IntField::New("HP", 0x48, Source);
	IntField::New("Health", 0x48, Source);
	IntField::New("MaxHP", 0x4C, Source);
	IntField::New("MaxHealth", 0x4C, Source);
	BlnField::New("Offensive", 0x50, Source);
	IntField::New("VanishTimer", 0x54, Source);
	IntField::New("SpecialTimer", 0x58, Source);
	IntField::New("StateTimer", 0x5C, Source);
	IntField::New("ActionTimer", 0x60, Source);
	IntField::New("MaxActionTimer", 0x64, Source);
	IntField::New("ActionRate", 0x64, Source);
	RctField::New("PlantRect", 0x68, Source);
	RctField::New("PlantAttackRect", 0x78, Source);
	IV2Field::New("TargetPosition", 0x88, Source);
	IntField::New("InitialLane", 0x90, Source);
	IntField::New("FireTimer", 0x98, Source);
	IntField::New("BlinkTimer", 0xB8, Source);
	IntField::New("EatenTimer", 0xBC, Source);
	IntField::New("FlashTimer", 0xC0, Source);
	IntField::New("GlowTimer", 0xC4, Source);
	FV2Field::New("ShakeOffset", 0xC8, Source);
	IntField::New("WakingTiemr", 0x138, Source);
	BlnField::New("IsAsleep", 0x13C, Source, true);
	BlnField::New("OnLawn", 0x13D, Source);
	BlnField::New("IsOnBungee", 0x13E, Source);
	BlnField::New("Highlighted", 0x13F, Source, true);
	IntField::New("ZenGardenIndex", 0x144, Source);
	
#pragma endregion
	SetupEvents();

	lua_newtable(L);
	
	lua_pushstring(L, "OnUpdate");
	OnUpdate.Push(L);
	lua_settable(L, -3);

	lua_setglobal(L, "Plant");

	return 0;
}