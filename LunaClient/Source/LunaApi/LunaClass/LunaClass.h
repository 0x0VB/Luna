#pragma once
#include "framework.h"

#include "Luau/lua.h"
#include "PvZ/Definitions.h"

#include "LunaApi/LunaApi.h"
#include "LunaApi/LunaEvent/LunaEvent.h"
#include "LunaApi/LunaEnum/LunaEnum.h"
#include "LunaApi/LunaIO/LunaIO.h"

namespace Luna::Class
{
	class LunaInstance;
	class LunaClass;
	class LunaField;

	extern std::map<void*, bool> CLASS_VALIDATE;
	extern CONST SIZE_T MAX_FIELD_CAPACITY;
	extern SIZE_T FIELDS_USED;
	extern LunaField* FIELDS;

	
	class LunaInstance
	{
	public:
		LunaClass* Class;
		void* Base;
		unsigned int Data[2] = {};
		int Associations[30] = {};
		void* GetBase();
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
		virtual void* GetBase(LunaInstance* Instance) { return (Instance == NULL) ? NULL : Instance->Base; };
		virtual void New(lua_State* L, void* Param);
		virtual void PushInjected(lua_State* L);
		virtual void GetInjected(lua_State* L);
		virtual void Inject(lua_State* L);
	};

	class LunaField
	{
	public:
		char Name[32] = {};
		bool ReadOnly = false;
		DWORD Offset = 0;
		void* Data = NULL;

		virtual void __index(lua_State* L) {}
		virtual void __newindex(lua_State* L);
		virtual void* GetBase(LunaInstance* self) { return (void*)((DWORD)self->Class->GetBase(self) + Offset); };
		void SetName(const char* NewName);
		void AddToClass(LunaClass* Class);
		void CheckReadOnly(lua_State* L)
		{
			if (ReadOnly) LunaIO::ThrowError(L, std::string(Name) + " is read-only.");
		}

		template <typename T>
		static T* New(const char* Name, DWORD Offset, LunaClass* Class, bool ReadOnly = false)
		{
			auto self = (LunaField*)(new (&FIELDS[FIELDS_USED]) T);
			self->Offset = Offset;
			self->SetName(Name);
			self->ReadOnly = ReadOnly;
			Class->Fields[Name] = self;
			FIELDS_USED++;
			return (T*)self;
		}

	};

	class LunaBase;
	class LunaAppBase;
	class LunaApp;
	class LunaUIContainer;
	class LunaUIElement;
	class LunaUIRoot;
	class LunaStoneButton;
	class LunaUIButton;
	class LunaImage;
	class LunaMemImage;
	class LunaDDImage;
	class LunaFont;
	class LunaIFont;
	class LunaSysFont;
	class LunaLawn;
	class LunaCrazyDave;
	
	class LunaDABase;
	class LunaPlant;
	class LunaZombie;
	class LunaProjectile;
	class LunaGridItem;
	class LunaPickup;
	class LunaMower;

	int __gc(lua_State* L);
	int __call(lua_State* L);
	int __type(lua_State* L);
	int __index(lua_State* L);
	int __newindex(lua_State* L);
	int __tostring(lua_State* L);

	// Makes sure the value at the given Index is a LunaInstance userdata.
	LunaInstance* GetAndAssert(lua_State* L, int Index = 1, std::string ParamName = "self", std::string Expected = "LunaInstance");
	// Returns the userdata at index 1 cast as a LunaInstance.
	LunaInstance* GetSelf(lua_State* L);
	// Returns the userdata at the given index and throws an error if it doesn't belong to the given subclass.
	LunaInstance* AssertIsA(lua_State* L, int Index, std::string SubClass, std::string ParamName = "self", bool AcceptsNil = false);

	int Init(lua_State* L);
};

namespace Luna::Class::Fields
{
#define DefNewField(T) static T* New(const char* Name, DWORD Offset, LunaClass* Class, bool ReadOnly = false) \
	{ return LunaField::New<T>(Name, Offset, Class, ReadOnly); }
#define FBase(T) auto self = GetSelf(L); auto Base = (T*)GetBase(self);
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
	public:
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
	public:
		virtual void __index(lua_State* L) override;
		virtual void __newindex(lua_State* L) override;
		DefNewField(PadField)
	};

	class EventField : public LunaField
	{
	public:
		virtual void __index(lua_State* L) override;
		static EventField* New(const char* Name, Luna::Event::LunaEvent* New, LunaClass* Class);
	};

	class FunctionField : public LunaField
	{
	public:
		virtual void __index(lua_State* L) override;
		virtual void __newindex(lua_State* L) override;
		DefNewField(FunctionField)
	};

	class EnumField : public LunaField
	{
	public:
		virtual void __index(lua_State* L) override;
		virtual void __newindex(lua_State* L) override;
		static EnumField* New(const char* Name, DWORD Offset, Enum::EnumLib* Library, LunaClass* Class);
	};
}