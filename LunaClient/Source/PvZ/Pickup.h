#pragma once
#include "Definitions.h"
#include "PottedPlant.h"
#include "Lawn.h"

class Pickup : public GameObject
{
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
	PickupMotion CoinMotion;
	AttachmentID AttachmentID;
	float CollectionDistance;
	SeedType UsableSeedType;
	PottedPlant PottedPlantSpec;
	bool NeedsBouncyArrow;
	bool HasBouncyArrow;
	bool HitGround;
	int TimesDropped;
};