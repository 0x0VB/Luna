#include "stdafx.h"
#include "LunaBase.h"

#include "LunaApi/LunaUtil/LunaUtil.h"
#include "Luna.h"

using namespace Luna::Class;
using namespace Fields;

namespace // Fields
{
	class ClassNameField : public LunaField
	{
	public:
		virtual void __index(lua_State* L) override
		{
			auto self = GetSelf(L);
			lua_pushstring(L, self->Class->Name);
		}
		DefNewField(ClassNameField)
	};
}

namespace // Methods
{
	int lua_IsA(lua_State* L)
	{
		auto self = GetAndAssert(L);
		auto SubClass = GetString(2);
		lua_pushboolean(L, self->Class->IsA(SubClass));
		return 1;
	}

	int GetAttribute(lua_State* L)
	{
		auto self = GetAndAssert(L);
		AssertType(2, "string", "AttributeName");
		self->Class->GetInjected(L);
		return 1;
	}

	int SetAttribute(lua_State* L)
	{
		auto self = GetAndAssert(L);
		AssertType(2, "string", "AttributeName");
		self->Class->PushInjected(L);
		lua_pushvalue(L, 2);
		lua_pushvalue(L, 3);
		lua_settable(L, -3);
		return 0;
	}

	int Destroy(lua_State* L)
	{
		auto self = GetAndAssert(L);
		LunaBase::Flush(L);
		delete self->Base;
		self->Base = NULL;
		return 0;
	}
}

LunaClass* LunaBase::Source = new LunaClass();
int LunaBase::Flush(lua_State* L)
{
	auto self = GetAndAssert(L);
	LunaUtil::Local("Injected");
	lua_pushvalue(L, 1);
	lua_newtable(L);
	lua_settable(L, -3);
	return 0;
}
int LunaBase::Init(lua_State* L)
{
	Source->AllowsInjection = false;
	Source->SetName("LunaBase");
	
	ClassNameField::New("ClassName", 0, Source);
	Source->Methods["IsA"] = lua_IsA;
	Source->Methods["Flush"] = Flush;
	Source->Methods["GetAttribute"] = GetAttribute;
	Source->Methods["SetAttribute"] = SetAttribute;
	Source->Methods["Destroy"] = Destroy;

	return 0;
}