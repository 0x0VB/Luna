#pragma once
class Sexy::UIContainer
{
public:
	PopList<UIElement*> Children;
	UIRoot* Root;
	UIContainer* Parent;
	bool UpdateIteratorModified;
	double Iterator;
	unsigned long LastWMUpdateCount;
	int UpdateCnt;
	bool Dirty;
	Rect Bounds;
	bool HasAlpha;
	bool Clip;
	PopFlags Flags;
	int Priority;
	int ZIndex;

	LawnStoneButton* NewStoneButton(std::string Text, int ID, ButtonListener* Listener);

	virtual ~UIContainer();
	virtual Rect* __thiscall GetRect(Rect* Out);
	virtual bool __thiscall Intersects(void* Other);
	virtual void __thiscall AddChild(void* Child);
	virtual void __thiscall RemoveChild(void* Child);
	virtual bool __thiscall HasChild(void* Child);
	virtual void __thiscall DisableChild(void* Child);
	virtual void __thiscall ClearChildren(bool Destruct, bool Recursive);
	virtual void __thiscall SetFocus(void* Child);
	virtual bool __thiscall IsBelow(void* Child1, void* Child2);
	virtual void __thiscall MarkAllDirty();
	virtual void __thiscall BringToFront(void* Child);
	virtual void __thiscall BringToBack(void* Child);
	virtual void __thiscall PutBehind(void* Child, void* Other);
	virtual void __thiscall PutInFront(void* Child, void* Other);
	virtual Rect* __thiscall AbsolutePosition(Rect* Out);
	virtual void __thiscall MarkDirty(void* Child);
	virtual void __thiscall MakeDirty();
	virtual void __thiscall MarkDirtyFull(void* Child);
	virtual void __thiscall MarkDirtyFull();
	virtual void __thiscall AddedToManager(void* Manager);
	virtual void __thiscall RemovedFromManager(void* Manager);
	virtual void __thiscall Update();
	virtual void __thiscall UpdateAll(PopFlags*);
	virtual void __thiscall UpdateF(float);
	virtual void __thiscall UpdateFAll(PopFlags*, float);
	virtual void __thiscall Draw(Graphics*);
	virtual void __thiscall DrawAll(PopFlags*, Graphics*);
	virtual void __thiscall SysColorChangedAll();
	virtual void __thiscall SysColorChanged();
};

class Sexy::UIElement : public UIContainer
{
public:
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
};