#pragma once
#pragma region Basic Fields
namespace Luna::Class::Fields
{
#define DefNewField(T) static T* New(const char* Name, DWORD Offset, Base::LunaClass* Class) \
	{ return Base::LunaField::New<T>(Name, Offset, Class); }
#define FBase(T) auto self = GetSelf(L); auto Base = (T*)GetBase(self);
	class WindTitle : public Base::LunaField
	{
	public:
		virtual void __index(lua_State* L) override
		{
			lua_pushstring(L, App->Title);
		}
		virtual void __newindex(lua_State* L) override
		{
			auto Value = GetString(3);
			AssertType(3, "string", Name);
			App->Title = Value;
			if (App->MainWindowHandle) SetWindowTextA(App->MainWindowHandle, Value.c_str());
		}
		DefNewField(WindTitle)
	};
	class WindBounds : public Base::LunaField
	{
	public:
		virtual void __index(lua_State* L)
		{
			App->WindowBounds.Push();
		}
		virtual void __newindex(lua_State* L)
		{
			AssertType(3, "Rect", Name);
			auto Value = GetRect(3);
			App->WindowBounds = Value;
			if (App->MainWindowHandle) GetWindowRect(App->MainWindowHandle, Value.ToLPRECT());
		}
		DefNewField(WindBounds)
	};

	class BytField : public Base::LunaField
	{
		virtual void __index(lua_State* L) override
		{
			FBase(BYTE);
			lua_pushnumber(L, *Base);
		}
		virtual void __newindex(lua_State* L) override
		{
			FBase(BYTE);
			auto Value = GetInt(3, -1);
			if (Value > 255 || Value < 0) LunaIO::ThrowError(std::string(Name) + " can only be a number between 0-255, got " + LunaUtil::Type(3));
			*Base = Value;
		}
		DefNewField(BytField)
	};
	class BlnField : Base::LunaField
	{
	public:
		virtual void __index(lua_State* L) override
		{
			FBase(bool);
			lua_pushboolean(L, *Base);
		}
		virtual void __newindex(lua_State* L) override
		{
			FBase(bool);
			AssertType(3, "boolean", Name);
			*Base = (bool)lua_toboolean(L, 3);
		}
		DefNewField(BlnField)
	};
	class IntField : public Base::LunaField
	{
	public:
		virtual void __index(lua_State* L) override
		{
			FBase(int);
			lua_pushinteger(L, *Base);
		}
		virtual void __newindex(lua_State* L) override
		{
			FBase(int);
			if (!lua_isnumber(L, 3)) LunaIO::ThrowError(std::string("Expected an integer for ") + Name + ", got " + LunaUtil::Type(3));
			*Base = (int)lua_tonumber(L, 3);
		}
		DefNewField(IntField)
	};
	class DblField : public Base::LunaField
	{
	public:
		virtual void __index(lua_State* L) override
		{
			FBase(double);
			lua_pushnumber(L, *Base);
		}
		virtual void __newindex(lua_State* L) override
		{
			FBase(double);
			if (!lua_isnumber(L, 3)) LunaIO::ThrowError(std::string("Expected a number for ") + Name + ", got " + LunaUtil::Type(3));
			*Base = (double)lua_tonumber(L, 3);
		}
		DefNewField(DblField)
	};
	class FltField : public Base::LunaField
	{
		virtual void __index(lua_State* L) override
		{
			FBase(float);
			lua_pushnumber(L, *Base);
		}
		virtual void __newindex(lua_State* L) override
		{
			FBase(float);
			if (!lua_isnumber(L, 3)) LunaIO::ThrowError(std::string("Expected a number for ") + Name + ", got " + LunaUtil::Type(3));
			*Base = (float)lua_tonumber(L, 3);
		}
		DefNewField(FltField)
	};
	class StrField : public Base::LunaField
	{
	public:
		virtual void __index(lua_State* L) override
		{
			FBase(std::string);
			lua_pushstring(L, Base->c_str());
		}
		virtual void __newindex(lua_State* L) override
		{
			FBase(std::string);
			AssertType(3, "string", std::string(Name));
			Base->assign(lua_tostring(L, 3));
		}
		DefNewField(StrField)
	};
	
	class RctField : public Base::LunaField
	{
	public:
		virtual void __index(lua_State* L) override
		{
			FBase(IRect);
			Base->Push();
		}
		virtual void __newindex(lua_State* L) override
		{
			FBase(IRect);
			AssertType(3, "Rect", Name);
			*Base = GetRect(3);
		}
		DefNewField(RctField)
	};
	class IV2Field : public Base::LunaField
	{
	public:
		virtual void __index(lua_State* L) override
		{
			FBase(IVector2);
			Base->Push();
		}
		virtual void __newindex(lua_State* L) override
		{
			FBase(IVector2);
			AssertType(3, "Vector2", Name);
			*Base = (IVector2)GetVector2(3);
		}
		DefNewField(IV2Field)
	};
	class FV2Field : public Base::LunaField
	{
	public:
		virtual void __index(lua_State* L) override
		{
			FBase(FVector2);
			Base->Push();
		}
		virtual void __newindex(lua_State* L) override
		{
			FBase(FVector2);
			AssertType(3, "Vector2", Name);
			*Base = (FVector2)GetVector2(3);
		}
		DefNewField(FV2Field)
	};
	class FV3Field : public  Base::LunaField
	{
	public:
		virtual void __index(lua_State* L) override
		{
			FBase(FVector3);
			Base->Push();
		}
		virtual void __newindex(lua_State* L) override

