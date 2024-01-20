#include "stdafx.h"

#include "LunaApi/LunaUtil/LunaUtil.h"
#include "LunaApi/LunaEvent/LunaEvent.h"
#include "LunaApi/LunaEnum/LunaEnum.h"

#include "PvZ/DataArray.h"
#include "PvZ/Plant.h"
#include "PvZ/Lawn.h"
#include "LunaPlant.h"
#include "PlantDefClass.h"
#include "UIContainerClass.h"
#include "GridItemClass.h"
#include "ZombieClass.h"

using namespace Luna::Event;
using namespace Luna::Class;
using namespace Luna::Enum;
using namespace Fields;

namespace
{
	EnumList* Enums;
}
Plant* GetPlant(lua_State* L, int I, std::string ParamName, bool AcceptNil)
{
	auto self = AssertIsA(L, I, "Plant", ParamName, AcceptNil);
	if (self == NULL && AcceptNil) return NULL;
	return (Plant*)self->GetBase();
}

namespace
{
	std::vector<DWORD> UpdateEntries = { 0x463E43 };
	LunaEventRef OnUpdate;

	std::vector<DWORD> ClickEntries = { 0x4122E9 };
	LunaEventRef OnClick;

	std::vector<DWORD> CreatedEntries = { 0x45E7B0 };
	LunaEventRef OnCreated;

	std::vector<DWORD> FireEntries = {
		0x45F282,
		0x46492F,
		0x464AF3,
		0x464B0A,
		0x464B26,
		0x464B68,
		0x464B7F,
		0x464B9C,
		0x464BC5,
		0x464C2F
	};
	LunaEventRef OnFire;

	std::vector<DWORD> EatenEntries = { 0x52F689 };
	LunaEventRef OnEaten;
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

	bool __stdcall ClickCaller(Plant* self, int X, int Y)
	{
		auto L = Luna::GlobalLState;
		int T = lua_gettop(L);
		LunaPlant::Source->New(L, self);
		auto Proxy = (LunaInstance*)lua_touserdata(L, -1);
		auto Skip = false;

		if (Proxy->Associations[0] != NULL)
		{
			lua_getref(L, Proxy->Associations[0]);
			lua_pushvalue(L, -2);
			lua_pushinteger(L, X);
			lua_pushinteger(L, Y);
			lua_pcall(L, 3, 1, 0);
			lua_pop(L, 2);

			Skip = lua_toboolean(L, -1);
		}
		
		lua_pushvalue(L, T + 1);
		lua_pushinteger(L, X);
		lua_pushinteger(L, Y);
		OnClick.GetEvent()->Call(L, 3);

		return Skip;
	}
	void __declspec(naked) ClickHandler()
	{
		__asm
		{
			push [esp+0x8]
			push [esp+0x8]
			push esi
			call ClickCaller

			cmp al, 01
			je Skip

			push [esp+0x8]
			push [esp+0x8]
			mov eax, 0x466390
			call eax

			Skip:
			ret 0x8
		}
	}

	void __stdcall CreatedCaller(Plant* self)
	{
		auto L = LUNA_STATE;
		int T = lua_gettop(L);

		self->Health = LunaPlantDef::PlantHP[self->Type];
		self->MaxHealth = self->Health;

		LunaPlant::Source->New(L, self);
		OnCreated.GetEvent()->Call(L, 1);

		lua_settop(L, T);
	}
	void __declspec(naked) CreatedHandler()
	{
		__asm
		{
			push [esp+0x4]
			call CreatedCaller
			ret 0xC
		}
	}

	bool __stdcall FireCaller(Plant* self, Zombie* Target, int Lane, bool IsSecondary)
	{
		auto L = LUNA_STATE;
		int T = lua_gettop(L);
		lua_newtable(L);

		LunaPlant::Source->New(L, self);
		lua_pushboolean(L, IsSecondary);
		lua_pushvalue(L, T + 1);
		OnFire.GetEvent()->Call(L, 3);

		lua_pushstring(L, "Skip");
		lua_gettable(L, T + 1);
		auto Skip = GetBool(L, -1);
		
		lua_settop(L, T);
		return Skip;
	}
	void __declspec(naked) FireHandler()
	{
		__asm
		{
			push [esp+0x10]
			push [esp+0x10]
			push [esp+0x10]
			push [esp+0x10]
			call FireCaller
			
			cmp al, 00
			je NoSkip
			ret 0x10

			NoSkip:
			mov eax, 0x466E00
			jmp eax
		}
	}

	bool __stdcall EatenCaller(Plant* self, Zombie* Zombie)
	{
		auto L = LUNA_STATE;
		int T = lua_gettop(L);
		lua_newtable(L);

		LunaPlant::Source->New(L, self);
		LunaZombie::Source->New(L, Zombie);
		lua_pushvalue(L, T + 1);
		OnEaten.GetEvent()->Call(L, 3);

		lua_pushstring(L, "Skip");
		lua_gettable(L, T + 1);
		auto Skip = GetBool(L, -1);

		lua_settop(L, T);
		return Skip;
	}
	void __declspec(naked) EatenHandler()
	{
		__asm
		{
			push ecx
			push [esp+0x8]
			push ecx
			call EatenCaller
			pop ecx

			cmp al, 00
			je NoSkip
			ret 0x4

			NoSkip:
			mov eax, 0x52FB40
			jmp eax
		}
	}
}

