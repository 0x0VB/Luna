#pragma once
#include "Definitions.h"
#include "UIElement.h"

class Sexy::PreModalInfo
{
	UIElement* BaseModalElement;
	UIElement* PrevBaseModalElement;
	UIElement* PrevFocusElement;
	PopFlags PrevBelowModalFlags;
};