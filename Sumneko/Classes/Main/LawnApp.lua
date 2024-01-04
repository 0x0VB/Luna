local NewField = LunaClass.NewField;
local TypeCasts = LunaClass.TypeCasts;
local Int = TypeCasts.Int;
local Long = TypeCasts.Long;
local Double = TypeCasts.Double;
local Bool = TypeCasts.Bool;
local String = TypeCasts.String;
local Rect = TypeCasts.RVector4;
local Vec2 = TypeCasts.IVector2;
local UI = TypeCasts.UI;
local Reanimation = TypeCasts.Reanimation;

local Game = NewField(0x768, true, true, "Game");
return LunaClass.Register(
    "LawnApp",
    {
        RandomSeed = NewField(0x8, false, false, Long);
        CompanyName = NewField(0x10, false, false, String);
        FullCompanyName = NewField(0x2C, false, false, String);
        ProductName = NewField(0x48, false, false, String);
        WindowTitle = NewField(0x64, false, false, String);
        RegisteryKey = NewField(0x80, false, false, String);
        GameDirectory = NewField(0x9C, false, false, String);
        WindowBounds = NewField(0xB8, false, false, Rect);
        WindowPosition = NewField(0xB8, false, false, Rect);
        WindowSize = NewField(0xC0, false, false, Vec2);

        MusicVolume = NewField(0xD0, false, false, Double);
        SFXVolume = NewField(0xD8, false, false, Double);
        AllowOnlyOneProcess = NewField(0xFC, false, false, Bool);
        IsBeta = NewField(0x11C, false, false, Bool);
        UIRoot = NewField(0x320, true, true, "UIRoot");
        Shutdown = NewField(0x341, false, false, Bool);
        ExitToMainMenu = NewField(0x342, false, false, Bool);
        IsWindowed = NewField(0x343, false, false, Bool);
        IsFullScreen = NewField(0x345, false, false, Bool);
        Initialized = NewField(0x348, false, false, Bool);
        TimeLoaded = NewField(0x34C, false, false, Long);
        InputDisabled = NewField(0x368, false, false, Bool);
        TabletPC = NewField(0x36A, false, false, Bool);

        ProductVersion = NewField(0x39C, false, false, String);
        CursorIcon = NewField(0x4B0, false, true, "Cursor");
        MuteOnFocusLost = NewField(0x431, false, false,Bool);
        FrameDelta = NewField(0x545, false, false, Int);
        IsDrawing = NewField(0x458, false, false, Bool);
        LastInputTime = NewField(0x478, false, false, Long);
        DrawCount = NewField(0x480, false, false, Int);
        UpdateCount = NewField(0x484, false, false, Int);
        Speed = NewField(0x490, false, false, Double);
        Paused = NewField(0x498, false, false, Bool);
        LastDrawTime = NewField(0x4A4, false, false, Long);
        SystemCursor = NewField(0x4B0, false, false, Int);
        MouseInWindow = NewField(0x4CC, false, false, Bool);
        Active = NewField(0x4CE, false, false, Bool);
        Minimized = NewField(0x4CF, false, false, Bool);
        HasFocus = NewField(0x4D2, false, false, Bool);
        Loaded = NewField(0x4FB, false, false, Bool);
        SystemCursorVisible = NewField(0x4FF, false, false, Bool);
        DebugKeysEnabled = NewField(0x5AC, false, false, Bool);
        EnableMaximizeButton = NewField(0x5AD, false, false, Bool);
        
        CtrlDown = NewField(0x5AE, false, false, Bool);
        AltDown = NewField(0x5AF, false, false, Bool);
        ResourceManager = NewField(0x634, true, true, "ResourceManager");
        BuildNumber = NewField(0x6E0, false, false, Int);
        BuildDate = NewField(0x6E8, false, false, String);

        Game = Game;
        Level = Game;
        Board = Game;
        TitleScreen = NewField(0x76C, true, false, UI);
        MainMenu = NewField(0x770, true, false, UI);
        ChooseYourSeeds = NewField(0x774, true, false, UI);
        AwardScreen = NewField(0x778, true, false, UI);
        CreditScreen = NewField(0x77C, true, false, UI);
        ChallengeScreen = NewField(0x780, true, false, UI);
        SoundSystem = NewField(0x784, true, true, "SoundSystem");
        Mod = NewField(0x7DC, false, false, String);
        CheatKeys = NewField(0x7F5, false, false, Bool);

        GameMode = NewField(0x7F8, false, false, Int);
        GameScene = NewField(0x7FC ,false, false, Int);
        NewUser = NewField(0x801, false, false, Bool);
        GamesPlayed = NewField(0x804, false, false, Int);
        MaxExecutions = NewField(0x808, false, false, Int);
        MaxTime = NewField(0x810, false, false, Int);
        EasyPlantingCheat = NewField(0x814, false, false, Bool);

        PoolEffect = NewField(0x818, true, true, "PoolEffect");
        ZenGarden = NewField(0x81C, true, true, "ZenGarden");
        EffectSystem = NewField(0x820, true, true, "EffectSystem");
        ProfileManager = NewField(0x828, true, true, "ProfileManager");
        UserData = NewField(0x82C, true, true, "UserData");
        LevelStats = NewField(0x830, true, true, "LevelStats");
        ShutdownRequest = NewField(0x834, false, false, Bool);
        AppCounter = NewField(0x838, false, false, Int);
        Music = NewField(0x83C, true, true, "Music");

        CrazyDaveAnimation = NewField(0x840, false, false, Reanimation);
        CrazyDaveState = NewField(0x844, false, false, Int);
        CrazyDaveBlinkTimer = NewField(0x848, false, false, Int);
        CrazyDaveBlinkAnimation = NewField(0x84C, false, false, Reanimation);
        CrazyDaveMessageIndex = NewField(0x850, false, false, Int);
        CrazyDaveMessage = NewField(0x858, false, false, String);

        SessionID = NewField(0x87C, false, false, Int);
        GameResult = NewField(0x888, false, false, Int);

        MustacheMode = NewField(0x8B4, false, false, Bool);
        SuperMowerMode = NewField(0x8B5, false, false, Bool);
        FutureMode = NewField(0x8B6, false, false, Bool);
        PinataMode = NewField(0x8B7, false, false, Bool);
        DaisyMode = NewField(0x8B8, false, false, Bool);
        SukhbirMode = NewField(0x8B9, false, false, Bool);

        Created = LawnApp.Created;
        OnLoaded = LawnApp.OnLoaded;
        Updating = LawnApp.Updating;
    },
    0x8C0,
    true
);