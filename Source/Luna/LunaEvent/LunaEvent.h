#pragma once
namespace Luna::Event
{
	class LunaEvent
	{
		void SHook(DWORD Entry)
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

	public:
		void* Handler;
		CONST DWORD* Entries;
		char Name[32];
		size_t EntryCount;
		bool Hooked;

		void Hook()
		{
			if (Hooked) return;
			Hooked = true;
			for (int i = 0; i < EntryCount; i++) SHook(Entries[i]);
		}
		void Setup(const char* EventName, void* EventHandler, CONST DWORD* EventEntries, size_t EventEntryCount = 1, bool AutoHook = false)
		{
			memcpy(Name, EventName, std::strlen(EventName) + 1);
			Handler = EventHandler;
			Entries = EventEntries;
			EntryCount = EventEntryCount;
			Hooked = false;
			if (AutoHook) Hook();

			LunaUtil::Local("EventConnections");
			lua_pushlightuserdata(L, this);
			lua_newtable(L);
			lua_settable(L, -3);
			lua_pop(L, 1);
		}
		void Push() { LunaUtil::Local("EventMeta"); lua_pushlightuserdata(L, this); lua_gettable(L, -2); }
		void Call(int ArgCount)
		{
			int T = lua_gettop(L);
			int RT = T - ArgCount;
			int GConn = T + 1;
			int Conn = T + 2;
			int K = T + 3;
			if (!Hooked) { lua_settop(L, RT); return; }
			LunaUtil::Local("EventConnections");
			lua_pushlightuserdata(L, this);
			lua_gettable(L, GConn);

			lua_pushnil(L);
			while (lua_next(L, Conn))
			{
				lua_copy(L, -2, -1);
				for (int i = 1; i <= ArgCount; i++) lua_pushvalue(L, RT + i);
				if (lua_pcall(L, ArgCount, 0, 0) != LUA_OK) LunaIO::Print("[" + std::string(Name) + "]: " + lua_tostring(L, -1), LunaIO::Error);
				lua_settop(L, K);
			}
			lua_settop(L, RT);
		}

		// Creates and returns a new event with the given parameters, pushes the lua userdata of this event onto the stack.
		static LunaEvent* New(const char* Name, void* Handler, DWORD Entries[], size_t EntryCount = 1, bool AutoHook = false)
		{
			int T = lua_gettop(L);
			auto self = (LunaEvent*)lua_newuserdata(L, sizeof(LunaEvent));// 1
			self->Setup(Name, Handler, Entries, EntryCount, AutoHook);
			LunaUtil::Local("EventMeta");// 2
			lua_pushlightuserdata(L, self);// 3
			lua_pushvalue(L, T + 1);
			lua_settable(L, T + 2);
			lua_setmetatable(L, T + 1);
			lua_settop(L, T);
			return self;
		}
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