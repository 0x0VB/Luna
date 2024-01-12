#pragma once
#include <string>
#include <map>

#include "Luna.h"

namespace Luna::Enum
{
	class EnumLib;
	class EnumItem;
	
	struct EnumLRef
	{
		int Ref;
		
		EnumLRef(int R) { Ref = R; }
		EnumLRef() { Ref = 0; }

		EnumLib* GetRef(lua_State* L = NULL)
		{
			if (L == NULL)
			{
				L = LUNA_STATE;
				lua_getref(L, Ref);
				auto self = (EnumLib*)lua_touserdata(L, -1);
				lua_pop(L, 1);
				return self;
			}
			else
			{
				lua_getref(L, Ref);
				auto self = (EnumLib*)lua_touserdata(L, -1);
				return self;
			}
		}
		operator int() { return Ref; }
	};

	struct EnumRef
	{
		int Ref;

		EnumRef(int R) { Ref = R; }
		EnumRef() { Ref = 0; }

		EnumItem* GetRef(lua_State* L = NULL)
		{
			if (L == NULL)
			{
				L = LUNA_STATE;
				lua_getref(L, Ref);
				auto self = (EnumItem*)lua_touserdata(L, -1);
				lua_pop(L, 1);
				return self;
			}
			else
			{
				lua_getref(L, Ref);
				auto self = (EnumItem*)lua_touserdata(L, -1);
				return self;
			}
		}
		operator int() { return Ref; }
	};

	class EnumLib
	{
	public:
		EnumLRef Reference;
		std::string Name;
		std::set<int> Values;
		std::map<std::string, EnumRef> Items;
		
		bool Contains(std::string Name);
		bool Contains(EnumItem* Enum);
		bool Contains(int Value);

		void Add(EnumItem* Enum);
		EnumItem* Add(lua_State* L, std::string ItemName, int Value);

		static EnumLib* New(lua_State* L, std::string LibName);
		
		static int __type(lua_State* L);
		static int __index(lua_State* L);
		static int __newindex(lua_State* L);
		static int __tostring(lua_State* L);
	};

	class EnumItem
	{
	public:
		EnumRef Reference;
		EnumLRef LibReference;

		std::string Name;
		int Value;

		static EnumItem* New(lua_State* L, EnumLib* Lib, std::string ItemName, int Value);

		static int __type(lua_State* L);
		static int __index(lua_State* L);
		static int __newindex(lua_State* L);
		static int __tostring(lua_State* L);
	};

	int Init(lua_State* L);
}