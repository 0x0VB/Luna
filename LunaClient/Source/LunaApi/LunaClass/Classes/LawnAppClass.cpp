#include "stdafx.h"
#include "LawnAppClass.h"

#include "LunaBase.h"
#include "SexyAppClass.h"

#include "LunaApi/LunaEnum/LunaEnum.h"
#include "LunaApi/LunaUtil/LunaUtil.h"
#include "Luna.h"

#include "PvZ/Graphics.h"
#include "PvZ/Lawn.h"

namespace
{
	using namespace Luna::Event;
	std::vector<DWORD> StoneButtonEntries = { 0x447B00 };
	LunaEventRef StoneButtonDraw;

	std::vector<DWORD> UpdateEntries = { 0x539140 };
	LunaEventRef OnUpdate;

	std::vector<DWORD> FinalDrawEntries = { 0x5390DC };
	LunaEventRef OnFinalDraw;

	std::vector<DWORD> OnNewGameEntries = { 0x42D893, 0x43C939, 0x43C941, 0x44F5C5, 0x451550, 0x457F09, 0x457F10 };
	std::map<DWORD, const char*> NewGameCallReasons =
	{
		{0x42D898, "TreeOfWisdomToZenGarden"},
		{0x43C93E, "CheatKeysResetAdventure"},
		{0x43C946, "CheatKeysReset"},
		{0x44F5CA, "GameStarted"},
		{0x451555, "SavedGameDiscarded"},
		{0x457F0E, "TryAgainAdventure"},
		{0x457F15, "TryAgain"}
	};
	LunaEventRef OnNewGame;

	std::vector<DWORD> OnGameLoadEntries = { 0x44F58A };
	LunaEventRef OnGameLoad;
}

#include "LunaApi/LunaStructs/Vector2/Vector2.h"
#include "UIContainerClass.h"

void HandleGame()
{
	auto L = LUNA_STATE;
	auto Game = Luna::App->Lawn;
	auto GameID = Game->GameID;
	
	lua_pushinteger(L, GameID);
	lua_newtable(L);
	
	lua_pushstring(L, "Plants");
	lua_newtable(L);
	lua_settable(L, -3);

	lua_pushstring(L, "Zombies");
	lua_newtable(L);
	lua_settable(L, -3);

	lua_pushstring(L, "Projectiles");
	lua_newtable(L);
	lua_settable(L, -3);

	lua_pushstring(L, "GridItems");
	lua_newtable(L);
	lua_settable(L, -3);

	lua_pushstring(L, "Pickups");
	lua_newtable(L);
	lua_settable(L, -3);


	lua_pushstring(L, "LawnMowers");
	lua_newtable(L);
	lua_settable(L, -3);

	lua_settable(L, LUA_REGISTRYINDEX);
}

namespace // Event Bodies
{
	DWORD __stdcall UpdateCaller()
	{
		Luna::Tick();
		OnUpdate.GetEvent()->Call(LUNA_STATE, 0);
		return 0x539148;
	}
	DWORD __stdcall FinalDrawCaller(Sexy::Graphics* G)
	{

		return 0x5390E1;
	}
	void __stdcall NewGameCaller(DWORD CallReason)
	{
		HandleGame();
		CreateUIObject(LUNA_STATE, Luna::App->Lawn);
		lua_pushstring(LUNA_STATE, NewGameCallReasons[CallReason]);
		OnNewGame.GetEvent()->Call(LUNA_STATE, 2);
	}
	DWORD __stdcall GameLoadCaller(bool Success)
	{
		if (!Success) return 0x44F58F;

		HandleGame();
		CreateUIObject(LUNA_STATE, Luna::App->Lawn);
		OnGameLoad.GetEvent()->Call(LUNA_STATE, 1);
		return 0x44F58F;
	}
}

namespace
{
	inline void __declspec(naked) UpdateHandler()
	{
		__asm
		{
			push ecx
			call UpdateCaller
			pop ecx
			sub esp, 0xC
			push esi
			lea esi, [esp + 04]
			jmp eax
		}
	}
	inline void __declspec(naked) FinalDrawHandler()
	{
		__asm
		{
			push ecx
			push ecx
			call FinalDrawCaller
			pop ecx
			jmp eax
		}
	}
	inline void __declspec(naked) StoneButtonDrawHandler()
	{
		// Button in EDI
		__asm
		{
			push[esp + 0x1C]
			push[esp + 0x1C]
			push[esp + 0x1C]
			push[esp + 0x1C]
			push[esp + 0x1C]
			push[esp + 0x1C]
			push eax
			push[esp + 0x20]
			push edi
			call LawnStoneButton::Draw
			ret
		}
	};
	inline void __declspec(naked) NewGameHandler()
	{
		// No need for register recovery since these events hook at function call, so scratch registers can be used.
		__asm
		{
			mov ecx, 0x44F890
			call ecx
			push [esp]
			call NewGameCaller
			ret
		}
	}
	inline void __declspec(naked) GameLoadHandler()
	{
		__asm
		{
			mov ecx, 0x44F7A0
			call ecx
			push eax
			push eax
			call GameLoadCaller
			mov ecx, eax
			pop eax
			jmp ecx
		}
	}
}

