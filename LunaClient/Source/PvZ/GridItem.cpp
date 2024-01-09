#include "stdafx.h"
#include "GridItem.h"
void GridItem::DoGraveEffects()
{
	if (MyLawn)
		MyLawn->EnableGraveStones = true;

	DoGraveEffects_Type Function = (DoGraveEffects_Type)(0x44E090);
	Function(this);
}