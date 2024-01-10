#include "stdafx.h"

#include "LunaApi/LunaUtil/LunaUtil.h"

#include "PvZ/DataArray.h"
#include "PvZ/Plant.h"
#include "LunaPlant.h"

using namespace Luna::Class;
using namespace Fields;

LunaPlant* LunaPlant::Source = new LunaPlant();
int LunaPlant::Init(lua_State* L)
{
	Source->AllowsInjection = true;
	Source->SetName("Plant");
	Source->AddSubClass("GameObject");
	
#pragma region Fields
	IntField::New("Type", 0x24, Source);
#pragma endregion
	return 0;
}

void* LunaPlant::GetBase(LunaInstance* self)
{
	auto Array = (DataArray<Plant>*)self->Base;
	auto ID = self->Data[0];
	return Array->TryToGet(ID);
}

void LunaPlant::New(lua_State* L, void* Param)
{
	auto NewPlant = (DataArrayItem<Plant>*)Param;
	auto ID = NewPlant->ID;

	int T = lua_gettop(L);
	LunaUtil::GetRegKey(L, "PlantRef");// T + 1
	lua_pushinteger(L, ID);
	lua_gettable(L, -2);
	if (!lua_isnil(L, -1))
	{
		lua_replace(L, T + 1);
		lua_settop(L, T + 1);
		return;
	}

	lua_settop(L, T + 1);
	lua_pushinteger(L, ID);

	auto self = (LunaInstance*)lua_newuserdata(L, sizeof(LunaInstance));
	self->Base = &(NewPlant->Item.MyLawn->Plants);
	self->Class = this;
	self->Data[0] = ID;

	LunaUtil::GetRegKey(L, "ClassMeta");
	lua_setmetatable(L, T + 2);
}