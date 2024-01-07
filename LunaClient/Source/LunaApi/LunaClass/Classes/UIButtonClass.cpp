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

NewLawnButton* Construct(
	Sexy::Image* DownImage,
	Sexy::Image* ButtonImage,
	int id,
	Sexy::ButtonListener* ButtonListenerPtr,
	PopString* Text,
	Sexy::Font* Font,
	Sexy::Image* OverImage)
{
	NewLawnButton* Res = nullptr;
	__asm
	{
		mov     eax, OverImage
		push    eax
		mov		eax, Font
		push    eax
		mov     eax, Text
		push    eax
		mov     eax, ButtonListenerPtr
		push    eax
		mov     eax, id
		push    eax
		mov     edi, ButtonImage
		mov     ebx, DownImage
		mov		eax, 0x448BC0
		call    eax
		xor		ebx, ebx
		add     esp, 0x14
		mov     Res, eax
	}
	return Res;
}

int LunaUIButton::Constructor(lua_State* L)
{
	Sexy::Image* MainImage = (Sexy::Image*)GetLunaImage(L, 2, "ButtonImage", true, true)->GetBase();
	PopString Label = PopString(GetString(L, 3, "Luna!"));

	auto Button = Construct(nullptr, MainImage, 0, nullptr, &Label, *Resources::Pico129, nullptr);
	CreateUIObject(L, Button);

	return 1;
}