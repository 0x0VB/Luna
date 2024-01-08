#pragma once
namespace Sexy {
	class ButtonListener
	{
		virtual void __thiscall ButtonClick(int ID, int ClickType) {};
		virtual void __thiscall ButtonPress(int ID) {};
		virtual void __thiscall ButtonDepress(int ID) {};
		virtual void __thiscall ButtonDownTick(int ID) {};
		virtual void __thiscall ButtonMouseEnter(int ID) {};
		virtual void __thiscall ButtonMouseLeave(int ID) {};
		virtual void __thiscall ButtonMouseMove(int ID, int X, int Y) {};
	};

	class DialogListener
	{
		virtual void __thiscall DialogButtonPress(int DialogID, int ButtonID) {};
		virtual void __thiscall DialogButtonDepress(int DialogID, int ButtonID) {};
	};

	class CheckBoxListener
	{
		virtual void __thiscall Checked(int ID, bool State) {};
	};
}