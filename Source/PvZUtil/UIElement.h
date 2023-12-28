#pragma once
class Sexy::UIContainer
{
public:
	UIContainer()
	{
		CONST DWORD Func = 0x536F00;
		__asm
		{
			mov esi, this
			call Func
		}
	}

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
	virtual ~UIContainer();// 00
	virtual IRect** GetRect(_Out_ IRect&& Out);// 04
	virtual bool Intersects(UIContainer* Other);// 08
	virtual void AddChild(UIElement* Child);// 0C
	virtual void RemoveChild(UIElement* Child);// 10
	virtual bool HasChild(UIElement* Child);// 14
	virtual void DisableWidget(UIElement* Child);// 18
	virtual void ClearChildren(bool Delete, bool Recursive);// 1C
	virtual void SetFocus(UIElement* Child);// 20
	virtual bool IsBelow(UIElement* E1, UIElement* E2);// 24
	virtual void MarkAllDirty();// 28
	virtual void BringToFront(UIElement* Child);// 2C
	virtual void BringToBack(UIElement* Child);// 30
	virtual void PutBehind(UIElement* Child, UIElement* Ref);// 34
	virtual void PutInFront(UIElement* Child, UIElement* Ref);// 38
	virtual IVector2&& GetAbsPos(_Out_ IVector2&& Out);// 3C
	virtual void MarkDirty(UIElement* Child);// 40
	virtual void MarkDirty();// 44
	virtual void MarkDirtyFull(UIContainer* Child);// 48
	virtual void MarkDirtyFull();// 4C
	virtual void AddedToRoot(UIRoot* Root);// 50
	virtual void RemovedFromRoot(UIRoot* Root);// 54
	virtual void Update();// 58
	virtual void UpdateAll();// 5C
	virtual void Unk2(DWORD);// 60
	virtual void UpdateFAll(float Frac);// 64
	virtual void Draw(Graphics* G);// 68
	virtual void DrawAll(PopModalFlags* Flags, Graphics* G);// 6C
	virtual void SysColorChangedAll();// 70
	virtual void Unk4();// 74
#pragma endregion
};

enum MBNum { MBN_Left, MBN_Right, MBN_Middle };
class Sexy::UIElement : public Sexy::UIContainer
{
public:
	UIElement()
	{
		CONST DWORD Function = 0x5396F0;
		__asm
		{
			push this
			call Function
		}
	}
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
	virtual ~UIElement();// 00
	virtual void Unk5(); // 78
	virtual void SetVisibile(bool Visible); // 7C
	virtual void SetColors(int Colors[][4], int ColorNum);// 80
	virtual void SetColors(int Colors[][3], int ColorNum);// 84
	virtual void SetColor(int Index, const Color& Color);// 88
	virtual Color&& GetColor(_Out_ Color&& Out, int Idx, const Color& Default);// 8C
	virtual const Color& GetColor(int Idx);// 90
	virtual void SetDisabled(bool Disabled);// 94
	virtual void ShowFinger(bool On);// 98
	virtual void Resize(IRect* NewSize);// 9C
	virtual void Resize(int X, int Y, int W, int H);// A0
	virtual void Move(int X, int Y);// A4
	virtual bool WantFocus();// A8
	virtual void DrawOverlay(Graphics* G, int Priority);// AC
	virtual void Unk6(DWORD);// B0
	virtual void GotFocus();// B4
	virtual void LostFocus();// B8
	virtual void Unk7(DWORD);// BC
	virtual void KeyDown(int KeyCode);// C0
	virtual void KeyUp(int KeyCode);// C4
	virtual void MouseEnter();// C8
	virtual void MouseLeave();// CC
	virtual void MouseMove(int X, int Y);// D0
	virtual void MouseDown(int X, int Y, MBNum Btn, int ClickCount);// D4
	virtual void MouseDown(int X, int Y, int ClickCount);// D8
	virtual void MouseUp(int X, int Y, int BtnNum, int ClickCount);// DC
	virtual void MouseUp(int X, int Y, int ClickCount);// E0
	virtual void MouseUp(int X, int Y);// E4
	virtual void UnkC(DWORD, DWORD);// E8
	virtual void UnkD(DWORD);// EC
	virtual bool IsPointVisible(int X, int Y);// F0
	virtual IRect&& WriteCenteredLine(_Out_ IRect&& Out, Graphics* G, int Offset, const PopString& Text, Color Color1, Color Color2, IVector2 ShadowOffset);// F4
	virtual IRect&& WriteCenteredLine(_Out_ IRect&& Out, Graphics* G, int Offset, const PopString& Text);// F8
	virtual int WriteString(Graphics* G, const PopString& Text, int X, int Y, int Width, int Justification, bool DrawString, int Offset, int Length);// FC | Returns the XOffset
	virtual int WriteWordWrapped(Graphics* G, const IRect& Rect, const PopString& Text, int LineSpacing, int Justification);// 100 | Returns the text height
	virtual int GetWordWrappedHeight(Graphics* G, int Width, const PopString& Text, int LineSpacing);// 104
	virtual int GetNumDigits(int Number);// 108
	virtual int WriteNumberFromStrip(Graphics* G, int Number, int X, int Y, Image* Strip, int Spacing);// 10C
	virtual bool Contains(int X, int Y);// 110
	virtual IRect&& GetInsetRect(_Out_ IRect&& Out);// 114
#pragma endregion
};