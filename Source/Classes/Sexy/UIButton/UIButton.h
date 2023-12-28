#pragma once
class Sexy::ButtonListener
{
	virtual void __thiscall ButtonPress(int ID, int ClickType) {};
	virtual void __thiscall ButtonPress2(int ID) {};
	virtual void __thiscall ButtonDepress(int ID) {};
	virtual void __thiscall ButtonDownTick(int ID) {};
	virtual void __thiscall ButtonMouseEnter(int ID) {};
	virtual void __thiscall ButtonMouseLeave(int ID) {};
	virtual void __thiscall ButtonMouseMove(int ID, int X, int Y) {};
};

class Sexy::UIButton : public UIElement
{
public:
	int ID;
	PopString Text;
	int TextAlign;
	Font* Font;
	
	Image* ButtonImage;
	Image* OverImage;
	Image* DownImage;
	Image* DisabledImage;
	
	Rect Bounds;
	Rect OverRect;
	Rect DownRect;
	Rect DisabledRect;

	bool Inverted;
	bool NoDraw;
	bool FrameNoDraw;
	ButtonListener* Listener;
	double OverAlpha;
	double OverAlphaSpeed;
	double OverAlphaFadeInSpeed;
};

class Sexy::UIDialogButton : public UIButton
{
public:
	Image* ComponentImage;
	IVector2 Offset;
	IVector2 TextOffset;
	DWORD Pad;
};

class Sexy::LawnStoneButton : public UIDialogButton
{
public:
	LawnStoneButton();
	static LawnStoneButton* New(const char* Text, ButtonListener* Listener, int ID)
	{
		CONST DWORD Function = 0x541080;
		LawnStoneButton* self = (LawnStoneButton*)new BYTE(sizeof(LawnStoneButton));
		memset(self, 0, sizeof(LawnStoneButton));
		self->Text = Text;
		__asm
		{
			mov ecx, ID
			push Listener
			push self
			call Function
			mov [eax], 0x658838
		}
		return self;
	}
};