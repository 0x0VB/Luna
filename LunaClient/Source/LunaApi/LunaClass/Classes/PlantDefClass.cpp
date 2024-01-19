#include "stdafx.h"

#include "LunaBase.h"
#include "PlantDefClass.h"

#include "LunaApi/LunaClass/LunaClass.h"
#include "LunaApi/LunaUtil/LunaUtil.h"

#include "PvZ/Definitions.h"
#include "PvZ/PlantDefinition.h"
#include "PvZ/Plant.h"

using namespace Luna::Event;
using namespace Luna::Class;
using namespace Fields;


#pragma region PlantDefField
void LunaPlantDef::PlantDefField::__index(lua_State* L)
{
	FBase(SeedType);
	int Type = *Base;
	lua_getref(L, LunaPlantDef::PlantDefReferences[Type]);
}
void LunaPlantDef::PlantDefField::__newindex(lua_State* L)
{
	FBase(SeedType);
	auto Def = Assert(L, 3, true, Name);
	if (Def == NULL)
		*Base = SEED_NONE;
	else
		*Base = Def->SeedType;
}
PlantDefinition* LunaPlantDef::Assert(lua_State* L, int I, bool AcceptNil, std::string ParamName)
{
	int T = lua_gettop(L);
	I = (I > 0) ? I : T + I + 1;
	bool Provided = T >= I;

	if (AcceptNil && (!Provided || lua_isnil(L, I)))
		return NULL;
	else if (!Provided)
	{
		lua_pushnil(L);
		lua_replace(L, I);
	}
	else if (lua_isnumber(L, I))
	{
		int Value = (int)lua_tonumber(L, I);
		if (Value >= CurrentPlantCount)
			LunaIO::ThrowError(L, "This PlantType is not defined.");
		return PlantDefinitions + Value;
	}
	else if (lua_isstring(L, I))
	{
		std::string Value = GetString(L, I);
		if (!PlantMap.contains(Value))
			LunaIO::ThrowError(L, "This PlantType is not defined.");
		return PlantDefinitions + PlantMap[Value];
	}
	AssertType(L, I, "PlantData", ParamName);
	auto Data = (LunaInstance*)lua_touserdata(L, I);
	return PlantDefinitions + (int)Data->Base;
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
	int Index = (int)((LunaInstance*)lua_touserdata(L, 1))->Base;
	int Value = (int)lua_tonumber(L, 3);
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
	self->Data[0] = I;

	lua_pushvalue(L, -1);
	PlantDefReferences[I] = lua_ref(L, -1);
	lua_settop(L, T + 1);

	LunaUtil::GetRegKey(L, "ClassMeta");
	lua_setmetatable(L, T + 1);
}

void LunaPlantDef::__tostring(lua_State* L)
{
	int Type = (int)GetSelf(L)->Base;
	lua_pushstring(L, PlantDefinitions[Type].PlantName);
}
#pragma endregion

#pragma region Methods
int Swap(lua_State* L)
{
	AssertType(L, 1, "PlantData", "Plant1");
	AssertType(L, 2, "PlantData", "Plant2");

	auto P0 = (LunaInstance*)lua_touserdata(L, 1);
	auto P1 = (LunaInstance*)lua_touserdata(L, 2);
	int I0 = (int)(P0)->Base;
	int I1 = (int)(P1)->Base;
	auto D0 = PlantDefinitions[I0];
	auto D1 = PlantDefinitions[I1];

	PlantDefinitions[I0] = D1;
	PlantDefinitions[I1] = D0;

	P0->Base = (void*)I1;
	P1->Base = (void*)I0;

	return 0;
}
#pragma endregion

#define RegisterPlant(Name, Idx) lua_pushstring(L, Name); Source->New(L, (void*)Idx); lua_settable(L, -3); CurrentPlantCount++; PlantMap[Name] = Idx;
LunaPlantDef* LunaPlantDef::Source = new LunaPlantDef();
std::map<std::string, int> LunaPlantDef::PlantMap = {};
int LunaPlantDef::PlantDefReferences[100] = { 0 };
int LunaPlantDef::PlantHP[100] = { 0 };
int LunaPlantDef::CurrentPlantCount = 0;

