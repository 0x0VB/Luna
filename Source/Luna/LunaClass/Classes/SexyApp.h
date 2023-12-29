#pragma once

namespace Disp::LunaAppBase
{

}

class Luna::Class::Classes::LunaAppBase : public Luna::Class::Base::LunaClass
{
public:
	static Base::LunaClass* Source;
	static int Init(lua_State* L)
	{
		using namespace Disp::LunaAppBase;
		using namespace Fields;
		Source = new LunaClass();
		Source->AllowsInjection = true;
		Source->SetName("SexyApp");
		Source->AddSubClass("SexyAppBase");

#pragma region Fields
		WindTitle::New("WindowTitle", 0, Source);
		WindBounds::New("WindowBounds", 0, Source);

		IntField::New("Seed", 0x8, Source);
		StrField::New("RegisteryKey", 0x80, Source);
		DblField::New("MusicVolume", 0xD0, Source);
		DblField::New("SFXVolume", 0xD8, Source);
		BlnField::New("IsBeta", 0x11C, Source);
		BlnField::New("IsWindowed", 0x343, Source);
		BlnField::New("Initialized", 0x348, Source);
		IntField::New("TimeLoaded", 0x34C, Source);
		BlnField::New("InputDisabled", 0x368, Source);
		BlnField::New("TabletPC", 0x36A, Source);
		IntField::New("FrameTime", 0x454, Source);
		BlnField::New("IsDrawing", 0x458, Source);
		IntField::New("DrawCount", 0x480, Source);
		IntField::New("UpdateCount", 0x484, Source);
		IntField::New("UpdateState", 0x488, Source);
		IntField::New("UpdateDepth", 0x48C, Source);
		DblField::New("Speed", 0x490, Source);
		BlnField::New("Paused", 0x498, Source);
		BlnField::New("MouseIn", 0x4CC, Source);
		BlnField::New("Active", 0x4CE, Source);
		BlnField::New("Minimized", 0x4CF, Source);
		BlnField::New("HasFocus", 0x4D2, Source);
		BlnField::New("Loaded", 0x4FB, Source);
		BlnField::New("CtrlDown", 0x5AE, Source);
		BlnField::New("AltDown", 0x5AF, Source);
		BlnField::New("AllowAltEnter", 0x5B0, Source);
#pragma endregion
#pragma region Methods

#pragma endregion
		return 0;
	}
};

Luna::Class::Base::LunaClass* Luna::Class::Classes::LunaAppBase::Source = nullptr;
// OK maybe my naming conventions aren't the best in the long run
// Still gonna use it tho