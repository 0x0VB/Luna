#pragma once
namespace Luna::Class
{
	namespace Base
	{
		class LunaClass;
		class LunaField;
		class LunaInstance;
	}

	std::map<void*, bool> CLASS_VALIDATE = {};
	CONST SIZE_T MAX_FIELD_CAPACITY = 1000;
	SIZE_T FIELDS_USED = 0;
	Base::LunaField* FIELDS;

	namespace Base
	{
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

			void SetName(const char* NewName)
			{
				int Length = strlen(NewName);
				memcpy(Name, NewName, Length);
				Name[Length] = 0;
				AddSubClass(NewName);
			}
			void AddSubClass(LunaClass* SubClass) { SubClasses[std::string(SubClass->Name)] = SubClass; }
			void AddSubClass(const char* ClassName) { SubClasses[std::string(ClassName)] = NULL; }
			virtual void __tostring(lua_State* L) { lua_pushstring(L, Name); }
			virtual int __call(lua_State* L) { LunaIO::ThrowError(std::string("Unable to call a ") + Name + "."); return 0; }
			virtual bool IsA(std::string SubClass) { return SubClasses.contains(SubClass); }
			virtual void Inherit(LunaClass* Other)
			{
				for (const auto& [K, V] : Other->SubClasses) { SubClasses[K] = V; }
				for (const auto& [K, V] : Other->Fields)
				{
					if (Fields.contains(K)) continue;
					Fields[K] = V;
				}

				for (const auto& [K, V] : Other->Methods)
				{
					if (Methods.contains(K)) continue;
					Methods[K] = V;
				}

			}
			virtual void* GetBase(LunaInstance* Instance) { return Instance->Base; };
			virtual LunaInstance* New(lua_State* L, void* Param)
			{
				int T = lua_gettop(L);
				auto self = (LunaInstance*)lua_newuserdata(L, sizeof(LunaInstance));
				self->Base = Param;
				self->Class = this;

				LunaUtil::Local("ClassRef");

				lua_pushlightuserdata(L, self);
				lua_pushvalue(L, T + 1);
				lua_settable(L, T + 2);

				lua_pushlightuserdata(L, Param);
				lua_pushvalue(L, T + 1);
				lua_settable(L, T + 2);
				lua_settop(L, T + 1);

				LunaUtil::Local("ClassMeta");
				lua_setmetatable(L, T + 1);
				CLASS_VALIDATE[self] = true;

				if (!AllowsInjection) return self;
				LunaUtil::Local("Injected");
				lua_pushvalue(L, T + 1);
				lua_newtable(L);
				lua_settable(L, -3);
				lua_settop(L, T + 1);

				return self;
			}
			virtual void PushInjected(lua_State* L)
			{
				LunaUtil::Local("Injected");
				lua_pushvalue(L, 1);
				lua_gettable(L, -2);
			}
			virtual void GetInjected(lua_State* L)
			{
				PushInjected(L);
				lua_pushvalue(L, 2);
				lua_gettable(L, -2);
			}
			virtual void Inject(lua_State* L)
			{
				PushInjected(L);
				lua_pushvalue(L, 2);
				lua_pushvalue(L, 3);
				lua_settable(L, -3);
			}
		};
		class LunaField
		{
		public:
			char Name[32];
			DWORD Offset;
			virtual void __index(lua_State* L) {}
			virtual void __newindex(lua_State* L) { LunaIO::ThrowError(std::string(Name) + " is read-only."); }
			virtual void* GetBase(LunaInstance* self) { return (void*)((DWORD)self->Base + Offset); }
			void SetName(const char* NewName)
			{
				int Length = strlen(NewName);
				memcpy(Name, NewName, Length);
				Name[Length] = 0;
			}
			void AddToClass(LunaClass* Class) { Class->Fields[Name] = this; }

			template <typename T>
			static T* New(const char* Name, DWORD Offset, Base::LunaClass* Class)
			{
				auto self = (LunaField*)(new (&FIELDS[FIELDS_USED]) T);
				self->Offset = Offset;
				self->SetName(Name);
				Class->Fields[Name] = self;
				FIELDS_USED++;
				return (T*)self;
			}
		};
	}

	namespace Classes
	{
		class LunaAppBase;
		class LunaApp;

	}

	int __call(lua_State* L);
	int __type(lua_State* L);
	int __index(lua_State* L);
	int __newindex(lua_State* L);
	int __tostring(lua_State* L);

	Base::LunaInstance* GetAndAssert(lua_State* L)
	{
		void* self = lua_touserdata(L, 1);
		if (!lua_isuserdata(L, 1)) LunaIO::ThrowError("Unable to get self.");
		if (CLASS_VALIDATE.contains(self)) return (Base::LunaInstance*)self;
		LunaIO::ThrowError("Self is not a valid LunaInstance.");
	}

	Base::LunaInstance* GetSelf(lua_State* L) { return (Base::LunaInstance*)lua_touserdata(L, 1); }
	int Init(lua_State* L);
};