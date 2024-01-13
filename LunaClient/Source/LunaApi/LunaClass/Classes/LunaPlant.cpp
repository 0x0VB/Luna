#include "stdafx.h"

#include "LunaApi/LunaUtil/LunaUtil.h"
#include "LunaApi/LunaEvent/LunaEvent.h"
#include "LunaApi/LunaEnum/LunaEnum.h"

#include "PvZ/DataArray.h"
#include "PvZ/Plant.h"
#include "PvZ/Lawn.h"
#include "LunaPlant.h"

using namespace Luna::Event;
using namespace Luna::Class;
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

namespace
{
	using namespace Luna::Enum;
	EnumLib* L_PlantState;
	EnumLib* L_PlantBungeeState;

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

	void SetupEnums(lua_State* L)
	{
		lua_PlantState(L);
		lua_PlantBungeeState(L);
	}
}

LunaPlant* LunaPlant::Source = new LunaPlant();
int LunaPlant::Init(lua_State* L)
{
	Source->AllowsInjection = true;
	Source->SetName("Plant");
	Source->AddSubClass("GameObject");
	SetupEnums(L);
	
#pragma region Fields
	IntField::New("Type", 0x24, Source);
	EnumField::New("State", 0x3C, L_PlantState, Source);
	EnumField::New("BungeeState", 0x134, L_PlantBungeeState, Source);
#pragma endregion
	SetupEvents();

	lua_newtable(L);
	
	lua_pushstring(L, "OnUpdate");
	OnUpdate.Push(L);
	lua_settable(L, -3);

	lua_setglobal(L, "Plant");

	return 0;
}