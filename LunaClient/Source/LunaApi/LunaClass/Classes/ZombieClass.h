#pragma once
#include "PvZ/Definitions.h"
#include "LunaApi/LunaEvent/LunaEvent.h"
#include "LunaApi/LunaClass/LunaClass.h"

Zombie* GetZombie(lua_State* L, int I = 1, std::string ParamName = "self", bool AcceptNil = false);
class Luna::Class::LunaZombie : public Luna::Class::LunaClass
{
public:
	static LunaZombie* Source;
	static int Init(lua_State* L);
	virtual void* GetBase(LunaInstance* Instance) override;
	virtual void New(lua_State* L, void* Param) override;
};