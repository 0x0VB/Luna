#pragma once
namespace Disp::LunaApp
{
	using namespace Luna::Event;
	using namespace Luna::Class;
	using namespace Classes;
#pragma region OnStoneButtonDraw
	DWORD StoneButtonEntries[1] = { 0x447B00 };
	LunaEvent* StoneButtonDraw;
#pragma endregion
#pragma region OnUpdate
	DWORD __stdcall UpdateCaller();
	void UpdateHandler();
	DWORD UpdateEntries[1] = { 0x539140 };
	LunaEvent* OnUpdate;

	DWORD __stdcall UpdateCaller()
	{
		OnUpdate->Call(0);
		return 0x539148;
	}
	void __declspec(naked) UpdateHandler()
	{
		__asm
		{
			push ecx
			call UpdateCaller
			pop ecx
			sub esp, 0xC
			push esi
			lea esi, [esp+04]
			jmp eax
		}
	}
#pragma endregion
#pragma region OnFinalDraw
	DWORD __stdcall FinalDrawCaller(Sexy::Graphics* G);
	void FinalDrawHandler();
	DWORD FinalDrawEntries[1] = { 0x5390DC };
	LunaEvent* OnFinalDraw;
	Sexy::Image* MyImg = nullptr;

	DWORD __stdcall FinalDrawCaller(Sexy::Graphics* G)
	{
		if (MyImg == nullptr) MyImg = (Sexy::Image*)App->GetImage("images/coolpic.jpg", true);
		G->DrawImage(MyImg, 0, 0, 800, 600);
		return 0x5390E1;
	}
	void __declspec(naked) FinalDrawHandler()
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
#pragma endregion

	int MsgBox(lua_State* L)
	{
		AssertType(2, "string", "Message");
		App->MsgBox(GetString(2, "Luna!"), GetString(3, "Luna!"), 0);
		return 0;
	}
	void SetupEvents()
	{
		StoneButtonDraw = Luna::Event::LunaEvent::New("OnStoneButtonDraw", StoneButton::StoneButtonDrawHandler, StoneButtonEntries, 1, true);
		OnUpdate = LunaEvent::New("OnUpdate", UpdateHandler, UpdateEntries, 1, false);
		OnFinalDraw = LunaEvent::New("OnFinalDraw", FinalDrawHandler, FinalDrawEntries, 1, true);
	}
}

class Luna::Class::Classes::LunaApp : public Luna::Class::Base::LunaClass
{
public:
	static Base::LunaClass* Source;
	static int Init(lua_State* L)
	{
		using namespace Disp::LunaApp;
		using namespace Fields;
		Source = new LunaClass();
		Source->AllowsInjection = true;
		Source->SetName("LawnApp");
		Source->Inherit(LunaAppBase::Source);
#pragma region Fields
		BlnField::New("ZombiesLoaded", 0x800, Source);
		BlnField::New("NewUser", 0x801, Source);
		IntField::New("GamePlayed", 0x804, Source);
		BlnField::New("EasyPlantingCheat", 0x814, Source);
		BlnField::New("CloseRequest", 0x834, Source);
		IntField::New("Age", 0x838, Source);

		BlnField::New("MustacheMode", 0x8B8, Source);
		BlnField::New("SuperMowerMode", 0x8B9, Source);
		BlnField::New("FutureMode", 0x8BA, Source);
		BlnField::New("PinataMode", 0x8BB, Source);
		BlnField::New("DanceMode", 0x8BC, Source);
		BlnField::New("DaisyMode", 0x8BD, Source);
		BlnField::New("SukhbirMode", 0x8BE, Source);
#pragma endregion
#pragma region Events
		SetupEvents();
		Event::New("OnUpdate", OnUpdate, Source);
#pragma endregion
#pragma region Methods
		Source->Methods["MessageBox"] = MsgBox;
#pragma endregion

		Source->New(L, LawnApp::GetApp());
		lua_setglobal(L, "LawnApp");
		return 0;
	}
};

Luna::Class::Base::LunaClass* Luna::Class::Classes::LunaApp::Source = nullptr;
// OK maybe my naming conventions aren't the best in the long run
// Still gonna use it tho