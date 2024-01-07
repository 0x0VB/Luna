#pragma once
#include "PvZ/Definitions.h"
#include "LunaApi/LunaEvent/LunaEvent.h"
#include "LunaApi/LunaClass/LunaClass.h"

/// <summary>
/// Detects the type of this Image using its vtable and constructs it accordingly, pushing it onto the lua stack.
/// </summary>
void CreateLunaImage(lua_State* L, void* At);

/// <summary>
/// Asserts the object at Index as an Image and returns it if so, substituting if necessary.
/// </summary>
Luna::Class::LunaInstance* GetLunaImage(lua_State* L, int Index = 1, std::string ParamName = "NO_PARAM_NAME", bool AcceptNil = false, bool Substitute = false);

class ImageField : public Luna::Class::LunaField
{
public:
	virtual void __index(lua_State* L) override;
	virtual void __newindex(lua_State* L) override;
	static ImageField* New(const char* Name, DWORD Offset, Luna::Class::LunaClass* Class, bool ReadOnly = false)
	{ return Luna::Class::LunaField::New<ImageField>(Name, Offset, Class, ReadOnly); }
};

class Luna::Class::LunaImage : public Luna::Class::LunaClass
{
public:
	static LunaClass* Source;
	static int Init(lua_State* L);
};

class Luna::Class::LunaMemImage : public Luna::Class::LunaClass
{
public:
	static LunaClass* Source;
	static int Init(lua_State* L);
};

class Luna::Class::LunaDDImage : public Luna::Class::LunaClass
{
public:
	static LunaClass* Source;
	static int Init(lua_State* L);
};