void SetupEvents()
{
	OnUpdate = LunaEvent::New("Plant.OnUpdate", UpdateHandler, UpdateEntries, true);
	OnClick = LunaEvent::New("Plant.OnClick", ClickHandler, ClickEntries, true, true);
	OnCreated = LunaEvent::New("Plant.OnCreated", CreatedHandler, CreatedEntries, true);
	OnFire = LunaEvent::New("Plant.OnFire", FireHandler, FireEntries, true, true);
	OnEaten = LunaEvent::New("Plant.OnEaten", EatenHandler, EatenEntries, true, true);
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

namespace Methods
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
int Methods::AddParticles(lua_State* L)
{
	auto self = GetPlant(L, 1);
	auto Effect = Enums->L_ParticleEffects->AssertEnum(L, 2, "Effect");
	auto X = GetInt(L, 3);
	auto Y = GetInt(L, 4);
	auto Layer = GetInt(L, 5);
	CONST DWORD Function = 0x45EEA0;

	int RenderPos = self->RenderOrder + Layer;
	auto Center = self->Bounds.GetCenter() + IVector2(X, Y);
	__asm
	{
		mov edi, self
		push Effect
		push RenderPos
		push Center.Y
		push Center.X
		call Function
	}
	return 0;
}
int Methods::Fire(lua_State* L)
{
	auto self = GetPlant(L, 1);
	auto IsSecondary = (bool)lua_toboolean(L, 2);
	self->Fire(NULL, self->Lane, IsSecondary);
	return 0;
}
int Methods::SpawnGrave(lua_State* L)
{
	auto self = GetPlant(L, 1);
	auto Kill = GetBool(L, 2, true);
	auto Effects = GetBool(L, 3, true);
	auto Grave = self->MyLawn->AddGrave(self->Column, self->Lane, Effects, Kill);
	LunaGridItem::Source->New(L, Grave);
	return 1;
}
int Methods::Kill(lua_State* L)
{
	GetPlant(L, 1)->Die();
}
#pragma endregion

LunaPlant* LunaPlant::Source = new LunaPlant();
int LunaPlant::Init(lua_State* L)
{
	Enums = Enum::GetEnums(L);
	Source->AllowsInjection = true;
	Source->SetName("Plant");
	Source->AddSubClass("GameObject");
	Source->CustomBase = true;

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
	IntField::New("Layer", 0x20, Source);

	// Plant Specific
	FunctionField::New("OnClick", 0, Source);
	LunaPlantDef::PlantDefField::New("Type", 0x24, Source);
	LunaPlantDef::PlantDefField::New("ImitaterType", 0x138, Source);
	EnumField::New("State", 0x3C, Enums->L_PlantState, Source);
	EnumField::New("BungeeState", 0x134, Enums->L_PlantBungeeState, Source);

	IntField::New("Column", 0x28, Source);
	IntField::New("AnimCounter", 0x2C, Source);
	BlnField::New("Dead", 0x44, Source);
	BlnField::New("Squished", 0x45, Source);

	IntField::New("HP", 0x40, Source);
	IntField::New("Health", 0x40, Source);
	IntField::New("MaxHP", 0x44, Source);
	IntField::New("MaxHealth", 0x44, Source);
	BlnField::New("Offensive", 0x48, Source);
	IntField::New("VanishTimer", 0x4C, Source);
	IntField::New("SpecialTimer", 0x50, Source);
	IntField::New("StateTimer", 0x54, Source);
	IntField::New("ActionTimer", 0x58, Source);
	IntField::New("MaxActionTimer", 0x5C, Source);
	IntField::New("ActionRate", 0x5C, Source);
	RctField::New("PlantRect", 0x60, Source);
	RctField::New("PlantAttackRect", 0x70, Source);
	IV2Field::New("TargetPosition", 0x80, Source);
	IntField::New("InitialLane", 0x88, Source);
	IntField::New("FireTimer", 0x90, Source);
	IntField::New("BlinkTimer", 0xB0, Source);
	IntField::New("EatenTimer", 0xB4, Source);
	IntField::New("FlashTimer", 0xB8, Source);
	IntField::New("GlowTimer", 0xBC, Source);
	FV2Field::New("ShakeOffset", 0xC0, Source);
	IntField::New("WakingTiemr", 0x130, Source);
	BlnField::New("IsAsleep", 0x143, Source, true);
	BlnField::New("OnLawn", 0x144, Source);
	BlnField::New("Highlighted", 0x145, Source, true);
	IntField::New("ZenGardenIndex", 0x13C, Source);
	
#pragma endregion
#pragma region Methods
	Source->Methods["AddParticles"] = Methods::AddParticles;
	Source->Methods["Fire"] = Methods::Fire;
	Source->Methods["SpawnGrave"] = Methods::SpawnGrave;
#pragma endregion

	SetupEvents();

	lua_newtable(L);
	
	lua_pushstring(L, "OnUpdate");
	OnUpdate.Push(L);
	lua_settable(L, -3);

	lua_pushstring(L, "OnCreated");
	OnCreated.Push(L);
	lua_settable(L, -3);

	lua_pushstring(L, "OnClick");
	OnClick.Push(L);
	lua_settable(L, -3);

	lua_pushstring(L, "OnFire");
	OnFire.Push(L);
	lua_settable(L, -3);

	lua_pushstring(L, "OnEaten");
	OnEaten.Push(L);
	lua_settable(L, -3);

	lua_setglobal(L, "Plant");

	return 0;
}