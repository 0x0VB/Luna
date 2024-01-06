#include "stdafx.h"
#include "LunaEvent.h"

#include "LunaApi/LunaUtil/LunaUtil.h"
#include "LunaApi/LunaIO/LunaIO.h"
#include "Luna.h"

using namespace Luna::Event;

void Luna::Event::LunaEvent::SetupHook()
{
	if (Hooked || IsLuaEvent) return;
	Hooked = true;
	for (const auto& Entry : Entries)
		Hook(Entry);
}

void Luna::Event::LunaEvent::Hook(DWORD Entry)
{
	BYTE* JmpInst = (BYTE*)Entry;
	DWORD* JumpAddress = (DWORD*)(Entry + 1);
	DWORD RelativeAddress = (DWORD)Handler - Entry - 5;
	DWORD OldProtection;
	VirtualProtect((LPVOID)Entry, 5, PAGE_EXECUTE_READWRITE, &OldProtection);

	*JmpInst = 0xE9;	// JMP OPCode
	*JumpAddress = RelativeAddress;	// Address to jump to

	DWORD _;
	VirtualProtect((LPVOID)Entry, 5, OldProtection, &_);
}

void Luna::Event::LunaEvent::Call(lua_State* CL, size_t ArgCount)
{
	int T = lua_gettop(CL);
	int RT = T - ArgCount;

	for (const auto& Connection : Connections)
	{
		lua_getref(Connection.L, Connection.RefIdx);
		for (int i = 1; i <= ArgCount; i++)
			lua_xpush(CL, Connection.L, RT + i);
		if (lua_pcall(Connection.L, ArgCount, 0, 0) != LUA_OK)
		{
			auto ErrorMessage = lua_tostring(Connection.L, -1);
			LunaIO::Print(std::string("[") + Name + "]: " + ErrorMessage, LunaIO::Error);
		}
	}

	lua_settop(CL, RT);
}

LunaEventRef::LunaEventRef(int Ref) { EventRef = Ref; }
void LunaEventRef::Push(lua_State* L) { lua_ref(L, EventRef); }
LunaEvent* LunaEventRef::GetEvent()
{
	lua_getref(LUNA_STATE, EventRef);
	auto Event = lua_touserdata(LUNA_STATE, -1);
	lua_pop(LUNA_STATE, 1);
	return (LunaEvent*)Event;
}

LunaEventRef Luna::Event::LunaEvent::New(const char* Name, lua_CFunction Handler)
{
	auto self = (LunaEvent*)lua_newuserdata(LUNA_STATE, sizeof(LunaEvent));// 1
	// Setup
	{
		self->EventRef = lua_ref(LUNA_STATE, -1);
		memcpy(self->Name, Name, 32);
		self->LHandler = Handler;
		self->IsLuaEvent = true;
		self->Hooked = true;
	}
	LunaUtil::Local(LUNA_STATE, "EventMeta");
	lua_setmetatable(LUNA_STATE, -2);
	lua_pop(LUNA_STATE, 1);

	return LunaEventRef(self->EventRef);
}

LunaEventRef Luna::Event::LunaEvent::New(const char* Name, void* Handler, std::vector<DWORD> Entries, bool AutoHook)
{
	auto self = (LunaEvent*)lua_newuserdata(LUNA_STATE, sizeof(LunaEvent));// 1
	// Setup
	{
		self->EventRef = lua_ref(LUNA_STATE, -1);
		memcpy(self->Name, Name, 32);
		self->IsLuaEvent = false;
		self->Entries = Entries;
		self->Handler = Handler;
		self->Hooked = false;
		if (AutoHook)
			self->SetupHook();
	}
	LunaUtil::Local(LUNA_STATE, "EventMeta");
	lua_setmetatable(LUNA_STATE, -2);
	lua_pop(LUNA_STATE, 1);

	return LunaEventRef(self->EventRef);
}


#pragma region API Methods
int Luna::Event::LunaEvent::Connect(lua_State* L)
{
	AssertType(L, 1, "LunaEvent", "self");
	AssertType(L, 2, "function", "Connection");
	auto self = (LunaEvent*)lua_touserdata(L, 1);

	if (self->Connections.size() >= LUNA_MAX_CONNECTIONS)
		LunaIO::ThrowError(L, "Cannot connect more than " + std::to_string(LUNA_MAX_CONNECTIONS) + " connections to a single event.");

	if (self->Connections.size() == 0 && !self->Hooked)
		self->SetupHook();
	
	auto Connection = (LunaConnection*)lua_newuserdata(L, sizeof(LunaConnection));
	Connection->RefIdx = lua_ref(L, 2);			// create ref of the callback function;
	Connection->L = L;
	Connection->EventRef = self->EventRef;
	self->Connections.push_back(*Connection);	// store new connection

	LunaUtil::Local(L, "ConnectionMeta");
	lua_setmetatable(L, -2);

	return 1;
}

int Luna::Event::LunaEvent::Fire(lua_State* L)
{
	AssertType(L, 1, "LunaEvent", "self");
	auto self = (LunaEvent*)lua_touserdata(L, 1);
	self->Call(L, lua_gettop(L) - 1);

	return 0;
}

