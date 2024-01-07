#pragma once
#include "Definitions.h"
#include "UIButton.h"

class Sexy::UIDialogButton : public Sexy::UIButton
{
public:
	Image* ComponentImage;
	IVector2 Translation;
	IVector2 TextOffset;

	virtual ~UIDialogButton();
};

class NewLawnButton : public Sexy::UIDialogButton
{
public:
	Sexy::Font* HilightFont;
	IVector2 TextDownOffset;

	virtual ~NewLawnButton();
};

class LawnStoneButton : public Sexy::UIDialogButton
{
public:
	virtual ~LawnStoneButton();
	void ResizeToFit();
	static LawnStoneButton* __stdcall New(int ID, Sexy::ButtonListener* Listener, const PopString& Text);
	static void __stdcall Draw(LawnStoneButton* self, Sexy::Graphics* G, int X, int Y, int W, int H, bool Down, bool Highlighted, const PopString& Text);
};