#pragma once

#include "Definitions.h"

#include "ButtonListener.h"
#include "UIElement.h"
#include "Zombie.h"
#include "Plant.h"
#include "Pickup.h"
#include "LawnMower.h"
#include "GridItem.h"
#include "DataArray.h"
#include "Projectile.h"


class Lawn : public Sexy::UIElement, Sexy::ButtonListener
{
#pragma region Fields
public:
	LawnApp* App;
	DataArray<Zombie> Zombies;
	DataArray<Plant> Plants;
	DataArray<Projectile> Projectiles;
	DataArray<Pickup> Pickups;
	DataArray<LawnMower> LawnMowers;
	DataArray<GridItem> GridItems;

	CursorObject* CursorObject;
	CursorPreview* CursorPreview;
	MessageWidget* Advice;
	SeedBank* SeedBank;
	GameButton* MenuButton;
	GameButton* StoreButton;
	bool IgnoreMouseUp;
	ToolTipWidget* ToolTip;
	Sexy::Font* DebugFont;
	CutScene* CutScene;
	Challenge* Challenge;
	bool Paused;
	GridSquareType GridSquareType[9][6];
	int GridCelLook[9][6];
	int GridCelOffset[9][6][2];
	int GridCelFog[9][7];
	bool EnableGraveStones;
	int SpecialGraveStoneX;
	int SpecialGraveStoneY;
	float FogOffset;
	int FogBlownCountDown;
	PlantRowType PlantRow[6];
	int WaveRowGotLawnMowered[6];
	int BonusLawnMowersRemaining;
	int IceMinX[6];
	int IceTimer[6];
	ParticleSystemID IceParticleID[6];
	SmoothArray RowPickingArray[6];
	ZombieType ZombiesInWave[100][50];
	bool ZombieAllowed[100];
	int SunCountDown;
	int NumSunsFallen;
	int ShakeCounter;
	int ShakeAmountX;
	int ShakeAmountY;
	BackgroundType Background;
	int Level;
	int SodPosition;
	int PrevMouseX;
	int PrevMouseY;
	int SunMoney;
	int NumWaves;
	int MainCounter;
	int EffectCounter;
	int DrawCount;
	int RiseFromGraveCounter;
	int OutOfMoneyCounter;
	int CurrentWave;
	int TotalSpawnedWaves;
	TutorialState TutorialState;
	ParticleSystemID TutorialParticleID;
	int TutorialTimer;
	int LastBungeeWave;
	int ZombieHealthToNextWave;
	int ZombieHealthWaveStart;
	int ZombieCountDown;
	int ZombieCountDownStart;
	int HugeWaveCountDown;
	bool HelpDisplayed[65];
	AdviceType HelpIndex;
	bool FinalBossKilled;
	bool ShowShovel;
	int CoinBankFadeCount;
	DebugTextMode DebugTextMode;
	bool LevelComplete;
	int BoardFadeOutCounter;
	int NextSurvivalStageCounter;
	int ScoreNextMowerCounter;
	bool LevelAwardSpawned;
	int ProgressMeterWidth;
	int FlagRaiseCounter;
	int IceTrapCounter;
	int BoardRandSeed;
	ParticleSystemID PoolSparklyParticleID;
	ReanimationID FwooshID[6][12];
	int FwooshCountDown;
	int TimeStopCounter;
	bool DroppedFirstCoin;
	int FinalWaveSoundCounter;
	int CobCannonCursorDelayCounter;
	int CobCannonMouseX;
	int CobCannonMouseY;

	bool KilledYeti;
	bool MustacheMode;
	bool SuperMowerMode;
	bool FutureMode;
	bool PinataMode;
	bool DaisyMode;
	bool SukhbirMode;
	BoardResult PrevBoardResult;
	int TriggeredLawnMowers;
	int PlayTimeActiveLevel;
	int PlayTimeInactiveLevel;
	int MaxSunPlants;
	int StartDrawTime;
	int IntervalDrawTime;
	int IntervalDrawCountStart;
	float MinFPS;
	int PreloadTime;
	int GameID;
	int GravesCleared;
	int PlantsEaten;
	int PlantsShoveled;
	int CoinsCollected;
	int DiamondsCollected;
	int PottedPlantsCollected;
	int ChocolateCollected;
#pragma endregion
	
#pragma region Functions
	GridItem* AddLadder(int Column, int Lane);
	GridItem* AddCrater(int Column, int Lane, bool KillPlants = false);
	GridItem* AddGrave(int Column, int Lane, bool DoEffects = false, bool KillPlants = false);
	GridItem* AddPortal(int Column, int Lane, bool Square = false);
	GridItem* AddBrain(int X, int Y, bool Zombaquarium = false);

	Pickup* AddPickup(int X, int Y, PickupType Type, PickupMotion Motion, SeedType PacketType = SEED_NONE);
	Plant* AddPlant(SeedType Type, int Column, int Lane, SeedType ImitaterType = SEED_NONE, bool DoPlantEffect = true);
	Zombie* __thiscall AddZombie(ZombieType Type, int Lane, int FromWave = -1);

	void KillPlantCell(int Column, int Lane);
	void KillPlantLane(int Lane);
	void KillPlantCol(int Col);
#pragma endregion
};