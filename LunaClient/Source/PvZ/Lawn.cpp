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

GridItem* Lawn::AddCrater(int Column, int Lane, bool KillPlants)
{
	Plant* Current = NULL;
	auto New = GridItems.Alloc();
	New->Type = GRIDITEM_CRATER;
	New->RenderOrder = Lane * 10000 + 0x30D41;
	New->Column = Column;
	New->Lane = Lane;
	New->MainTimer = 100;

	if (KillPlants)
		while (Plants.Next(&Current))
			if (Current->Column == Column && Current->Lane == Lane)
				Current->Die();

	return New;
}

GridItem* Lawn::AddGrave(int Column, int Lane, bool DoEffects, bool KillPlants)
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

GridItem* Lawn::AddPortal(int Column, int Lane, bool IsSquare)
{
	auto New = GridItems.Alloc();
	New->Type = (IsSquare) ? GRIDITEM_PORTAL_SQUARE : GRIDITEM_PORTAL_CIRCLE;
	New->RenderOrder = Lane * 10000 + 0x4AF38;
	New->Column = Column;
	New->Lane = Lane;
	New->OpenPortal();
	return New;
}

GridItem* Lawn::AddBrain(int X, int Y, bool IsZomb)
{
	auto New = GridItems.Alloc();
	New->Type = (IsZomb) ? GRIDITEM_BRAIN : GRIDITEM_IZOMBIE_BRAIN;
	if (IsZomb)
	{
		New->RenderOrder = Y * 10000 + 0x30D40;
		New->Position = IVector2(X, Y);
	}
	else
	{
		New->RenderOrder = 0x49BB0;
		New->MainTimer = 70;
		New->Column = X;
		New->Lane = Y;
		New->Position = IVector2(50, 50);
	}
	
	return New;
}

Pickup* Lawn::AddPickup(int X, int Y, PickupType Type, PickupMotion Motion)
{
	auto New = Pickups.Alloc();
	New->Initialize(X, Y, Type, Motion);
	return New;
}

void Lawn::KillPlantCell(int Col, int Lane)
{
	Plant* Current = NULL;
	while (Plants.Next(&Current))
		if (Current->Column == Col && Current->Lane == Lane)
			Current->Die();
}

void Lawn::KillPlantLane(int Lane)
{
	Plant* Current = NULL;
	while (Plants.Next(&Current))
		if (Current->Lane == Lane)
			Current->Die();
}

void Lawn::KillPlantCol(int Col)
{
	Plant* Current = NULL;
	while (Plants.Next(&Current))
		if (Current->Column == Col)
			Current->Die();
}