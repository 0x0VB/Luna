#pragma once
#include "PvZ/Definitions.h"
#include "LunaApi/LunaEvent/LunaEvent.h"
#include "LunaApi/LunaClass/LunaClass.h"

Plant* GetPlant(lua_State* L, int I, std::string ParamName = "self", bool AcceptNil = false);

class Luna::Class::LunaPlant : public Luna::Class::LunaClass
{
public:
	static LunaPlant* Source;
	static int Init(lua_State* L);
	virtual void* GetBase(LunaInstance* Instance) override;
	virtual void New(lua_State* L, void* Param) override;
};