#pragma once
#include "Definitions.h"
#include "PottedPlant.h"
#include "Lawn.h"

#pragma region Enums
enum PickupMotion
{
	PICK_MOTION_FROM_SKY = 0x0,
	PICK_MOTION_FROM_SKY_SLOW = 0x1,
	PICK_MOTION_FROM_PLANT = 0x2,
	PICK_MOTION_COIN = 0x3,
	PICK_MOTION_LAWNMOWER_COIN = 0x4,
	PICK_MOTION_FROM_PRESENT = 0x5,
	PICK_MOTION_FROM_BOSS = 0x6,
};

enum PickupType
{
	PICK_NONE = 0x0,
	PICK_SILVER = 0x1,
	PICK_GOLD = 0x2,
	PICK_DIAMOND = 0x3,
	PICK_SUN = 0x4,
	PICK_SMALLSUN = 0x5,
	PICK_LARGESUN = 0x6,
	PICK_FINAL_SEED_PACKET = 0x7,
	PICK_TROPHY = 0x8,
	PICK_SHOVEL = 0x9,
	PICK_ALMANAC = 0xA,
	PICK_CARKEYS = 0xB,
	PICK_VASE = 0xC,
	PICK_WATERING_CAN = 0xD,
	PICK_TACO = 0xE,
	PICK_NOTE = 0xF,
	PICK_USABLE_SEED_PACKET = 0x10,
	PICK_PRESENT_PLANT = 0x11,
	PICK_AWARD_MONEY_BAG = 0x12,
	PICK_AWARD_PRESENT = 0x13,
	PICK_AWARD_BAG_DIAMOND = 0x14,
	PICK_AWARD_SILVER_SUNFLOWER = 0x15,
	PICK_AWARD_GOLD_SUNFLOWER = 0x16,
	PICK_CHOCOLATE = 0x17,
	PICK_AWARD_CHOCOLATE = 0x18,
	PICK_PRESENT_MINIGAMES = 0x19,
	PICK_PRESENT_PUZZLE_MODE = 0x1A,
};

#pragma endregion

class Pickup : public GameObject
{
#pragma region Fields
public:
	FVector2 Position;
	FVector2 Velocity;
	float Scale;
	bool Dead;
	int FadeCount;
	FVector2 CollectPos;
	int Floor;
	int Age;
	bool IsBeingCollected;
	int VanishTimer;
	PickupType Type;
	PickupMotion Motion;
	AttachmentID AttachmentID;
	float CollectionDistance;
	SeedType UsableSeedType;
	PottedPlant PottedPlantSpec;
	bool NeedsBouncyArrow;
	bool HasBouncyArrow;
	bool HitGround;
	int TimesDropped;
#pragma endregion
	Pickup()
	{
		App = Luna::App;
		MyLawn = Luna::App->Lawn;
		Lane = 0;
		RenderOrder = 400000;
		Visible = true;
		VanishTimer = 1000;
	}

	void __thiscall Initialize(int X, int Y, PickupType Type = PICK_SUN, PickupMotion Motion = PICK_MOTION_COIN);
};
