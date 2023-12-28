#pragma once

#pragma region Lua Functions
int Luna::Event::Call(lua_State* L)
{
	AssertType(1, "LunaEvent", "self");
	auto self = (LunaEvent*)lua_touserdata(L, 1);
	self->Call(lua_gettop(L) - 1);
	return 0;
}

int Luna::Event::Connect(lua_State* L)
{
	AssertType(1, "LunaEvent", "self");
	AssertType(2, "function", "Connection");
	LunaUtil::Local("EventConnections");
	auto self = (LunaEvent*)lua_touserdata(L, 1);
	if (!self->Hooked) self->Hook();
	lua_pushlightuserdata(L, self);
	lua_gettable(L, -2);
	lua_pushvalue(L, 2);
	lua_pushboolean(L, 1);
	lua_settable(L, -3);
	return 0;
}

int Luna::Event::Disconnect(lua_State* L)
{
	AssertType(1, "LunaEvent", "self");
	AssertType(2, "function", "Connection");
	LunaUtil::Local("EventConnections");
	lua_pushlightuserdata(L, lua_touserdata(L, 1));
	lua_gettable(L, -2);
	lua_pushvalue(L, 2);
	lua_pushnil(L);
	lua_settable(L, -3);
	return 0;
}

int Luna::Event::DisconnectAll(lua_State* L)
{
	AssertType(1, "LunaEvent", "self");
	AssertType(2, "function", "Connection");
	LunaUtil::Local("EventConnections");
	lua_pushlightuserdata(L, lua_touserdata(L, 1));
	lua_newtable(L);
	lua_settable(L, -3);
	return 0;
}
#pragma endregion

#pragma region Meta Methods
int Luna::Event::__index(lua_State* L)
{
	auto FieldString = lua_tostring(L, 2);
	if (!lua_isstring(L, 2)) LunaIO::ThrowError(LunaUtil::Type(2) + " is not a valid member of LunaEvent.");
	if (FieldString[0] == '_') LunaIO::ThrowError(std::string(FieldString) + " is not a valid member of LunaEvent.");
	LunaUtil::Local("EventMeta");
	lua_pushvalue(L, 2);
	lua_gettable(L, -2);
	if (lua_isnil(L, -1)) LunaIO::ThrowError(std::string(FieldString) + " is not a valid member of LunaEvent.");
	return 1;
}
int Luna::Event::__newindex(lua_State* L) { LunaIO::ThrowError("LunaEvents cannot be modified."); return 0; }
int Luna::Event::__tostring(lua_State* L)
{
	auto self = (LunaEvent*)lua_touserdata(L, 1);
	lua_pushstring(L, self->Name);
	return 1;
}
int Luna::Event::__call(lua_State* L) { Call(L); return 0; }
#pragma endregion

int Luna::Event::Init(lua_State* L)
{
	lua_newtable(L);
	LunaUtil::Local("EventConnections", -1, true);
	lua_newtable(L);
	lua_pushstring(L, "__type");
	lua_pushstring(L, "LunaEvent");
	lua_settable(L, -3);
#define SetMeta(N) lua_pushstring(L, #N); lua_pushcclosure(L, N, 0); lua_settable(L, -3);

	SetMeta(__index);
	SetMeta(__newindex);
	SetMeta(__tostring);
	SetMeta(__call);

	SetMeta(Call);
	SetMeta(Connect);
	SetMeta(Disconnect);
	SetMeta(DisconnectAll);

	LunaUtil::Local("EventMeta", -1, true);
	return 0;
}