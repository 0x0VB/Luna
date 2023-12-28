#pragma once
enum ReanimationID;
enum CrazyDaveState;
class CrazyDave
{
	ReanimationID AnimationID;
	CrazyDaveState State;
	int BlinkCounter;
	ReanimationID BlinkAnimationID;
	int MessageIndex;
	PopString Message;
};
class Sexy::SexyAppBase
{
public:
	DWORD** VTable;
	void* Pad_04;
	unsigned long RandSeed;

	PopString CompanyName;
	PopString FullCompanyName;
	PopString ProductName;
	PopString Title;
	PopString RegisteryKey;
	PopString ChangeDirTo;
	int RelaxUpdateBacklogCount;

	Rect WindowBounds;
	int FullScreenBits;
	int Pad_CC;
	double MusicVolume;
	double SFXVolume;
	double DemoMusicVolume;
	double DemoSFXVolume;
	bool NoSoundNeeded;
	bool WantFMod;
	bool CmdLineParsed;
	bool SkipSignatureChecks;
	bool StandardWordWrap;
	bool AllowExtendedChars;

	void* Mutex;
	bool OnlyOneProcess;
	unsigned int NotifyGameMessage;
	_RTL_CRITICAL_SECTION CriticalSection;
	bool IsBeta;
	unsigned char Add8BitMaxTable[512];

	Sexy::UIRoot* UIRoot;
	PopMap<int, Sexy::UIDialog*> DialogMap;
	PopList<Sexy::UIDialog*> DialogList;
	unsigned long PrimaryThreadID;
	bool SEHOccured;
	bool Shutdown;
	bool ExitToMainMenu;
	bool IsWindowed;
	bool IsPhysWindowed;
	bool FullScreenWindow;
	bool ForceFullScreen;
	bool ForceWindowed;
	bool Initialized;
	bool ProcessInTimer;

	unsigned long TimeLoaded;
	HWND MainWindowHandle;
	HWND InvisWindowHandle;
	bool IsScreenSaver;
	bool AllowMonitorPowerSave;
	PopList<tagMSG> DeferredMessages;
	bool InputDisabled;
	bool FullScreenPageFlip;
	bool TabletPC;

	Sexy::DDInterface* DDInterface;
	bool AlphaDisabled;
	Sexy::MusicInterface* MusicInterface;

	bool ReadFromRegistry;
	PopString RegisterLink;
	PopString ProductVersion;

	BYTE CursorImages[52];
	HICON OverrideCursor;
	bool IsOpeningURL;
	bool ShutdownOnURLOpen;
	PopString OpeningURL;
	unsigned long OpeningURLTimer;
	unsigned long LastTimerTime;
	unsigned long LastBigDelayTime;
	double UnmutedMusicVolume;
	double UnmutedSFXVolume;
	int MuteCount;
	int AutoMuteCount;
	bool DemoMute;
	bool MuteOnLostFocus;

	PopSet<Sexy::MemoryImage*> MemoryImages;
	PopMap<PopPair<PopString, PopString>, Sexy::SharedImage> SharedImages;
	bool CleanupSharedImages;

	int NonDrawCount;
	int FrameDelta;
	bool IsDrawing;
	bool LastDrawWasEmpty;
	bool DrawPending;
	int Pad_045C;

	double PendingUpdatesAcc;
	double UpdateFTimeAcc;
	unsigned long LastTimeCheck;
	unsigned long LastTime;
	unsigned long LastUserInputTick;
	int SleepCount;
	int DrawCount;
	int UpdateCount;
	int UpdateAppState;
	int UpdateAppDepth;
	double Speed;
	bool Paused;
	int FastForwardToUpdateNum;
	bool FastForwardToMarker;
	bool FastForwardStep;

	unsigned long LastDrawTick;
	unsigned long NextDrawTick;
	int StepMode;
	int CursorNum;
	Sexy::SoundManager* SoundManager;
	HICON HandCursor;
	HICON DraggingCursor;
	PopList<Sexy::UISafeDeleteInfo> SafeDeleteList;
	bool MouseIn;
	bool Running;
	bool Active;
	bool Minimized;
	bool PhysMinimized;
	bool IsDisabled;
	bool HasFocus;

	int DrawTime;
	unsigned long FPSStartTick;
	int FPSFlipCount;
	int FPSDirtyCount;
	int FPSTime;
	int FPSCount;
	bool ShowFPS;
	int ShowFPSMode;
	int ScreenBitTime;

	bool AutoStartLoadingThread;
	bool LoadingThreadStarted;
	bool LoadingThreadComplete;
	bool Loaded;
	bool YieldMainThread;
	bool LoadingFailed;
	bool CursorThreadRunning;
	bool SysCursor;
	bool CustomCursorsEnabled;
	bool CustomCursorDirty;
	bool LastShutdownWasGraceful;
	bool IsWideWindow;
	bool WriteToSexyCache;
	bool SexyCacheBuffers;
	int NumLoadingThreadTasks;
	int CompletedLoadingThreadTasks;
	bool RecordingDemoBuffer;
	bool PlayingDemoBuffer;
	bool ManualShutdown;

