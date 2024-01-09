#include "stdafx.h"
#include "Lawn.h"

GridItem* Lawn::AddLadder(int Column, int Lane)
{
	auto New = GridItems.Alloc();
	New->Type = GRIDITEM_LADDER;
	New->RenderOrder = Lane * 10000 + 0x49ED0;
	New->Column = Column;
	New->Lane = Lane;
	return New;
}

GridItem* Lawn::AddCrater(int Column, int Lane)
{
	auto New = GridItems.Alloc();
	New->Type = GRIDITEM_CRATER;
	New->RenderOrder = Lane * 10000 + 0x30D41;
	New->Column = Column;
	New->Lane = Lane;
	New->MainTimer = 100;
	return New;
}

GridItem* Lawn::AddGrave(int Column, int Lane, bool DoEffects)
{
	auto New = GridItems.Alloc();
	New->Type = GRIDITEM_GRAVESTONE;
	New->RenderOrder = Lane * 10000 + 0x497CB;
	New->Column = Column;
	New->Lane = Lane;
	New->MainTimer = 0;
	if (DoEffects) New->DoGraveEffects();
	return New;
}