#pragma once
#include "PvZ/Definitions.h"
#include "LunaApi/LunaEvent/LunaEvent.h"
#include "LunaApi/LunaClass/LunaClass.h"

class Luna::Class::LunaPlant : public Luna::Class::LunaClass
{
public:
	static LunaPlant* Source;
	static int Init(lua_State* L);
	virtual void* GetBase(LunaInstance* Instance) override;
	virtual void New(lua_State* L, void* Param) override;
};