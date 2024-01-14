#include "stdafx.h"

#include "LunaBase.h"
#include "PlantDefClass.h"

#include "LunaApi/LunaClass/LunaClass.h"
#include "LunaApi/LunaUtil/LunaUtil.h"

#include "PvZ/Plant.h"
#include "PvZ/PlantDefinition.h"

using namespace Luna::Event;
using namespace Luna::Class;
using namespace Fields;


#pragma region PlantDefField
void PlantDefField::__index(lua_State* L)
{
	FBase(SeedType);
	int Type = *Base;
}
void PlantDefField::__newindex(lua_State* L)
{
	FBase(SeedType);
	AssertType(L, 3, "PlantDefinition", Name);

}
#pragma endregion

#pragma region Fields
void LunaPlantDef::HealthField::__index(lua_State* L)
{
	int Index = (int)lua_touserdata(L, 1);
	lua_pushinteger(L, PlantHP[Index]);
}

void LunaPlantDef::HealthField::__newindex(lua_State* L)
{
	AssertType(L, 3, "number", Name);
	int Index = (int)lua_touserdata(L, 1);
	int Value = (int)lua_tonumber(L, 2);
	PlantHP[Index] = Value;
}

void LunaPlantDef::IndexField::__index(lua_State* L)
{
	auto self = GetSelf(L);
	int Index = (int)self->Base;
	auto Definition = PlantDefinitions + Index;
	lua_pushinteger(L, *((int*)Definition + Offset));
}

void LunaPlantDef::IndexField::__newindex(lua_State* L)
{
	CheckReadOnly(L);
	AssertType(L, 3, "number", Name);
	int Index = (int)((LunaInstance*)lua_touserdata(L, 1))->Base;
	auto Definition = PlantDefinitions + Index;
	auto Value = ((int*)Definition + Offset);
	*Value = GetInt(L, 3);
}

void LunaPlantDef::PlantNameField::__index(lua_State* L)
{
	int Index = (int)((LunaInstance*)lua_touserdata(L, 1))->Base;
	auto Definition = PlantDefinitions + Index;
	lua_pushstring(L, Definition->PlantName);
}

void LunaPlantDef::PlantNameField::__newindex(lua_State* L)
{
	AssertType(L, 3, "string", Name);
	int Index = (int)((LunaInstance*)lua_touserdata(L, 1))->Base;
	auto Definition = PlantDefinitions + Index;
	Definition->PlantName = lua_tostring(L, 3);
}

void LunaPlantDef::New(lua_State* L, void* Param)
{
	int T = lua_gettop(L);
	int I = (int)Param;
	if (PlantDefReferences[I] != NULL)
	{
		lua_getref(L, PlantDefReferences[I]);
		return;
	}

	auto self = (LunaInstance*)lua_newuserdata(L, sizeof(LunaInstance));
	self->Base = Param;
	self->Class = this;

	lua_pushvalue(L, -1);
	PlantDefReferences[I] = lua_ref(L, -1);
	lua_settop(L, T + 1);

	LunaUtil::GetRegKey(L, "ClassMeta");
	lua_setmetatable(L, T + 1);
}
#pragma endregion

#pragma region Methods
int Swap(lua_State* L)
{
	int I0 = (int)((LunaInstance*)lua_touserdata(L, 1))->Base;
	int I1 = (int)((LunaInstance*)lua_touserdata(L, 2))->Base;
	auto D0 = PlantDefinitions[I0];
	auto D1 = PlantDefinitions[I1];
	PlantDefinitions[I0] = D1;
	PlantDefinitions[I1] = D0;
	return 0;
}
#pragma endregion

LunaPlantDef* LunaPlantDef::Source = new LunaPlantDef();
int LunaPlantDef::PlantDefReferences[100] = { 0 };
int LunaPlantDef::PlantHP[100] = { 0 };
int LunaPlantDef::Init(lua_State* L)
{
	Source->AllowsInjection = false;
	Source->SetName("PlantData");
	Source->Inherit(LunaBase::Source);

	HealthField::New("Health", 0, Source);
	PlantNameField::New("Name", 0, Source);
	IndexField::New("PacketIndex", 3, Source);
	IndexField::New("SunCost", 4, Source);
	IndexField::New("Cooldown", 5, Source);
	IndexField::New("ActionRate", 7, Source);
	memset(PlantHP, 300, PlantCapacity * 4);

	Source->Methods["Swap"] = Swap;

	// Create PlantDefs

	lua_newtable(L);// [1]
	
	for (int i = 0; i < 53; i++)
	{
		auto Definition = PlantDefinitions + i;
		lua_pushstring(L, Definition->PlantName);
		Source->New(L, (void*)i);
		lua_settable(L, -3);
		std::cout << i << ": " << Definition->PlantName << "\n";
	}
	lua_setglobal(L, "Plants");

	return 0;
}