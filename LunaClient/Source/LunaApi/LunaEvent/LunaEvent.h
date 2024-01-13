#pragma once
#include <vector>
#include <Luna.h>

#define LUNA_MAX_CONNECTIONS 20

namespace Luna::Event
{
	class LunaEvent;
	struct LunaEventRef
	{
		int EventRef = 0;
		LunaEventRef() { EventRef = 0; }
		LunaEventRef(int);
		void Push(lua_State*);
		LunaEvent* GetEvent();
	};

	struct LunaConnection
	{
		int RefIdx;
		int EventRef;
		lua_State* L;

		static int __index(lua_State* L);
		static int __newindex(lua_State* L);
		static int __tostring(lua_State* L);

		static int Disconnect(lua_State* L);

		bool operator==(LunaConnection Other) { return RefIdx == Other.RefIdx && EventRef == Other.EventRef; }
	};

	class LunaEvent
	{
	private:
		void SetupHook();
		void Hook(DWORD Entry);
	public:
		union
		{
			void* Handler;
			lua_CFunction LHandler;
		};
		char Name[32];
		bool CallHook;

		std::vector<DWORD> Entries;
		std::vector<LunaConnection> Connections;

		bool IsLuaEvent;
		bool Hooked;

		int EventRef;

		void Call(lua_State* CL, size_t ArgCount=0);

		static LunaEventRef New(const char* Name, lua_CFunction Handler);
		static LunaEventRef New(const char* Name, void* Handler, std::vector<DWORD> Entries, bool AutoHook = false, bool CallHook = false);

		static int __index(lua_State* L);
		static int __newindex(lua_State* L);
		static int __tostring(lua_State* L);
		static int __call(lua_State* L);

		static int Fire(lua_State* L);
		static int Connect(lua_State* L);
		static int DisconnectAll(lua_State* L);
	};

	int Init(lua_State* L);
}