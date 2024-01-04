#pragma once
#include "PvZ/Definitions.h"
#include "LunaApi/LunaEvent/LunaEvent.h"
#include "LunaApi/LunaClass/LunaClass.h"

class Luna::Class::LunaUIRoot : public Luna::Class::LunaClass
{
public:
	static LunaClass* Source;
	static int Init(lua_State* L);
};