int Luna::Event::LunaEvent::DisconnectAll(lua_State* L)
{
	AssertType(L, 1, "LunaEvent", "self");
	LunaEvent* self = (LunaEvent*)lua_touserdata(L, 1);

	for (const auto& Connection : self->Connections)
		lua_unref(L, Connection.RefIdx);
	self->Connections.clear();

	return 0;
}

int Luna::Event::LunaConnection::Disconnect(lua_State* L)
{
	AssertType(L, 1, "LunaConnection", "self");
	LunaConnection* self = (LunaConnection*)lua_touserdata(L, 1);
	lua_getref(L, self->EventRef);
	LunaEvent* Event = (LunaEvent*)lua_touserdata(L, -1);

	for (const auto& Connection : Event->Connections)
	{
		if (Connection.RefIdx == self->RefIdx && Connection.EventRef == self->EventRef)
		{
			lua_unref(L, Connection.RefIdx);
			Event->Connections.erase(std::remove(Event->Connections.begin(), Event->Connections.end(), Connection), Event->Connections.end());
			break;
		}
	}

	return 0;
}
#pragma endregion

#pragma region LunaConnection Meta Methods
int Luna::Event::LunaConnection::__index(lua_State* L)
{
	auto FieldString = lua_tostring(L, 2);
	if (!lua_isstring(L, 2))
		LunaIO::ThrowError(L, LunaUtil::Type(L, 2) + " is not a valid member of LunaConnection.");
	if (FieldString[0] == '_')
		LunaIO::ThrowError(L, std::string(FieldString) + " is not a valid member of LunaConnection.");

	LunaUtil::Local(L, "ConnectionMeta");
	lua_pushvalue(L, 2);
	lua_gettable(L, -2);

	if (lua_isnil(L, -1))
		LunaIO::ThrowError(L, std::string(FieldString) + " is not a valid member of LunaConnection.");

	return 1;
}

int Luna::Event::LunaConnection::__newindex(lua_State* L)
{
	LunaIO::ThrowError(L, "LunaConnection cannot be modified.");
	return 0;
}

int Luna::Event::LunaConnection::__tostring(lua_State* L)
{
	auto self = (LunaConnection*)lua_touserdata(L, 1);
	lua_getref(L, self->EventRef);
	LunaEvent* Event = (LunaEvent*)lua_touserdata(L, -1);
	
	std::string ToStr = std::format("{}#LunaConnection", Event->Name);
	lua_pushstring(L, ToStr.c_str());
	return 1;
}
#pragma endregion

#pragma region LunaEvent Meta Methods
int Luna::Event::LunaEvent::__index(lua_State* L)
{
	auto FieldString = lua_tostring(L, 2);
	if (!lua_isstring(L, 2))
		LunaIO::ThrowError(L, LunaUtil::Type(L, 2) + " is not a valid member of LunaEvent.");
	if (FieldString[0] == '_')
		LunaIO::ThrowError(L, std::string(FieldString) + " is not a valid member of LunaEvent.");

	LunaUtil::Local(L, "EventMeta");
	lua_pushvalue(L, 2);
	lua_gettable(L, -2);

	if (lua_isnil(L, -1))
		LunaIO::ThrowError(L, std::string(FieldString) + " is not a valid member of LunaEvent.");

	return 1;
}

int Luna::Event::LunaEvent::__newindex(lua_State* L) {
	LunaIO::ThrowError(L, "LunaEvent cannot be modified.");
	return 0;
}

int Luna::Event::LunaEvent::__tostring(lua_State* L)
{
	auto self = (LunaEvent*)lua_touserdata(L, 1);
	lua_pushstring(L, self->Name);
	return 1;
}

int Luna::Event::LunaEvent::__call(lua_State* L) {
	Fire(L);
	return 0;
}
#pragma endregion

int Luna::Event::Init(lua_State* L)
{
	lua_newtable(L);
	lua_pushstring(L, "__type");
	lua_pushstring(L, "LunaEvent");
	lua_settable(L, -3);

	SetMetaByName(LunaEvent::__index, "__index");
	SetMetaByName(LunaEvent::__newindex, "__newindex");
	SetMetaByName(LunaEvent::__tostring, "__tostring");
	SetMetaByName(LunaEvent::__call, "__call");

	SetMetaByName(LunaEvent::Fire, "Fire");
	SetMetaByName(LunaEvent::Connect, "Connect");
	SetMetaByName(LunaEvent::DisconnectAll, "DisconnectAll");

	LunaUtil::Local(L, "EventMeta", -1, true);
	
	lua_newtable(L);
	lua_pushstring(L, "__type");
	lua_pushstring(L, "LunaConnection");
	lua_settable(L, -3);

	SetMetaByName(LunaConnection::__index, "__index");
	SetMetaByName(LunaConnection::__newindex, "__newindex");
	SetMetaByName(LunaConnection::__tostring, "__tostring");

	SetMetaByName(LunaConnection::Disconnect, "Disconnect");

	LunaUtil::Local(L, "ConnectionMeta", -1, true);
	return 0;
}