namespace // Methods
{
	Luna::Enum::EnumList* Enums;
	int MsgBox(lua_State* L)
	{
		AssertType(L, 2, "string", "Message");
		Luna::App->MsgBox(GetString(L, 2, "Luna!"), GetString(L, 3, "Luna!"), 0);
		return 0;
	}
	int LawnMsgBox(lua_State* L)
	{
		AssertType(L, 2, "string", "Content");
		auto Content = GetString(L, 2);
		auto Title = GetString(L, 3, "Luna!");
		auto B1 = GetString(L, 4, "Yes");
		auto B2 = GetString(L, 5, "No");
		auto ButtonMode = GetInt(L, 6, 1);
		int R = Luna::App->LawnMessageBox(Title.c_str(), Content.c_str(), B1.c_str(), B2.c_str(), ButtonMode);
		lua_pushboolean(L, R == 0);
		return 1;
	}
	int AddParticle(lua_State* L)
	{
		auto self = AssertIsA(L, 1, "LawnApp");
		auto Effect = Enums->L_ParticleEffects->AssertEnum(L, 2, "Effect");
		auto X = GetInt(L, 3);
		auto Y = GetInt(L, 4);
		auto Layer = GetInt(L, 5, 400000);
		auto App = (LawnApp*)self->GetBase();
		App->AddParticles((ParticleEffect)Effect, X, Y, Layer);

		return 0;
	}

	void SetupEvents()
	{
		StoneButtonDraw = LunaEvent::New("OnStoneButtonDraw", StoneButtonDrawHandler, StoneButtonEntries, true);
		OnFinalDraw = LunaEvent::New("OnFinalDraw", FinalDrawHandler, FinalDrawEntries, true);
		OnUpdate = LunaEvent::New("OnUpdate", UpdateHandler, UpdateEntries, true);
		OnNewGame = LunaEvent::New("OnNewGame", NewGameHandler, OnNewGameEntries, true, true);
		OnGameLoad = LunaEvent::New("OnGameLoad", GameLoadHandler, OnGameLoadEntries, true);
	}
}

int Luna::Class::LunaApp::LunaInstanceRef = 0;
Luna::Class::LunaClass* Luna::Class::LunaApp::Source = new LunaClass();
int Luna::Class::LunaApp::Init(lua_State* L)
{
	Enums = Enum::GetEnums(L);
	Source->AllowsInjection = true;
	Source->SetName("LawnApp");
	Source->Inherit(Luna::Class::LunaAppBase::Source);

	using namespace Luna::Class::Fields;
	BlnField::New("ZombiesLoaded", 0x800, Source);
	BlnField::New("NewUser", 0x801, Source);
	IntField::New("GamePlayed", 0x804, Source);
	BlnField::New("EasyPlantingCheat", 0x814, Source);
	BlnField::New("FreePlantingCheat", 0x814, Source);
	BlnField::New("CloseRequest", 0x834, Source);
	IntField::New("Age", 0x838, Source);

	UIObjectField::New("Lawn", 0x768, Source);
	UIObjectField::New("TitleScreen", 0x76C, Source);
	UIObjectField::New("GameSelector", 0x770, Source);
	UIObjectField::New("SeedChooser", 0x774, Source);
	UIObjectField::New("AwardScreen", 0x778, Source);
	UIObjectField::New("CreditsScreen", 0x77C, Source);
	UIObjectField::New("ChallengeScreen", 0x780, Source);

	BlnField::New("MustacheMode", 0x8B8, Source);
	BlnField::New("SuperMowerMode", 0x8B9, Source);
	BlnField::New("FutureMode", 0x8BA, Source);
	BlnField::New("PinataMode", 0x8BB, Source);
	BlnField::New("DanceMode", 0x8BC, Source);
	BlnField::New("DaisyMode", 0x8BD, Source);
	BlnField::New("SukhbirMode", 0x8BE, Source);

	SetupEvents();
	EventField::New("OnUpdate", OnUpdate.GetEvent(), Source);
	EventField::New("OnNewGame", OnNewGame.GetEvent(), Source);
	EventField::New("OnGameLoad", OnGameLoad.GetEvent(), Source);

	Source->Methods["MessageBox"] = MsgBox;
	Source->Methods["LawnMsgBox"] = LawnMsgBox;
	Source->Methods["AddParticles"] = AddParticle;

	Source->New(L, LawnApp::GetApp());
	LunaInstanceRef = lua_ref(L, -1);

	return 0;
}