	PopString DemoPrefix;
	PopString DemoFileName;
	Sexy::Buffer DemoBuffer;
	int DemoLength;
	Vector2<int> LastDemoMousePosition;
	int LastDemoUpdateCnt;
	bool DemoNeedsCommand;
	bool DemoIsShortCmd;
	int DemoCmdNum;
	int DemoCmdOrder;
	int DemoCmdBitPos;
	bool DemoLoadingComplete;

	PopMap<void*, int> HandleToIntMap;
	int CursorHandleNum;
	PopList<PopString> DemoMarkerList;
	bool DebugKeysEnabled;
	bool EnableMaximizeButton;
	bool CtrlDown;
	bool AltDown;
	bool AllowAltEnter;

	int SyncRefreshRate;
	bool VSyncUpdates;
	bool VSyncBroken;
	int VSyncBreakCount;
	unsigned long VSyncBrokenTestStartTick;
	unsigned long VSyncBrokentestUpdates;
	bool WaitForVSync;
	bool SoftVSyncWait;
	bool UserChanged3DSetting;

	bool AutoEnable3D;
	bool Test3D;
	unsigned long MinVidMemory3D;
	unsigned long RecommendedVidMem3D;
	bool WidescreenAware;
	bool WidescreenTranslate;
	Rect ScreenBounds;
	bool EnableWindowAspect;

	Ratio WindowAspect;
	PopMap<PopString, PopString> StringProperties;
	PopMap<PopString, PopString> BoolProperties;
	PopMap<PopString, PopString> IntProperties;
	PopMap<PopString, PopString> DoubleProperties;
	PopMap<PopString, PopString> StringVectorProperties;

	Sexy::ResourceManager* ResourceManager;
	unsigned long OldWndProc;
	size_t SexyAppBaseSize = sizeof(SexyAppBase);
};
class Sexy::SexyApp : public SexyAppBase
{
public:
	Sexy::InternetManager* InternetManager;
	Sexy::BetaSupport* BetaSupport;
	PopString BetaSupportSiteOverride;
	PopString BetaSupportProdNameOverride;
	PopString ReferID;
	PopString Variation;
	unsigned long DownloadID;
	PopString RegSource;
	unsigned long LastVerCheckQueryTime;
	bool SkipAd;
	bool DontUpdate;

	int BuildNum;
	PopString BuildDate;
	PopString UserName;
	PopString RegUserName;
	PopString RegCode;
	bool IsRegistered;
	bool BuildUnlocked;

	int TimesPlayed;
	int TimesExecuted;
	bool TimedOut;

	size_t SexyAppSize = sizeof(SexyApp);
};
class LawnApp : public Sexy::SexyApp
{
public:
	Lawn* Lawn;
	TitleScreen* TitleScreen;
	MainMenu* MainMenu;
	ChooseYourSeeds* ChooseYourSeeds;
	AwardScreen* AwardScreen;
	CreditScreen* CreditScreen;
	ChallengeScreen* ChallengeScreen;
	SoundSystem* SoundSystem;

	PopList<Sexy::UIButton> ControlButtonList;
	PopList<Sexy::Image> CreatedImageList;
	PopString ReferID;
	PopString RegisterLink;
	PopString Mod;
	bool RegisterResourcesLoaded;
	bool CheatKeys;

	GameMode GameMode;
	GameScene GameScene;
	bool LoadingZombiesThreadCompleted;
	bool IsNewUser;
	int GamesPlayed;
	int MaxExecutions;
	int MaxPlays;
	int MaxTime;
	bool EasyPlantingCheat;

	PoolEffect* PoolEffect;
	ZenGarden* ZenGarden;
	EffectSystem* EffectSystem;
	ReanimatorCache* ReanimatorCache;
	ProfileManager* ProfileManager;
	UserData* UserData;
	LevelStats* LastLevelStats;
	bool CloseRequest;

	int AppCounter;
	Music* Music;
	CrazyDave CrazyDave;

	int RandAppSeed;
	HICON BigArrowCursor;
	PopDRM* DRM;
	int SessionID;
	int PlaytimeActiveSession;
	int PlaytimeInactiveSession;
	GameResult GameResult;
	bool KilledYetiAndRestarted;

	TypingCheck* KonamiCheck;
	TypingCheck* MustacheCheck;
	TypingCheck* MoustacheCheck;
	TypingCheck* SuperMowerCheck;
	TypingCheck* SuperMowerCheck2;
	TypingCheck* FutureCheck;
	TypingCheck* PinataCheck;
	TypingCheck* DaisyCheck;
	TypingCheck* SukhbirCheck;

	bool MustacheMode;
	bool SuperMowerMode;
	bool FutureMode;
	bool PinataMode;
	bool DaisyMode;
	bool SukhbirMode;

	size_t LawnAppSize = sizeof(LawnApp);
};