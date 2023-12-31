#pragma once
#include "framework.h"
#include "PvZ/Definitions.h"
#include "Include/lua.h"

#include "LunaApi/LunaEvent/LunaEvent.h"

namespace Luna::Class
{
	class LunaClass;
	class LunaField;
	class LunaInstance;

	extern std::map<void*, bool> CLASS_VALIDATE;
	extern CONST SIZE_T MAX_FIELD_CAPACITY;
	extern SIZE_T FIELDS_USED;
	extern LunaField* FIELDS;

	
	class LunaInstance
	{
	public:
		LunaClass* Class;
		void* Base;
	};
	class LunaClass
	{
	public:
		char Name[35];
		bool AllowsInjection;
		std::map<std::string, LunaField*> Fields;
		std::map<std::string, lua_CFunction> Methods;
		std::map<std::string, LunaClass*> SubClasses;

		void SetName(const char* NewName);
		void AddSubClass(LunaClass* SubClass);
		void AddSubClass(const char* ClassName);
		virtual void __tostring(lua_State* L);
		virtual int __call(lua_State* L);
		virtual bool IsA(std::string SubClass);
		virtual void Inherit(LunaClass* Other);
		virtual void* GetBase(LunaInstance* Instance) { return Instance->Base; };
		virtual LunaInstance* New(lua_State* L, void* Param);
		virtual void PushInjected(lua_State* L);
		virtual void GetInjected(lua_State* L);
		virtual void Inject(lua_State* L);
	};

	class LunaField
	{
	public:
		char Name[32];
		DWORD Offset;
		virtual void __index(lua_State* L) {}
		virtual void __newindex(lua_State* L);
		virtual void* GetBase(LunaInstance* self) { return (void*)((DWORD)self->Base + Offset); };
		void SetName(const char* NewName);
		void AddToClass(LunaClass* Class);

		template <typename T>
		static T* New(const char* Name, DWORD Offset, LunaClass* Class)
		{
			auto self = (LunaField*)(new (&FIELDS[FIELDS_USED]) T);
			self->Offset = Offset;
			self->SetName(Name);
			Class->Fields[Name] = self;
			FIELDS_USED++;
			return (T*)self;
		}

	};

	class LunaAppBase;
	class LunaApp;

	int __call(lua_State* L);
	int __type(lua_State* L);
	int __index(lua_State* L);
	int __newindex(lua_State* L);
	int __tostring(lua_State* L);

	LunaInstance* GetAndAssert(lua_State* L);
	LunaInstance* GetSelf(lua_State* L);

	int Init(lua_State* L);
};

namespace Luna::Class::Fields
{
#define DefNewField(T) static T* New(const char* Name, DWORD Offset, LunaClass* Class) \
	{ return LunaField::New<T>(Name, Offset, Class); }
#define FBase(T) auto self = GetSelf(L); auto Base = (T*)GetBase(self);
	class WindTitle : public LunaField
	{
	public:
		virtual void __index(lua_State* L) override;
		virtual void __newindex(lua_State* L) override;
		DefNewField(WindTitle)
	};
	class WindBounds : public LunaField
	{
	public:
		virtual void __index(lua_State* L);
		virtual void __newindex(lua_State* L);
		DefNewField(WindBounds)
	};

	class BytField : public LunaField
	{
		virtual void __index(lua_State* L) override;
		virtual void __newindex(lua_State* L) override;
		DefNewField(BytField)
	};
	class BlnField : LunaField
	{
	public:
		virtual void __index(lua_State* L) override;
		virtual void __newindex(lua_State* L) override;
		DefNewField(BlnField)
	};
	class IntField : public LunaField
	{
	public:
		virtual void __index(lua_State* L) override;
		virtual void __newindex(lua_State* L) override;
		DefNewField(IntField)
	};
	class DblField : public LunaField
	{
	public:
		virtual void __index(lua_State* L) override;
		virtual void __newindex(lua_State* L) override;
		DefNewField(DblField)
	};
	class FltField : public LunaField
	{
		virtual void __index(lua_State* L) override;
		virtual void __newindex(lua_State* L) override;
		DefNewField(FltField)
	};
	class StrField : public LunaField
	{
	public:
		virtual void __index(lua_State* L) override;
		virtual void __newindex(lua_State* L) override;
		DefNewField(StrField)
	};

	class RctField : public LunaField
	{
	public:
		virtual void __index(lua_State* L) override;
		virtual void __newindex(lua_State* L) override;
		DefNewField(RctField)
	};
	class IV2Field : public LunaField
	{
	public:
		virtual void __index(lua_State* L) override;
		virtual void __newindex(lua_State* L) override;
		DefNewField(IV2Field)
	};
	class FV2Field : public LunaField
	{
	public:
		virtual void __index(lua_State* L) override;
		virtual void __newindex(lua_State* L) override;
		DefNewField(FV2Field)
	};
	class FV3Field : public  LunaField
	{
	public:
		virtual void __index(lua_State* L) override;
		virtual void __newindex(lua_State* L) override;
		DefNewField(FV3Field)
	};
	class ColField : public LunaField
	{
	public:
		virtual void __index(lua_State* L) override;
		virtual void __newindex(lua_State* L) override;
		DefNewField(ColField)
	};
	class PadField : public LunaField
	{
		virtual void __index(lua_State* L) override;
		virtual void __newindex(lua_State* L) override;
		DefNewField(PadField)
	};

	class EventField : public LunaField
	{
	public:
		virtual void __index(lua_State* L) override;
		static EventField* New(const char* Name, Luna::Event::LunaEvent* New, LunaClass* Class)
		{
			return LunaField::New<EventField>(Name, (DWORD)New, Class);
		}
	};
}