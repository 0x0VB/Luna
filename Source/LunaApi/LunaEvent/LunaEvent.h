#pragma once
#include "Luau/lua.h"
#include "framework.h"

namespace Luna::Event
{
	class LunaEvent
	{
		void SHook(DWORD Entry);

	public:
		void* Handler;
		CONST DWORD* Entries;
		char Name[32];
		size_t EntryCount;
		bool Hooked;

		void Hook();
		void Setup(const char* EventName, void* EventHandler, CONST DWORD* EventEntries, size_t EventEntryCount = 1, bool AutoHook = false);
		void Push();
		void Call(int ArgCount);

		// Creates and returns a new event with the given parameters, pushes the lua userdata of this event onto the stack.
		static LunaEvent* New(const char* Name, void* Handler, DWORD Entries[], size_t EntryCount = 1, bool AutoHook = false);
	};

	int Call(lua_State* L);
	int Connect(lua_State* L);
	int Disconnect(lua_State* L);
	int DisconnectAll(lua_State* L);

	int __index(lua_State* L);
	int __newindex(lua_State* L);
	int __tostring(lua_State* L);
	int __call(lua_State* L);

	int Init(lua_State* L);
}