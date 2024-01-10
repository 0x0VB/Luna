#pragma once
#include "PvZ/Definitions.h"
#include "PvZ/DialogButton.h"
#include "LunaApi/LunaEvent/LunaEvent.h"
#include "LunaApi/LunaClass/LunaClass.h"

namespace // Methods
{
	int MsgBox(lua_State* L);
	void SetupEvents();
}

class Luna::Class::LunaApp : public Luna::Class::LunaClass
{
public:
	static int LunaInstanceRef;
	static LunaClass* Source;
	static int Init(lua_State* L);
};