#pragma once
#include "LunaApi/LunaClass/LunaClass.h"

class Luna::Class::LunaAppBase : public Luna::Class::LunaClass
{
public:
	static LunaClass* Source;
	static int Init(lua_State* L);
};