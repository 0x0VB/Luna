#pragma once
#include "Definitions.h"

class Projectile : public GameObject
{
public:
	int Frame;
	int NumFrames;
	int AnimCounter;
	FVector3 Position;
	FVector3 Velocity;
	float Gravvity;
	float Floor;
	bool Dead;
	int AnimTicksPerFrame;
	ProjectileMotion MotionType;
	ProjectileType Type;
	int Age;
	int ClickBackoffCounter;
	float Rotation;
	float RotationSpeed;
	bool OnHighGround;
	int DamageRangeFlags;
	int HitTorchwoodGridX;
	AttachmentID AttachmentID;
	float CobTargetX;
	int CobTargetRow;
	ZombieID TargetZombieID;
	int LastPortalX;
};