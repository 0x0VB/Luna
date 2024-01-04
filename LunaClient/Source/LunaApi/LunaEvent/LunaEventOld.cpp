#include "stdafx.h"
#include "LunaEventOld.h"

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
}

void Luna::Event::LunaEvent::Push(lua_State* L)
{
	LunaUtil::Local(L, "EventMeta");
	lua_pushlightuserdata(L, this);
	lua_gettable(L, -2);
}

void Luna::Event::LunaEvent::Call(lua_State* L, int ArgCount)
{
	std::cout << "Calling!" << "\n";
	int T = lua_gettop(L);
	int RT = T - ArgCount;
	
	for (int i = 0; i < MAX_CONNECTIONS; i++)
	{
		auto Connection = Connections[i];
		if (Connection.ConnectedFunction.Pointer == 0) continue;

		lua_f Func = Connection.ConnectedFunction;
		lua_State* C = Connection.ConnectionState;
		Func.Push(C);
		for (int i = 1; i <= ArgCount; i++)
			lua_xpush(L, C, RT + i);
		lua_call(C, ArgCount, 0);
	}

	lua_settop(L, RT);
}

Luna::Event::LunaEvent* Luna::Event::LunaEvent::New(const char* Name, void* Handler, DWORD Entries[], size_t EntryCount, bool AutoHook)
{
	int T = lua_gettop(LUNA_STATE);
	auto self = (LunaEvent*)lua_newuserdata(LUNA_STATE, sizeof(LunaEvent));// 1
	self->Setup(Name, Handler, Entries, EntryCount, AutoHook);
	LunaUtil::Local(LUNA_STATE, "EventMeta");// 2
	lua_pushlightuserdata(LUNA_STATE, self);// Key
	lua_pushvalue(LUNA_STATE, T + 1);// Real self (Value)
	lua_settable(LUNA_STATE, T + 2);
	lua_setmetatable(LUNA_STATE, T + 1);
	lua_settop(LUNA_STATE, T);
	return self;
}

int Luna::Event::Call(lua_State* L)
{
	AssertType(L, 1, "LunaEvent", "self");
	auto self = (LunaEvent*)lua_touserdata(L, 1);
	self->Call(L, lua_gettop(L) - 1);
	return 0;
}

int Luna::Event::Connect(lua_State* L)
{
	AssertType(L, 1, "LunaEvent", "self");
	AssertType(L, 2, "function", "Connection");
	auto self = (LunaEvent*)lua_touserdata(L, 1);
	auto Connection = LunaConnection(L, 2);
	
	for (int i = 0; i < MAX_CONNECTIONS; i++)
	{
		auto Conn = self->Connections[i];
		if (Conn.ConnectedFunction.Pointer == 0)
		{
			self->Connections[i] = Connection;
			std::cout << i << "\n";
			return 0;
		}
	}
	self->Connections[MAX_CONNECTIONS - 1] = Connection;
	return 0;
}

int Luna::Event::Disconnect(lua_State* L)
{
	AssertType(L, 1, "LunaEvent", "self");
	AssertType(L, 2, "function", "Connection");
	auto self = (LunaEvent*)lua_touserdata(L, 1);
	lua_f Function = lua_f(L, 2);
	return 0;
}

int Luna::Event::DisconnectAll(lua_State* L)
{
	AssertType(L, 1, "LunaEvent", "self");
	AssertType(L, 2, "function", "Connection");
	LunaEvent* self = (LunaEvent*)lua_touserdata(L, 1);
	return 0;
}
#pragma endregion

#pragma region Meta Methods
int Luna::Event::__index(lua_State* L)
{
	auto FieldString = lua_tostring(L, 2);
	if (!lua_isstring(L, 2)) LunaIO::ThrowError(L, LunaUtil::Type(L, 2) + " is not a valid member of LunaEvent.");
	if (FieldString[0] == '_') LunaIO::ThrowError(L, std::string(FieldString) + " is not a valid member of LunaEvent.");
	LunaUtil::Local(L, "EventMeta");
	lua_pushvalue(L, 2);
	lua_gettable(L, -2);
	if (lua_isnil(L, -1)) LunaIO::ThrowError(L, std::string(FieldString) + " is not a valid member of LunaEvent.");
	return 1;
}
int Luna::Event::__newindex(lua_State* L) { LunaIO::ThrowError(L, "LunaEvents cannot be modified."); return 0; }
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
	lua_pushstring(L, "__type");
	lua_pushstring(L, "LunaEvent");
	lua_settable(L, -3);

	SetMeta(__index);
	SetMeta(__newindex);
	SetMeta(__tostring);
	SetMeta(__call);

	SetMeta(Call);
	SetMeta(Connect);
	SetMeta(Disconnect);
	SetMeta(DisconnectAll);

	LunaUtil::Local(L, "EventMeta", -1, true);
	return 0;
}