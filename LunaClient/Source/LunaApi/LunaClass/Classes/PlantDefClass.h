#pragma once
#include "PvZ/Definitions.h"
#include "LunaApi/LunaEvent/LunaEvent.h"
#include "LunaApi/LunaClass/LunaClass.h"

using namespace Luna::Class;
class PlantDefField : public Luna::Class::LunaField
{
	virtual void __index(lua_State* L) override;
	virtual void __newindex(lua_State* L) override;
	DefNewField(PlantDefField)
};

class Luna::Class::LunaPlantDef : public Luna::Class::LunaClass
{
public:
	virtual void New(lua_State* L, void* Param) override;

	static LunaPlantDef* Source;
	static int Init(lua_State* L);

	static const size_t PlantCapacity = 100;
	static int PlantHP[PlantCapacity];
	static int PlantDefReferences[PlantCapacity];

	static class HealthField : public LunaField
	{
	public:
		void __index(lua_State* L) override;
		void __newindex(lua_State* L) override;
		DefNewField(HealthField)
	};

	static class IndexField : public LunaField
	{
	public:
		void __index(lua_State* L) override;
		void __newindex(lua_State* L) override;
		DefNewField(IndexField)
	};

	static class PlantNameField : public LunaField
	{
	public:
		void __index(lua_State* L) override;
		void __newindex(lua_State* L) override;
		DefNewField(PlantNameField)
	};
};