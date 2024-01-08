#pragma once
#include "Definitions.h"

#include "ButtonListener.h"
#include "UIElement.h"
#include "DataArray.h"
#include "Zombie.h"
#include "Plant.h"
#include "Pickup.h"
#include "LawnMower.h"
#include "GridItem.h"

class Lawn : public Sexy::UIElement, Sexy::ButtonListener
{
public:
	LawnApp* App;
	DataArray<Zombie> Zombies;
	DataArray<Plant> Plants;
	DataArray<Projectile> Projectiles;
	DataArray<Pickup> Pickups;
	DataArray<LawnMower> LawnMowers;
	DataArray<GridItem> GridItems;
	
#pragma region Functions
	GridItem* AddLadder(int Column, int Lane)
	{
		auto New = GridItems.Alloc();
		New->Type = GRIDITEM_LADDER;
		New->RenderOrder = Lane * 10000 + 0x49ED0;
		New->Column = Column;
		New->Lane = Lane;
		return New;
	}
	GridItem* AddCrater(int Column, int Lane)
	{

	}
	GridItem* AddGrave(int Column, int Lane)
	{
		auto New = GridItems.Alloc();
		New->Type = GRIDITEM_GRAVESTONE;
		New->RenderOrder = Lane * 10000 + 0x497CB;
		New->Column = Column;
		New->Lane = Lane;
		New->Age = 0;
		std::cout << New << " " << GridItems.Block << "\n";
		return New;
	}
#pragma endregion

};