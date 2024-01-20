#pragma once
#include "PvZ/Definitions.h"
#include "LunaApi/LunaEvent/LunaEvent.h"
#include "LunaApi/LunaClass/LunaClass.h"

GridItem* GetGridItem(lua_State* L, int I = 1, std::string ParamName = "self", bool AcceptNil = false);
class Luna::Class::LunaGridItem: public Luna::Class::LunaClass
{
public:
	static LunaGridItem* Source;
	static int Init(lua_State* L);
	virtual void* GetBase(LunaInstance* Instance) override;
	virtual void New(lua_State* L, void* Param) override;
};