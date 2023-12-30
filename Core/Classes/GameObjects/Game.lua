---@diagnostic disable: undefined-global, missing-fields
local NewField = LunaClass.NewField;
local TypeCasts = LunaClass.TypeCasts;
local Int = TypeCasts.Int;
local Float = TypeCasts.Float;
local IVec2 = TypeCasts.IVector2;
local FVec2 = TypeCasts.FVector2;
local Bool = TypeCasts.Bool;
LunaClass.Register(
    "Game",
    {
        LawnApp = NewField(0x8C, true, true, "LawnApp");
        CursorObject = NewField(0x138, true, true, "GameCursor");
        CursorPreview = NewField(0x13C, true, true, "CursorPreview");

        Advice = NewField(0x140, true, true, "UIMessage");
        SeedBank = NewField(0x144, true, true, "SeedBank");
        MenuButton = NewField(0x148, true, true, "GameButton");
        StoreButton = NewField(0x14C, true, true, "GameButton");
        IgnoreMouseUp = NewField(0x150, false, false, Bool);
        ToolTip = NewField(0x154, true, true, "UIToolTip");
        DebugFont = NewField(0x158, true, true, "Font");
        CutScene = NewField(0x15C, true, true, "CutScene");
        Challenge = NewField(0x160, true, true, "Challenge");
        Paused = NewField(0x164, false, false, Bool);

        EnableGraveStones = NewField(0x5C4, false, false, Bool);
        SpecialGrave = NewField(0x5C8, false, false, IVec2);
        SpecialGraveX = NewField(0x5C8, false, false, Int);
        SpecialGraveY = NewField(0x5CC, false, false, Int);
        FogOffset = NewField(0x5D0, false, false, Float);
        FogBlownTimer = NewField(0x5D4, false, false, Int);

        SunDropTimer = NewField(0x5538, false, false, Int);
        SunsFallen = NewField(0x553C, false, false, Int);
        ShakeTimer = NewField(0x5540, false, false, Int);
        ShakeAmount = NewField(0x5544, false, false, FVec2);
        ShakeAmountX = NewField(0x5544, false, false, Float);
        ShakeAmountY = NewField(0x5548, false, false, Float);
        Background = NewField(0x554C, false, false, Int);
        Level = NewField(0x5550, false, false, Int);
        SodPosition = NewField(0x5554, false, false, Int);
        LastMousePosition = NewField(0x5558, false, false, IVec2);
        Sun = NewField(0x5560, false, false, Int);
        SunCount = NewField(0x5560, false, false, Int);
        WaveCount = NewField(0x5564, false, false, Int);
        MainTimer = NewField(0x5568, false, false, Int);
        EffectTimer = NewField(0x556C, false, false, Int);
        DrawCount = NewField(0x5570, false, false, Int);
        
        RiseFromGraveTimer = NewField(0x5574, false, false, Int);
        OutOfMoneyNoticeTimer = NewField(0x5578, false, false, Int);
        CurrentWave = NewField(0x557C, false, false, Int);
        TotalSpawnedWaves = NewField(0x5580, false, false, Int);
        TutorialState = NewField(0x5584, false, false, Int);
        TutorialTimer = NewField(0x558C, false, false, Int);
        LastBungeeWave = NewField(0x5590, false, false, Int);
        NextWaveHPThreshold = NewField(0x5594, false, false, Int);
        MaxWaveHP = NewField(0x5598, false, false, Int);
        NextWaveTimer = NewField(0x559C, false, false, Int);
        MaxWaveTimer = NewField(0x55A0, false, false, Int);
        HugeWaveTimer = NewField(0x55A4, false, false, Int);
        AdviceIndex = NewField(0x55EC, false, false, Int);
        
        FinalBossKilled = NewField(0x55F0, false, false, Bool);
        ShowShovel = NewField(0x55F1, false, false, Bool);
        CoinBankFadeTimer = NewField(0x55F4, false, false, Int);
        DebugTextMode = NewField(0x55F8, false, false, Int);
        LevelComplete = NewField(0x55FC, false, false, Bool);
        GameFadeTimer = NewField(0x5600, false, false, Int);
        NextSurvivalStageTimer = NewField(0x5604, false, false, Int);
        ScoreNextMowerTimer = NewField(0x5608, false, false, Int);
        LevelAwardSpawned = NewField(0x560C, false, false, Int);
        ProgressMeterWidth = NewField(0x5610, false, false, Int);
        FlagsRaisedCount = NewField(0x5614, false, false, Int);
        ZombieFreezeTimer = NewField(0x5618, false, false, Int);
        RandomSeed = NewField(0x561C, false,  false, Int);
        TimeStopTimer = NewField(0x5748, false, false, Int);
        CoinsDropping = NewField(0x574C, false, false, Bool);

        FinalWaveSoundTimer = NewField(0x5750, false, false, Int);
        CobCannonCursorDelay = NewField(0x5754, false, false, Int);
        CobCannonMouse = NewField(0x5758, false, false, IVec2);
        CobCannonMouseX = NewField(0x5758, false, false, Int);
        CobCannonMouseY = NewField(0x575C, false, false, Int);
        KilledYeti = NewField(0x5760, false, false, Bool);
        MustacheMode = NewField(0x5761, false, false, Bool);
        SuperMowerMode = NewField(0x5762, false, false, Bool);
        FutureMode = NewField(0x5763, false, false, Bool);
        PinataMode = NewField(0x5764, false, false, Bool);
        DaisyMode = NewField(0x5765, false, false, Bool);
        SukhbirMode = NewField(0x5766, false, false, Bool);
        PreviousGameResult = NewField(0x5768, false, false, Int);
        TriggeredLawnMowers = NewField(0x576C, false, false, Int);
        ActivePlayTime = NewField(0x5770, false, false, Int);
        InactivePlayTime = NewField(0x5774, false, false, Int);
        MaxSunPlants = NewField(0x5778, false, false, Int);
        MaxSunProducers = NewField(0x5778, false, false, Int);
        StartDrawTime = NewField(0x577C, false, false, Int);
        IntervalDrawTime = NewField(0x5780, false, false, Int);
        IntervalDrawCountStart = NewField(0x5784, false, false, Int);
        PreloadTime = NewField(0x578C, false, false, Int);
        GameID = NewField(0x5790, false, false, Int);
        GravesCleared = NewField(0x5794, false, false, Int);
        PlantsEaten = NewField(0x5798, false, false, Int);
        PlantsShoveled = NewField(0x579C, false, false, Int);
        CoinsCollected = NewField(0x57A0, false, false, Int);
        DiamondsCollected = NewField(0x57A4, false, false, Int);
        ZenGardenPlantsCollected = NewField(0x57A8, false, false, Int);
        ChocolateCollected = NewField(0x57AC, false, false, Int);

        Exists = true;
        LawnToPixel = GAME_PXTOLN;
        PixelToLawn = GAME_LNTOPX;

        AddProjectile = GAME_PROJ_ADD;
        AddPlant = GAME_PLANT_ADD;

        Created = GAME_NEW;
        Killed = GAME_KILL;
        Update = GAME_UPDATE;
    },
    0x57B0,
    true,
    "UIElement"
);

---@type Game
Game = {Exists = false};

Game.Created = GAME_NEW;
Game.Killed = GAME_KILL;
Game.Update = GAME_UPDATE;

ENV.GAME_NEW = nil;
ENV.GAME_KILL = nil;
ENV.GAME_UPDATE = nil;
ENV.GAME_PXTOLN = nil;
ENV.GAME_LNTOPX = nil;
ENV.GAME_PROJ_ADD = nil;
ENV.GAME_PLANT_ADD = nil;

return Game;