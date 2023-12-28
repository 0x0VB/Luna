#pragma once
class Sexy::PreModalInfo
{
public:
	UIElement* BaseModalElement;
	UIElement* PrevBase;
	UIElement* PrevFocus;
	PopFlags BelowFlags;
};
class Sexy::UIRoot : public UIContainer
{
public:
	UIElement* DefaultTab;
	Graphics* CurrentGraphics;
	LawnApp* App;
	MemoryImage* Image;
	MemoryImage* TransientImage;
	bool LastHadTransparencies;
	UIElement* PopupCommand;
	PopVector<UIElement*> DeferredOverlayElements;
	int MinDeferredOverlayPriority;
	bool HasFocus;
	UIElement* FocusedElement;
	UIElement* LastDownElement;
	UIElement* HoveredElement;
	UIElement* BaseModalElement;
	PopFlags FocusFlags;
	PopFlags BelowFlags;
	PopFlags DefaultBelowFlags;
	PopList<PreModalInfo> PreModalInfoList;
	Rect MouseDest;
	Rect MouseSource;
	bool MouseIn;
	IVector2 LastMousePos;
	DWORD DownButtons;
	DWORD ActualDownButtons;
	int LastUpdateCnt;
	bool KeyDown[255];
	int LastDownButtonID;
	int ElementFlags;
};