#pragma once

Sexy::LawnStoneButton* Sexy::UIContainer::NewStoneButton(std::string Text, int ID, ButtonListener* Listener)
{
	CONST DWORD CreateStoneButtonA = 0x448620;
	LawnStoneButton* NewButton = NULL;
	PopString Label = PopString(Text);
	auto LabelA = &Label;
	__asm
	{
		push LabelA
		push Listener
		push ID
		call CreateStoneButtonA
		mov NewButton, eax
	}
	*(Rect*)((DWORD)NewButton + 0x30) = Rect(0, 0, 200, 46);
	this->AddChild(NewButton);
	return NewButton;
}