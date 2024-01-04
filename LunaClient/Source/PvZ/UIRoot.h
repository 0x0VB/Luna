#pragma once
#include "Definitions.h"
#include "UIElement.h"
#include "PreModalInfo.h"

class Sexy::UIRoot : public Sexy::UIContainer
{
public:
	UIRoot();
#pragma region Fields
	UIElement* DefaultTab;
	Graphics* CurrentGraphics;
	SexyAppBase* App;
	MemoryImage* Image;
	MemoryImage* TransientImage;
	bool LastHadTransients;

	UIElement* PopupCommandElement;
	PopVector<UIElement*> DeferredOverlayElements;
	int MinDeferredOverlayPriority;
	bool HasFocus;
	UIElement* FocusedElement;
	UIElement* LastDownElement;
	UIElement* OverElement;
	UIElement* BaseModalElement;
	PopFlags LostFocusFlags;
	PopFlags BelowModalFlags;
	PopFlags DefaultBelowModalFlags;
	PopList<PreModalInfo> PreModalInfoList;
	IRect MouseDestRect;
	IRect MouseSourceRect;
	bool MouseIn;
	IVector2 LastMousePos;
	int DownButtons;
	int ActualDownButtons;
	int LastUpdateCnt;
	bool KeysDown[255];
	int LastDownButtonID;
	int ElementFlags;
#pragma endregion

#pragma region Virtual Functions
	virtual ~UIRoot() {};
#pragma endregion
};