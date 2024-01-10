#include "stdafx.h"

#include "LunaApi/LunaUtil/LunaUtil.h"
#include "LunaApi/LunaEvent/LunaEvent.h"

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

LunaPlant* LunaPlant::Source = new LunaPlant();
int LunaPlant::Init(lua_State* L)
{
	Source->AllowsInjection = true;
	Source->SetName("Plant");
	Source->AddSubClass("GameObject");
	
#pragma region Fields
	IntField::New("Type", 0x24, Source);
#pragma endregion
	SetupEvents();

	lua_newtable(L);
	
	lua_pushstring(L, "OnUpdate");
	OnUpdate.Push(L);
	lua_settable(L, -3);

	lua_setglobal(L, "Plant");

	return 0;
}

void* LunaPlant::GetBase(LunaInstance* self)
{
	auto L = LUNA_STATE;
	auto Array = (DataArray<Plant>*)self->Base;
	auto ID = self->Data[0];
	int T = lua_gettop(L);
	void* Result;

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
	auto GameID = Game->GameID;

	int T = lua_gettop(L);
	lua_pushinteger(L, GameID);
	lua_gettable(L, LUA_REGISTRYINDEX);// T + 1: GameRef
	lua_pushstring(L, "Plants");// T + 2: PlantRef
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
	self->Base = &(Game->Plants);
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