		{
			FBase(FVector3);
			AssertType(3, "Vector3", Name);
			*Base = GetVector3(3);
		}
		DefNewField(FV3Field)
	};
	class ColField : public Base::LunaField
	{
	public:
		virtual void __index(lua_State* L) override
		{
			FBase(Color);
			Base->Push();
		}
		virtual void __newindex(lua_State* L) override
		{
			FBase(Color);
			AssertType(3, "Color", Name);
			*Base = GetColor(3);
		}
		DefNewField(ColField)
	};
	class PadField : public Base::LunaField
	{
		virtual void __index(lua_State* L) override
		{
			FBase(Pad);
			Base->Push();
		}
		virtual void __newindex(lua_State* L) override
		{
			FBase(Pad);
			AssertType(3, "Pad", Name);
			*Base = GetPad(3);
		}
		DefNewField(PadField)
	};

	class Event : public Base::LunaField
	{
	public:
		virtual void __index(lua_State* L) override
		{
			auto Event = (Luna::Event::LunaEvent*)Offset;
			Event->Push();
		}
		static Event* New(const char* Name, Luna::Event::LunaEvent* New, Base::LunaClass* Class)
		{
			return Base::LunaField::New<Event>(Name, (DWORD)New, Class);
		}
	};
}
#pragma endregion

#pragma region MetaMethods
int Luna::Class::__type(lua_State* L)
{
	auto self = GetAndAssert(L);
	lua_pushstring(L, self->Class->Name);
	return 1;
}

int Luna::Class::__call(lua_State* L)
{
	auto self = GetAndAssert(L);
	return self->Class->__call(L);
}

int Luna::Class::__index(lua_State* L)
{
	auto self = GetAndAssert(L);
	auto Field = GetString(2);
	auto Class = self->Class;

	if (!lua_isstring(L, 2)) LunaIO::ThrowError("Expected a string field, got " + LunaUtil::Type(2));// Only string fields allowed
	else if (Class->Methods.contains(Field)) lua_pushcclosure(L, Class->Methods[Field], 0);// Get Method
	else if (Class->Fields.contains(Field)) Class->Fields[Field]->__index(L);// Get Field
	else if (!Class->AllowsInjection) LunaIO::ThrowError(Field + " is not a valid member of " + Class->Name);// Check if Field Injection is allowed
	else Class->GetInjected(L);// Get Injected Field
	return 1;
}

int Luna::Class::__newindex(lua_State* L)
{
	auto self = GetAndAssert(L);
	auto Field = GetString(2);
	auto Class = self->Class;

	if (!lua_isstring(L, 2)) LunaIO::ThrowError("Expected a string field, got " + LunaUtil::Type(2));// Only string fields allowed
	else if (Class->Methods.contains(Field)) LunaIO::ThrowError(Field + " is read-only.");// Error: Methods are read-only.
	else if (Class->Fields.contains(Field)) Class->Fields[Field]->__newindex(L);// Set Field
	else if (!Class->AllowsInjection) LunaIO::ThrowError(Field + " is not a valid member of " + Class->Name);// Check Injection
	else Class->Inject(L);// Inject a new field
	return 0;
}

int Luna::Class::__tostring(lua_State* L)
{
	auto self = GetAndAssert(L);
	self->Class->__tostring(L);
	return 1;
}
#pragma endregion


#include "Classes/SexyApp.h"
#include "Classes/LawnApp.h"
int Luna::Class::Init(lua_State* L)
{
	FIELDS = new Base::LunaField[MAX_FIELD_CAPACITY];
	
	lua_newtable(L);
	LunaUtil::Local("ClassRef", -1);

	lua_newtable(L);
	LunaUtil::Local("Injected", -1);

	lua_newtable(L);

	lua_pushstring(L, "__type");
	lua_pushcclosure(L, __type, 0);
	lua_settable(L, -3);

	lua_pushstring(L, "__call");
	lua_pushcclosure(L, __call, 0);
	lua_settable(L, -3);

	lua_pushstring(L, "__index");
	lua_pushcclosure(L, __index, 0);
	lua_settable(L, -3);

	lua_pushstring(L, "__newindex");
	lua_pushcclosure(L, __newindex, 0);
	lua_settable(L, -3);

	lua_pushstring(L, "__tostring");
	lua_pushcclosure(L, __tostring, 0);
	lua_settable(L, -3);

	LunaUtil::Local("ClassMeta", -1);
	LunaInit(Classes::LunaAppBase);
	LunaInit(Classes::LunaApp);

	return 0;
}