#pragma once
#include "Definitions.h"
#include "Zombie.h"
#include "Plant.h"
#include "Lawn.h"
#include "Luna.h"

#pragma region Enums
enum GridItemType
{
	GRIDITEM_NONE = 0x0,
	GRIDITEM_GRAVESTONE = 0x1,
	GRIDITEM_CRATER = 0x2,
	GRIDITEM_LADDER = 0x3,
	GRIDITEM_PORTAL_CIRCLE = 0x4,
	GRIDITEM_PORTAL_SQUARE = 0x5,
	GRIDITEM_BRAIN = 0x6,
	GRIDITEM_VASE = 0x7,
	GRIDITEM_SQUIRREL = 0x8,
	GRIDITEM_ZEN_TOOL = 0x9,
	GRIDITEM_STINKY = 0xA,
	GRIDITEM_RAKE = 0xB,
	GRIDITEM_IZOMBIE_BRAIN = 0xC
};
enum GridItemState
{
	GRIDITEM_STATE_NORMAL = 0x0,
	GRIDITEM_STATE_GRAVESTONE_SPECIAL = 0x1,
	GRIDITEM_STATE_PORTAL_CLOSED = 0x2,
	GRIDITEM_STATE_SCARY_POT_QUESTION = 0x3,
	GRIDITEM_STATE_SCARY_POT_LEAF = 0x4,
	GRIDITEM_STATE_SCARY_POT_ZOMBIE = 0x5,
	GRIDITEM_STATE_SQUIRREL_WAITING = 0x6,
	GRIDITEM_STATE_SQUIRREL_PEEKING = 0x7,
	GRIDITEM_STATE_SQUIRREL_RUNNING_UP = 0x8,
	GRIDITEM_STATE_SQUIRREL_RUNNING_DOWN = 0x9,
	GRIDITEM_STATE_SQUIRREL_RUNNING_LEFT = 0xA,
	GRIDITEM_STATE_SQUIRREL_RUNNING_RIGHT = 0xB,
	GRIDITEM_STATE_SQUIRREL_CAUGHT = 0xC,
	GRIDITEM_STATE_SQUIRREL_ZOMBIE = 0xD,
	GRIDITEM_STATE_ZEN_TOOL_WATERING_CAN = 0xE,
	GRIDITEM_STATE_ZEN_TOOL_FERTILIZER = 0xF,
	GRIDITEM_STATE_ZEN_TOOL_BUG_SPRAY = 0x10,
	GRIDITEM_STATE_ZEN_TOOL_PHONOGRAPH = 0x11,
	GRIDITEM_STATE_ZEN_TOOL_GOLD_WATERING_CAN = 0x12,
	GRIDITEM_STINKY_WALKING_LEFT = 0x13,
	GRIDITEM_STINKY_TURNING_LEFT = 0x14,
	GRIDITEM_STINKY_WALKING_RIGHT = 0x15,
	GRIDITEM_STINKY_TURNING_RIGHT = 0x16,
	GRIDITEM_STINKY_SLEEPING = 0x17,
	GRIDITEM_STINKY_FALLING_ASLEEP = 0x18,
	GRIDITEM_STINKY_WAKING_UP = 0x19,
	GRIDITEM_STATE_RAKE_ATTRACTING = 0x1A,
	GRIDITEM_STATE_RAKE_WAITING = 0x1B,
	GRIDITEM_STATE_RAKE_TRIGGERED = 0x1C,
	GRIDITEM_STATE_BRAIN_SQUISHED = 0x1D
};
enum VaseType
{
	VASE_NONE = 0x0,
	VASE_SEED = 0x1,
	VASE_ZOMB = 0x2,
	VASE_SUN = 0x3
};
#pragma endregion


struct MotionTrailFrame
{
	FVector2 Position;
	float AnimTime;
};

class GridItem
{
	typedef void(__stdcall* DoGraveEffects_Type)(GridItem*);
public:
	LawnApp* App;
	Lawn* MyLawn;
	GridItemType Type;
	GridItemState State;
	int Column;
	int Lane;
	int MainTimer;
	int RenderOrder;
	bool Dead;
	FVector2 Position;
	FVector2 Goal;
	ReanimationID ReanimID;
	ParticleSystemID ParticleID;
	ZombieType ZombieType;
	SeedType SeedType;
	VaseType VaseType;
	bool Highlighted;
	int TransparentTimer;
	int SunCount;
	MotionTrailFrame MotionTrailFrames[12];
	int MotionTrailCount;

	GridItem()
	{
		App = Luna::App;
		MyLawn = App->Lawn;
		Type = GRIDITEM_NONE;
		State = GRIDITEM_STATE_NORMAL;
		Column = 0;
		Lane = 0;
		MainTimer = 0;
		RenderOrder = 0;
		Dead = false;
		Position = FVector2();
		Goal = FVector2();
		ReanimID = REANIMATIONID_NULL;
		ParticleID = PARTICLESYSTEMID_NULL;
		ZombieType = ZOMBIE_INVALID;
		SeedType = SEED_NONE;
		VaseType = VASE_NONE;
		Highlighted = false;
		TransparentTimer = 0;
		SunCount = 0;
		MotionTrailCount = 0;
	}
	void DoGraveEffects();
};