int LunaPlantDef::Init(lua_State* L)
{
	Source->AllowsInjection = false;
	Source->SetName("PlantData");
	Source->Inherit(LunaBase::Source);
	Source->CustomBase = true;

	HealthField::New("Health", 0, Source);
	PlantNameField::New("Name", 0, Source);
	IndexField::New("PacketIndex", 3, Source);
	IndexField::New("SunCost", 4, Source);
	IndexField::New("Cooldown", 5, Source);
	IndexField::New("ActionRate", 7, Source);

	for (int i = 0; i < PlantCapacity; i++)
		PlantHP[i] = 300;

	PlantHP[SEED_PUMPKIN] = 3000;
	PlantHP[SEED_WALLNUT] = 3000;
	PlantHP[SEED_TALLNUT] = 6000;

	Source->Methods["Swap"] = Swap;

#pragma region Create PlantDefs
	lua_newtable(L);// [1]	
	RegisterPlant("Peashooter", SEED_PEASHOOTER);
	RegisterPlant("Sunflower", SEED_SUNFLOWER);
	RegisterPlant("CherryBomb", SEED_CHERRYBOMB);
	RegisterPlant("Wallnut", SEED_WALLNUT);
	RegisterPlant("PotatoMine", SEED_POTATOMINE);
	RegisterPlant("SnowPea", SEED_SNOWPEA);
	RegisterPlant("Chomper", SEED_CHOMPER);
	RegisterPlant("Repeater", SEED_REPEATER);
	RegisterPlant("Puffshroom", SEED_PUFFSHROOM);
	RegisterPlant("Sunshroom", SEED_SUNSHROOM);
	RegisterPlant("Fumeshroom", SEED_FUMESHROOM);
	RegisterPlant("Gravebuster", SEED_GRAVEBUSTER);
	RegisterPlant("Hypnoshroom", SEED_HYPNOSHROOM);
	RegisterPlant("Scaredyshroom", SEED_SCAREDYSHROOM);
	RegisterPlant("Iceshroom", SEED_ICESHROOM);
	RegisterPlant("Doomshroom", SEED_DOOMSHROOM);
	RegisterPlant("Lilypad", SEED_LILYPAD);
	RegisterPlant("Squash", SEED_SQUASH);
	RegisterPlant("Threepeater", SEED_THREEPEATER);
	RegisterPlant("Tanglekelp", SEED_TANGLEKELP);
	RegisterPlant("Jalapeno", SEED_JALAPENO);
	RegisterPlant("Spikeweed", SEED_SPIKEWEED);
	RegisterPlant("Torchwood", SEED_TORCHWOOD);
	RegisterPlant("Tallnut", SEED_TALLNUT);
	RegisterPlant("Seashroom", SEED_SEASHROOM);
	RegisterPlant("Plantern", SEED_PLANTERN);
	RegisterPlant("Cactus", SEED_CACTUS);
	RegisterPlant("Blover", SEED_BLOVER);
	RegisterPlant("SplitPea", SEED_SPLITPEA);
	RegisterPlant("Starfruit", SEED_STARFRUIT);
	RegisterPlant("Pumpkin", SEED_PUMPKIN);
	RegisterPlant("Magnetshroom", SEED_MAGNETSHROOM);
	RegisterPlant("Cabbagepult", SEED_CABBAGEPULT);
	RegisterPlant("Flowerpot", SEED_FLOWERPOT);
	RegisterPlant("Kernelpult", SEED_KERNELPULT);
	RegisterPlant("InstantCoffee", SEED_INSTANT_COFFEE);
	RegisterPlant("Garlic", SEED_GARLIC);
	RegisterPlant("Umbrella", SEED_UMBRELLA);
	RegisterPlant("Marigold", SEED_MARIGOLD);
	RegisterPlant("Melonpult", SEED_MELONPULT);
	RegisterPlant("GatlingPea", SEED_GATLINGPEA);
	RegisterPlant("TwinSunflower", SEED_TWINSUNFLOWER);
	RegisterPlant("Gloomshroom", SEED_GLOOMSHROOM);
	RegisterPlant("Cattail", SEED_CATTAIL);
	RegisterPlant("Wintermelon", SEED_WINTERMELON);
	RegisterPlant("GoldMagnet", SEED_GOLD_MAGNET);
	RegisterPlant("Spikerock", SEED_SPIKEROCK);
	RegisterPlant("Cobcannon", SEED_COBCANNON);
	RegisterPlant("Imitater", SEED_IMITATER);
	RegisterPlant("ExplodeONut", SEED_EXPLODE_O_NUT);
	RegisterPlant("GiantWallnut", SEED_GIANT_WALLNUT);
	RegisterPlant("Sprout", SEED_SPROUT);
	RegisterPlant("Leftpeater", SEED_LEFTPEATER);
	LunaUtil::SetRegKey(L, "PlantData");
#pragma endregion

	return 0;
}