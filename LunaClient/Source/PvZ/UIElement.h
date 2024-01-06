#pragma once
#include "Definitions.h"

class Sexy::UIContainer
{
public:
	UIContainer();

#pragma region Fields
	PopList<UIElement*> Children;
	UIRoot* Root;
	UIContainer* Parent;
	bool UpdateIteratorModified;
	int IteratorPad;
	std::list<UIElement*>::iterator UpdateIterator;
	unsigned long LastWMUpdateCount;
	int UpdateCnt;
	bool Dirty;
	IRect Bounds;
	bool ClipChildren;
	PopFlags UIFlagsMod;
	int Priority;
	int ZIndex;
#pragma endregion

#pragma region Virtual Functions
	virtual ~UIContainer() {};// 00
	virtual IRect* GetRect(const IRect* Out) = 0;// 04
	virtual bool Intersects(UIContainer* Other)  = 0;// 08
	virtual void AddChild(UIElement* Child)  = 0;// 0C
	virtual void RemoveChild(UIElement* Child)  = 0;// 10
	virtual bool HasChild(UIElement* Child)  = 0;// 14
	virtual void DisableWidget(UIElement* Child)  = 0;// 18
	virtual void ClearChildren(bool Delete, bool Recursive)  = 0;// 1C
	virtual void SetFocus(UIElement* Child)  = 0;// 20
	virtual bool IsBelow(UIElement* E1, UIElement* E2)  = 0;// 24
	virtual void MarkAllDirty()  = 0;// 28
	virtual void BringToFront(UIElement* Child)  = 0;// 2C
	virtual void BringToBack(UIElement* Child)  = 0;// 30
	virtual void PutBehind(UIElement* Child, UIElement* Ref)  = 0;// 34
	virtual void PutInFront(UIElement* Child, UIElement* Ref)  = 0;// 38
	virtual IVector2* GetAbsPos(const IVector2* Out)  = 0;// 3C
	virtual void MarkDirty(UIElement* Child)  = 0;// 40
	virtual void MarkDirty()  = 0;// 44
	virtual void MarkDirtyFull(UIContainer* Child)  = 0;// 48
	virtual void MarkDirtyFull()  = 0;// 4C
	virtual void AddedToRoot(UIRoot* Root)  = 0;// 50
	virtual void RemovedFromRoot(UIRoot* Root)  = 0;// 54
	virtual void Update()  = 0;// 58
	virtual void UpdateAll()  = 0;// 5C
	virtual void Unk2(DWORD)  = 0;// 60
	virtual void UpdateFAll(float Frac)  = 0;// 64
	virtual void Draw(Graphics* G)  = 0;// 68
	virtual void DrawAll(PopModalFlags* Flags, Graphics* G)  = 0;// 6C
	virtual void SysColorChangedAll()  = 0;// 70
	virtual void Unk4()  = 0;// 74
#pragma endregion
};

enum MBNum { MBN_Left, MBN_Right, MBN_Middle };
class Sexy::UIElement : public Sexy::UIContainer
{
public:
	UIElement();
#pragma region Fields
	bool Visible;
	bool MouseVisible;
	bool Disabled;
	bool HasFocus;
	bool IsDown;
	bool IsOver;
	bool HasTransparencies;

	PopVector<Color> Colors;
	Pad MousePadding;
	bool DoFinger;
	bool WantsFocus;
	UIElement* Prev;
	UIElement* Next;
#pragma endregion

#pragma region Virtual functions
	virtual ~UIElement() = 0;// 00
	virtual void Unk5() {}; // 78
	virtual void SetVisibile(bool Visible) {}; // 7C
	virtual void SetColorsAlpha(int Colors[][4], int ColorNum) = 0;// 80
	virtual void SetColors(int Colors[][3], int ColorNum) = 0;// 84
	virtual void SetColor(int Index, const Color& Color) = 0;// 88
	virtual Color* GetColorOut(const Color* Out, int Idx, const Color& Default) = 0;// 8C
	virtual const Color& GetColor(int Idx) = 0;// 90
	virtual void SetDisabled(bool Disabled) = 0;// 94
	virtual void ShowFinger(bool On) = 0;// 98
	virtual void ResizeRect(IRect* NewSize) = 0;// 9C
	virtual void Resize(int X, int Y, int W, int H) = 0;// A0
	virtual void Move(int X, int Y) = 0;// A4
	virtual bool WantFocus() = 0;// A8
	virtual void DrawOverlay(Graphics* G, int Priority) = 0;// AC
	virtual void Unk6(DWORD) = 0;// B0
	virtual void GotFocus() = 0;// B4
	virtual void LostFocus() = 0;// B8
	virtual void Unk7(DWORD) = 0;// BC
	virtual void KeyDown(int KeyCode) = 0;// C0
	virtual void KeyUp(int KeyCode) = 0;// C4
	virtual void MouseEnter() = 0;// C8
	virtual void MouseLeave() = 0;// CC
	virtual void MouseMove(int X, int Y) = 0;// D0
	virtual void MouseBDown(int X, int Y, MBNum Btn, int ClickCount) = 0;// D4
	virtual void MouseDown(int X, int Y, int ClickCount) = 0;// D8
	virtual void MouseBUp(int X, int Y, int BtnNum, int ClickCount) = 0;// DC
	virtual void MouseCUp(int X, int Y, int ClickCount) = 0;// E0
	virtual void MouseUp(int X, int Y) = 0;// E4
	virtual void UnkC(DWORD, DWORD) = 0;// E8
	virtual void UnkD(DWORD) = 0;// EC
	virtual bool IsPointVisible(int X, int Y) = 0;// F0
	virtual IRect* WriteCenteredLineColor(const IRect* Out, Graphics* G, int Offset, const PopString& Text, Color Color1, Color Color2, IVector2 ShadowOffset) = 0;// F4
	virtual IRect* WriteCenteredLine(const IRect* Out, Graphics* G, int Offset, const PopString& Text) = 0;// F8
	virtual int WriteString(Graphics* G, const PopString& Text, int X, int Y, int Width, int Justification, bool DrawString, int Offset, int Length) = 0;// FC | Returns the XOffset
	virtual int WriteWordWrapped(Graphics* G, const IRect& Rect, const PopString& Text, int LineSpacing, int Justification) = 0;// 100 | Returns the text height
	virtual int GetWordWrappedHeight(Graphics* G, int Width, const PopString& Text, int LineSpacing) = 0;// 104
	virtual int GetNumDigits(int Number) = 0;// 108
	virtual int WriteNumberFromStrip(Graphics* G, int Number, int X, int Y, Image* Strip, int Spacing) = 0;// 10C
	virtual bool Contains(int X, int Y) = 0;// 110
	virtual IRect* GetInsetRect(const IRect* Out) = 0;// 114
#pragma endregion
};