#pragma once
#include "Definitions.h"

#pragma region Enums
enum ZombieType
{
	ZOMBIE_INVALID = 0xFFFFFFFF,
	ZOMBIE_NORMAL = 0x0,
	ZOMBIE_FLAG = 0x1,
	ZOMBIE_CONEHEAD = 0x2,
	ZOMBIE_POLEVAULTER = 0x3,
	ZOMBIE_BUCKETHEAD = 0x4,
	ZOMBIE_NEWSPAPER = 0x5,
	ZOMBIE_DOOR = 0x6,
	ZOMBIE_FOOTBALL = 0x7,
	ZOMBIE_DANCER = 0x8,
	ZOMBIE_BACKUP_DANCER = 0x9,
	ZOMBIE_DUCKY_TUBE = 0xA,
	ZOMBIE_SNORKEL = 0xB,
	ZOMBIE_ZOMBONI = 0xC,
	ZOMBIE_BOBSLED = 0xD,
	ZOMBIE_DOLPHIN_RIDER = 0xE,
	ZOMBIE_JACK_IN_THE_BOX = 0xF,
	ZOMBIE_BALLOON = 0x10,
	ZOMBIE_DIGGER = 0x11,
	ZOMBIE_POGO = 0x12,
	ZOMBIE_YETI = 0x13,
	ZOMBIE_BUNGEE = 0x14,
	ZOMBIE_LADDER = 0x15,
	ZOMBIE_CATAPULT = 0x16,
	ZOMBIE_GARGANTUAR = 0x17,
	ZOMBIE_IMP = 0x18,
	ZOMBIE_BOSS = 0x19,
	ZOMBIE_PEA_HEAD = 0x1A,
	ZOMBIE_WALLNUT_HEAD = 0x1B,
	ZOMBIE_JALAPENO_HEAD = 0x1C,
	ZOMBIE_GATLING_HEAD = 0x1D,
	ZOMBIE_SQUASH_HEAD = 0x1E,
	ZOMBIE_TALLNUT_HEAD = 0x1F,
	ZOMBIE_GIGA_GARGANTUAR = 0x20,
	NUM_ZOMBIE_TYPES = 0x21
};
#pragma endregion

class Zombie : public GameObject
{
public:
#pragma region Fields
	ZombieType Type;
	ZombiePhase Phase;
	FVector2 Position;
	float Speed;
	int AnimCounter;
	int GroanCounter;
	int AnimTicksPerFrame;
	int AnimFrames;
	int Frame;
	int PrevFrame;
	bool Variant;
	bool IsEating;
	int JustGotShotCounter;
	int ShieldJustGotShotCounter;
	int ShieldRecoilCounter;
	int ZombieAge;
	ZombieHeight Height;
	int PhaseCounter;
	int FromWave;
	bool DroppedLoot;
	int FadeTimer;
	bool FlatTires;
	int UseLadderCol;
	int TargetCol;
	float Altitude;
	bool HitUmbrella;
	IRect ZombieRect;
	IRect ZombieAttackRect;
	int ChilledCounter;
	int ButteredCounter;
	int IceTrapCounter;
	bool MindControlled;
	bool BlowingAway;
	bool HasHead;
	bool HasArm;
	bool HasObject;
	bool InPool;
	bool OnHighGround;
	bool YuckyFace;
	int YuckyFaceCounter;
	HelmType HelmType;
	int BodyHealth;
	int BodyMaxHealth;
	int HelmHealth;
	int HelmMaxHealth;
	ShieldType ShieldType;
	int ShieldHealth;
	int ShieldMaxHealth;
	int FlyingHealth;
	int FlyingMaxHealth;
	bool Dead;
	ZombieID RelatedZombieID;
	ZombieID FollowerZombieID[4];
	bool PlayingSong;
	int ParticleOffsetX;
	int ParticleOffsetY;
	AttachmentID AttachmentID;
	int SummonCounter;
	ReanimationID BodyReanimID;
	float ScaleZombie;
	float VelZ;
	float OrginalAnimRate;
	PlantID TargetPlantID;
	int BossMode;
	int TargetRow;
	int BossBungeeCounter;
	int BossStompCounter;
	int BossHeadCounter;
	ReanimationID BossFireBallReanimID;
	ReanimationID SpecialHeadReanimID;
	int FireballRow;
	bool IsFireBall;
	ReanimationID MoweredReanimID;
	int LastPortalX;
#pragma endregion

	void __thiscall DieNoLoot();
	void __thiscall DieWithLoot();
	void __thiscall Rise(int Col, int Row);
	void __thiscall Update();
};