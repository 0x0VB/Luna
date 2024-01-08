#pragma once
#include "Definitions.h"

struct MagnetItem
{
	FVector2 Position;
	FVector2 Destination;
	MagnetItemType ItemType;
};

class Plant : public GameObject
{
public:
	SeedType Type;
	int Column;
	int AnimCounter;
	int Frame;
	int FrameLength;
	int NumFrames;
	PlantState State;
	int PlantHealth;
	int PlantMaxHealth;
	int Subclass;
	int DisappearCountdown;
	int DoSpecialCountdown;
	int StateCountdown;
	int LaunchCounter;
	int LaunchRate;
	IRect PlantRect;
	IRect PlantAttackRect;
	int TargetX;
	int TargetY;
	int StartRow;
	ParticleSystemID ParticleID;
	int ShootingCounter;
	ReanimationID BodyReanimID;
	ReanimationID HeadReanimID;
	ReanimationID HeadReanimID2;
	ReanimationID HeadReanimID3;
	ReanimationID BlinkReanimID;
	ReanimationID LightReanimID;
	ReanimationID SleepingReanimID;
	int BlinkCountdown;
	int RecentlyEatenCountdown;
	int EatenFlashCountdown;
	int BeghouledFlashCountdown;
	float ShakeOffsetX;
	float ShakeOffsetY;
	MagnetItem MagnetItems[5];
	ZombieID TargetZombieID;
	int WakeUpCounter;
	PlantOnBungeeState OnBungeeState;
	SeedType ImitaterType;
	int PottedPlantIndex;
	bool AnimPing;
	bool Dead;
	bool Squished;
	bool IsAsleep;
	bool IsOnBoard;
	bool Highlighted;
};