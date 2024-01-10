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
	LunaUtil::GetRegKey(L, "ClassRef");
	lua_pushlightuserdata(L, Param);
}