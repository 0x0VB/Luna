#pragma once
#include "PvZ/Definitions.h"
#include "LunaApi/LunaEvent/LunaEvent.h"
#include "LunaApi/LunaClass/LunaClass.h"
#include "PvZ/ButtonListener.h"

class Luna::Class::LunaStoneButton : public Luna::Class::LunaClass
{
public:
	static LunaClass* Source;
	static int Init(lua_State* L);
	static int Constructor(lua_State* L);
	static Sexy::ButtonListener* LunaListener;
};