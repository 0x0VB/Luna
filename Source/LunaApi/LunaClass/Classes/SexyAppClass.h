#pragma once
#include "LunaApi/LunaClass/LunaClass.h"

class Luna::Class::Classes::LunaAppBase : public Luna::Class::Base::LunaClass
{
public:
	static Base::LunaClass* Source;
	static int Init(lua_State* L);
};