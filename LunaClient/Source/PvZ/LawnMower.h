#pragma once
#include "Definitions.h"

#pragma region Enums
enum LawnMowerType
{
	MOWER_LAWN = 0x0,
	MOWER_POOL = 0x1,
	MOWER_ROOF = 0x2,
	MOWER_SUPER_MOWER = 0x3,
	NUM_MOWER_TYPES = 0x4
};
enum LawnMowerState
{
	MOWER_ROLLING_IN = 0x0,
	MOWER_READY = 0x1,
	MOWER_TRIGGERED = 0x2,
	MOWER_SQUISHED = 0x3
};
enum MowerHeight
{
	MOWER_HEIGHT_LAND = 0x0,
	MOWER_HEIGHT_DOWN_TO_POOL = 0x1,
	MOWER_HEIGHT_IN_POOL = 0x2,
	MOWER_HEIGHT_UP_TO_LAND = 0x3
};
#pragma endregion

class LawnMower : public GameObject
{
public:
	LawnApp* App;
	Lawn* Board;
	FVector2 Position;
	int RenderOrder;
	int Row;
	int AnimTicksPerFrame;
	ReanimationID ReanimID;
	int ChompCounter;
	int RollingInCounter;
	int SquishedCounter;
	LawnMowerState MowerState;
	bool Dead;
	bool Visible;
	LawnMowerType MowerType;
	float Altitude;
	MowerHeight MowerHeight;
	int LastPortalX;
};