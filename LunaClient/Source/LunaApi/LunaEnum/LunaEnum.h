#pragma once
#include <string>
#include <map>

#include "Luna.h"

namespace Luna::Enum
{
	class EnumLib;
	class EnumItem;
	
	class EnumLib
	{
	public:
		int Reference;
		std::string Name;
		std::map<int, EnumItem*> Values;
		std::map<std::string, EnumItem*> Items;
		EnumLib(std::string LibName)
		{
			Name = LibName;
			Values = {};
			Items = {};
		}
		
		bool Contains(std::string Name);
		bool Contains(EnumItem* Item);
		bool Contains(int Value);

		void Add(EnumItem* Enum);
		void Add(lua_State* L, std::string ItemName, int Value);
		int AssertEnum(lua_State* L, int Index, std::string ParamName = "this field");

		static EnumLib* New(lua_State* L, std::string LibName);
		
		static int __type(lua_State* L);
		static int __index(lua_State* L);
		static int __newindex(lua_State* L);
		static int __tostring(lua_State* L);
	};

	class EnumItem
	{
	public:
		int Reference;
		EnumLib* Library;
		std::string Name;
		int Value;

		EnumItem(std::string ItemName, EnumLib* Lib, int ItemValue)
		{
			Name = ItemName;
			Value = ItemValue;
			Lib->Add(this);
		}

		static EnumItem* New(lua_State* L, EnumLib* Lib, std::string ItemName, int Value);

		static int __type(lua_State* L);
		static int __index(lua_State* L);
		static int __newindex(lua_State* L);
		static int __tostring(lua_State* L);
	};

	void SetEnum(lua_State* L, EnumLib* Lib);
	int Init(lua_State* L);
}