#include "stdafx.h"
#include "DialogButton.h"

#include "ButtonListener.h"
#include "Resources.h"
#include "Graphics.h"


LawnStoneButton* __stdcall LawnStoneButton::New(int ID, Sexy::ButtonListener* Listener, const PopString& Text)
{
	CONST DWORD Function = 0x448620;
	__asm
	{
		push Text
		push Listener
		push ID
		call Function
	}
}

void __stdcall LawnStoneButton::Draw(Sexy::Graphics* G, int X, int Y, int W, int H, bool Down, bool Highlighted, const PopString& Text)
{
	using namespace Resources;
	auto Right = (Down) ? *StoneButtonRightDown : *StoneButtonRight;
	auto Left = (Down) ? *StoneButtonLeftDown : *StoneButtonLeft;
	auto Middle = (Down) ? *StoneButtonMiddleDown : *StoneButtonMiddle;
	auto Font = (Highlighted) ? *DwarvenTodcraft18BrightGreenInset : *DwarvenTodcraft18GreenInset;

	int Width = W;
	int StartX = X;
	W -= 71;
	int Segments = W / 46;
	int Remaining = W % 46;
	G->DrawImage(Right, X, Y);
	X += 36;
	for (int i = 0; i < Segments; i++)
	{
		G->DrawImage(Middle, X, Y);
		X += 46;
	}
	if (W > 0)
	{
		G->DrawImage(Middle, X, Y, Remaining, 47);
		X += Remaining;
	}
	G->DrawImage(Left, X, Y);
	G->State.Font = Font;

	int SWidth = Font->TextWidth(Text);
	int Height = Font->GetAscent();
	G->State.Color = Color(255, 255, 255);
	G->DrawString(Text, StartX + 1 + (Width - SWidth) / 2, Y - 4 + (Height + (H - Height / 6) - 1) / 2);
}