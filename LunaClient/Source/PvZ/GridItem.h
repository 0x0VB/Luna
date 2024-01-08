#pragma once
#include "Definitions.h"

struct MotionTrailFrame
{
	FVector2 Position;
	float AnimTime;
};

class GridItem
{
public:
	LawnApp* App;
	Lawn* Lawn;
	GridItemType GridItemType;
	GridItemState GridItemState;
	int GridX;
	int GridY;
	int GridItemCounter;
	int RenderOrder;
	bool Dead;
	float PosX;
	float PosY;
	float GoalX;
	float GoalY;
	ReanimationID GridItemReanimID;
	ParticleSystemID GridItemParticleID;
	ZombieType ZombieType;
	SeedType SeedType;
	VaseType VaseType;
	bool Highlighted;
	int TransparentCounter;
	int SunCount;
	MotionTrailFrame MotionTrailFrames[12];
	int MotionTrailCount;
};