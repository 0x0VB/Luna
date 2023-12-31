#include "stdafx.h"
#include "LunaEvent.h"

#include "LunaApi/LunaUtil/LunaUtil.h"
#include "LunaApi/LunaIO/LunaIO.h"
#include "Luna.h"

#pragma region Lua Functions

void Luna::Event::LunaEvent::SHook(DWORD Entry)
{
	BYTE* JmpInst = (BYTE*)Entry;
	DWORD* JumpAddress = (DWORD*)(Entry + 1);
	DWORD RelativeAddress = (DWORD)Handler - Entry - 5;
	DWORD OldProtection;
	VirtualProtect((LPVOID)Entry, 5, PAGE_EXECUTE_READWRITE, &OldProtection);

	*JmpInst = 0xE9;// JMP OPCode
	*JumpAddress = RelativeAddress;// Address to jump to

	DWORD _;
	VirtualProtect((LPVOID)Entry, 5, OldProtection, &_);
}

void Luna::Event::LunaEvent::Hook()
{
	if (Hooked) return;
	Hooked = true;
	for (int i = 0; i < EntryCount; i++) SHook(Entries[i]);
}

void Luna::Event::LunaEvent::Setup(const char* EventName, void* EventHandler, CONST DWORD* EventEntries, size_t EventEntryCount, bool AutoHook)
{
	memcpy(Name, EventName, std::strlen(EventName) + 1);
	Handler = EventHandler;
	Entries = EventEntries;
	EntryCount = EventEntryCount;
	Hooked = false;
	if (AutoHook) Hook();

	LunaUtil::Local("EventConnections");
	lua_pushlightuserdata(Luna::GlobalLState, this);
	lua_newtable(Luna::GlobalLState);
	lua_settable(Luna::GlobalLState, -3);
	lua_pop(Luna::GlobalLState, 1);
}

void Luna::Event::LunaEvent::Push() {
	LunaUtil::Local("EventMeta");
	lua_pushlightuserdata(Luna::GlobalLState, this);
	lua_gettable(Luna::GlobalLState, -2);
}

void Luna::Event::LunaEvent::Call(int ArgCount)
{
	int T = lua_gettop(Luna::GlobalLState);
	int RT = T - ArgCount;
	int GConn = T + 1;
	int Conn = T + 2;
	int K = T + 3;
	if (!Hooked) { lua_settop(Luna::GlobalLState, RT); return; }
	LunaUtil::Local("EventConnections");
	lua_pushlightuserdata(Luna::GlobalLState, this);
	lua_gettable(Luna::GlobalLState, GConn);

	lua_pushnil(Luna::GlobalLState);
	while (lua_next(Luna::GlobalLState, Conn))
	{
		lua_copy(Luna::GlobalLState, -2, -1);
		for (int i = 1; i <= ArgCount; i++) lua_pushvalue(Luna::GlobalLState, RT + i);
		if (lua_pcall(Luna::GlobalLState, ArgCount, 0, 0) != LUA_OK) LunaIO::Print("[" + std::string(Name) + "]: " + lua_tostring(Luna::GlobalLState, -1), LunaIO::Error);
		lua_settop(Luna::GlobalLState, K);
	}
	lua_settop(Luna::GlobalLState, RT);
}

Luna::Event::LunaEvent* Luna::Event::LunaEvent::New(const char* Name, void* Handler, DWORD Entries[], size_t EntryCount, bool AutoHook)
{
	int T = lua_gettop(Luna::GlobalLState);
	auto self = (LunaEvent*)lua_newuserdata(Luna::GlobalLState, sizeof(LunaEvent));// 1
	self->Setup(Name, Handler, Entries, EntryCount, AutoHook);
	LunaUtil::Local("EventMeta");// 2
	lua_pushlightuserdata(Luna::GlobalLState, self);// 3
	lua_pushvalue(Luna::GlobalLState, T + 1);
	lua_settable(Luna::GlobalLState, T + 2);
	lua_setmetatable(Luna::GlobalLState, T + 1);
	lua_settop(Luna::GlobalLState, T);
	return self;
}

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