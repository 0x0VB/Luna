#pragma once
#include "Definitions.h"

#include "ButtonListener.h"
#include "UIElement.h"
#include "DataArray.h"
#include "Zombie.h"

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
	
};