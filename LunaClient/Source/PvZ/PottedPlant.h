#pragma once
#include "Definitions.h"

class PottedPlant
{
	SeedType SeedType;
	GardenType WhichZenGarden;
	IVector2 Positon;
	int Facing;
	__int64 LastWateredTime;
	DrawVariation DrawVariation;
	PottedPlantAge PlantAge;
	int TimesFed;
	int FeedingsPerGrow;
	PottedPlantNeed PlantNeed;
	__int64 LastNeedFulfilledTime;
	__int64 LastFertilizedTime;
	__int64 LastChocolateTime;
	int FutureAttribute[1];
};