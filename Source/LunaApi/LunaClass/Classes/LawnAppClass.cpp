#include "stdafx.h"
#include "LawnAppClass.h"

#include "SexyAppClass.h"

#include "LunaApi/LunaUtil/LunaUtil.h"
#include "Luna.h"

#include "PvZ/Graphics.h"
#include "PvZ/DialogButton.h"

namespace Disp::LunaApp {
	DWORD StoneButtonEntries[1] = { 0x447B00 };
	LunaEvent* StoneButtonDraw;

	DWORD UpdateEntries[1] = { 0x539140 };
	LunaEvent* OnUpdate;

	DWORD FinalDrawEntries[1] = { 0x5390DC };
	LunaEvent* OnFinalDraw;
	Sexy::Image* MyImg = nullptr;
}

DWORD __stdcall Disp::LunaApp::UpdateCaller()
{
	OnUpdate->Call(0);
	return 0x539148;
}

DWORD __stdcall Disp::LunaApp::FinalDrawCaller(Sexy::Graphics* G)
{
	if (MyImg == nullptr) MyImg = (Sexy::Image*)Luna::App->GetImage("images/coolpic.jpg", true);
	G->DrawImage(MyImg, 0, 0, 800, 600);
	return 0x5390E1;
}

int Disp::LunaApp::MsgBox(lua_State* L)
{
	AssertType(2, "string", "Message");
	Luna::App->MsgBox(GetString(2, "Luna!"), GetString(3, "Luna!"), 0);
	return 0;
}
void Disp::LunaApp::SetupEvents()
{
	StoneButtonDraw = Luna::Event::LunaEvent::New("OnStoneButtonDraw", StoneButton::StoneButtonDrawHandler, StoneButtonEntries, 1, true);
	OnUpdate = LunaEvent::New("OnUpdate", UpdateHandler, UpdateEntries, 1, false);
	OnFinalDraw = LunaEvent::New("OnFinalDraw", FinalDrawHandler, FinalDrawEntries, 1, true);
}

using namespace Luna::Class::Fields;
Luna::Class::Base::LunaClass* Luna::Class::Classes::LunaApp::Source = nullptr;
int Luna::Class::Classes::LunaApp::Init(lua_State* L)
{
	Source = new LunaClass();
	Source->AllowsInjection = true;
	Source->SetName("LawnApp");
	Source->Inherit(Luna::Class::Classes::LunaAppBase::Source);

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

	Disp::LunaApp::SetupEvents();
	EventField::New("OnUpdate", Disp::LunaApp::OnUpdate, Source);

	Source->Methods["MessageBox"] = Disp::LunaApp::MsgBox;

	Source->New(L, LawnApp::GetApp());
	lua_setglobal(L, "LawnApp");
	return 0;
}