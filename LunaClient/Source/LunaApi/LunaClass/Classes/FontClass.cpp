#include "stdafx.h"
#include "FontClass.h"

#include "LunaApi/LunaUtil/LunaUtil.h"
#include "LunaApi/LunaIO/LunaIO.h"
#include "Luna.h"

#include "PvZ/LawnApp.h"
#include "PvZ/Font.h"

#include "LunaBase.h"

using namespace Luna::Class;
using namespace Fields;


LunaClass* LunaFont::Source = new LunaClass();
LunaClass* LunaIFont::Source = new LunaClass();
LunaClass* LunaSysFont::Source = new LunaClass();

int LunaFont::Init(lua_State* L)
{

	return 0;
}

int LunaIFont::Init(lua_State* L)
{

	return 0;
}

int LunaSysFont::Init(lua_State* L)
{

	return 0;
}