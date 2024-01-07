#include "stdafx.h"
#include "UIButtonClass.h"

#include "LunaApi/LunaStructs/Rect/Rect.h"
#include "LunaApi/LunaUtil/LunaUtil.h"
#include "LunaApi/LunaIO/LunaIO.h"

#include "PvZ/ButtonListener.h"
#include "PvZ/DialogButton.h"
#include "PvZ/UIElement.h"
#include "PvZ/Resources.h"
#include "PvZ/UIRoot.h"
#include "PvZ/Font.h"
#include "Luna.h"

#include "LunaBase.h"
#include "UIElementClass.h"
#include "UIContainerClass.h"
#include "StoneButtonClass.h"
#include "ImageClass.h"

using namespace Luna::Class;
using namespace Fields;

namespace
{
	class ButtonBounds : public LunaField
	{
	public:
		virtual void __index(lua_State* L) override
		{
			auto self = (Sexy::UIButton*)GetSelf(L)->GetBase();
			self->Bounds.Push(L);
		}
		virtual void __newindex(lua_State* L) override
		{
			auto self = (Sexy::UIButton*)GetSelf(L)->GetBase();
			auto Value = GetRect(L, 2, "Bounds");
			self->Bounds = Value;
			self->NormalRect = Value;
			self->OverRect = Value;
			self->DownRect = Value;
			self->DisabledRect = Value;
		}
		DefNewField(ButtonBounds)
	};
}

LunaClass* LunaUIButton::Source = new LunaClass();
int LunaUIButton::Init(lua_State* L)
{
	Source->AllowsInjection = true;
	Source->SetName("UIButton");
	Source->AddSubClass("BaseButton");
	Source->Inherit(LunaUIElement::Source);

	// TODO: Font
	ButtonBounds::New("Bounds", 0, Source);
	ImageField::New("NormalImage", 0xB0, Source);
	ImageField::New("HoveredImage", 0xB4, Source);
	ImageField::New("DownImage", 0xB8, Source);
	ImageField::New("DisabledImage", 0xBC, Source);

	StrField::New("Text", 0x90, Source);
	RctField::New("TrueBounds", 0x30, Source);
	RctField::New("NormalBounds", 0xC0, Source);
	RctField::New("HoveredBounds", 0xD0, Source);
	RctField::New("DownBounds", 0xE0, Source);
	RctField::New("DisabledBounds", 0xF0, Source);
	BlnField::New("Inverted", 0x100, Source);
	BlnField::New("NoDraw", 0x101, Source);

	return 0;
}

// Yes i know this isnt the best way to do it uniqua, im desprate at this point
auto Listener = Sexy::ButtonListener();
NewLawnButton* _Out;
Sexy::Image* _MainImage;
PopString* _Label;
Sexy::Font* _Font;

void __declspec(naked) Construct()
{
	__asm
	{
		pushad
		mov ebx, _MainImage
		mov edi, _MainImage
		push _MainImage
		push _Font
		push _Label
		push Listener
		push 00
		mov eax, 0x448BC0
		call eax
		mov _Out, eax
		popad
		add esp, 0x14
		ret
	}
}
int LunaUIButton::Constructor(lua_State* L)
{
	Sexy::Image* MainImage = (Sexy::Image*)GetLunaImage(L, 2, "ButtonImage", true, true)->GetBase();
	PopString Label = PopString(GetString(L, 3, "Luna!"));

	_Label = &Label;
	_Font = *Resources::Pico129;
	_MainImage = MainImage;
	Construct();// If you comment this line it returns properly
	std::cout << _Out << "\n";// this works fine, it even prints correctly

	//CreateUIObject(L, Button);// Commented this just to make sure this isn't whats breaking the code
	return 0;// Returns incorrectly for some reason???
}