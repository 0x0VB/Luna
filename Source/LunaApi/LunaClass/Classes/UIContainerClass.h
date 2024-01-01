#pragma once
#include "PvZ/Definitions.h"
#include "LunaApi/LunaEvent/LunaEvent.h"
#include "LunaApi/LunaClass/LunaClass.h"

using namespace Luna::Class;
using namespace Luna::Event;
namespace
{
	std::map<DWORD, LunaClass*> UI_VTABLES;
}

/// <summary>
/// Detects the type of this UI object using its vtable and constructs it accordingly, pushing it onto the lua stack.
/// </summary>
void CreateUIObject(lua_State* L, void* At);

/// <summary>
/// Asserts the object at Index as a UIObject and returns it if so.
/// </summary>
LunaInstance* GetUIObject(lua_State* L, int Index = 1, std::string ParamName = "NO_PARAM_NAME");

class UIObjectField : public LunaField
{
public:
	virtual void __index(lua_State* L) override;
	virtual void __newindex(lua_State* L) override;
	DefNewField(UIObjectField)
};

class Luna::Class::LunaUIContainer : public LunaClass
{
public:
	static LunaClass* Source;
	static int Init(lua_State* L);
};