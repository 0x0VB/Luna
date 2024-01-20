#include "stdafx.h"
#include "GridItemClass.h"
#include "PvZ/GridItem.h"
#include "LunaApi/LunaUtil/LunaUtil.h"
#include "UIContainerClass.h"
#include "ZombieClass.h"
#include "PlantDefClass.h"

using namespace Luna::Event;
using namespace Luna::Class;
using namespace Luna::Enum;
using namespace Fields;
GridItem* GetGridItem(lua_State* L, int I, std::string ParamName, bool AcceptNil)
{
	auto self = AssertIsA(L, I, "GridItem", ParamName, AcceptNil);
	if (self == NULL && AcceptNil) return NULL;
	return (GridItem*)self->GetBase();
}

namespace
{
	EnumList* Enums;
}

namespace
{
	int Kill(lua_State* L)
	{
		auto self = GetGridItem(L);
		self->Die();
		return 0;
	}
	int SpawnZombie(lua_State* L)
	{
		auto self = GetGridItem(L);
		auto Type = GetInt(L, 2);
		auto Zombie = self->MyLawn->AddZombie((ZombieType)Type, self->Lane);
		Zombie->Rise(self->Column, self->Lane);

		LunaZombie::Source->New(L, Zombie);
		return 1;
	}
}


LunaGridItem* LunaGridItem::Source = new LunaGridItem();
int LunaGridItem::Init(lua_State* L)
{
	Enums = Enum::GetEnums(L);
	Source->AllowsInjection = true;
	Source->SetName("GridItem");
	Source->AddSubClass("GameObject");
	Source->CustomBase = true;

	LunaPlantDef::PlantDefField::New("VasePlantType", 0x40, Source);
	UIObjectField::New("Lawn", 0x4, Source);
	UIObjectField::New("Game", 0x4, Source);

	IntField::New("Type", 0x8, Source);
	IntField::New("State", 0xC, Source);

	IV2Field::New("GridPosition", 0x10, Source);
	IntField::New("Column", 0x10, Source);
	IntField::New("Lane", 0x14, Source);

	IntField::New("Counter", 0x18, Source);
	IntField::New("Layer", 0x1C, Source);
	BlnField::New("Dead", 0x20, Source);

	FV2Field::New("Position", 0x24, Source);
	FltField::New("X", 0x24, Source);
	FltField::New("Y", 0x28, Source);

	FV2Field::New("Goal", 0x2C, Source);
	FltField::New("GoalX", 0x2C, Source);
	FltField::New("GoalY", 0x30, Source);

	BlnField::New("Highlighted", 0x48, Source);
	IntField::New("TransparentTimer", 0x4C, Source);
	IntField::New("SunCount", 0x50, Source);

	Source->Methods["Kill"] = Kill;
	Source->Methods["SpawnZombie"] = SpawnZombie;

	return 0;
}

void* LunaGridItem::GetBase(LunaInstance* self)
{
	auto L = LUNA_STATE;
	auto Array = (DataArray<GridItem>*)self->Base;
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

void LunaGridItem::New(lua_State* L, void* Param)
{
	auto NewPlant = (DataArrayItem<GridItem>*)Param;
	auto ID = NewPlant->ID;
	auto Game = NewPlant->Item.MyLawn;
	auto NoGame = Game == NULL;
	auto GameID = (NoGame) ? 0 : (Game->GameID);

	int T = lua_gettop(L);
	lua_pushinteger(L, GameID);
	lua_gettable(L, LUA_REGISTRYINDEX);// T + 1: GameRef
	lua_pushstring(L, "GridItems");// T + 2: PlantRef
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
	self->Base = (NoGame) ? Param : &(Game->GridItems);
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