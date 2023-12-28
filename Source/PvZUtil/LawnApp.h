#pragma once
#include "Definitions.h"
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

class Sexy::SexyAppBase : public Sexy::ButtonListener, public Sexy::DialogListener
{
#pragma region Fields
public:
	unsigned long RandSeed;

	PopString CompanyName;
	PopString FullCompanyName;
	PopString ProductName;
	PopString Title;
	PopString RegisteryKey;
	PopString ChangeDirTo;
	int RelaxUpdateBacklogCount;

	IRect WindowBounds;
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
	bool HasSEHOccured;
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

	bool DoReadFromRegistry;
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
	Buffer DemoBuffer;
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
	IRect ScreenBounds;
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
#pragma endregion
#pragma region Virtual Functions
	virtual void __thiscall ButtonClick(int ID, int ClickType); // 0000
	virtual void __thiscall ButtonPress(int ID); // 0004
	virtual void __thiscall ButtonDepress(int ID);// 0008
	virtual void __thiscall ButtonDownTick(int ID);// 000C
	virtual void __thiscall ButtonMouseEnter(int ID);// 0010
	virtual void __thiscall ButtonMouseLeave(int ID);// 0014
	virtual void __thiscall ButtonMouseMove(int ID, int X, int Y);// 0018

	virtual void __thiscall DialogButtonPress(int DialogID, int ButtonID);
	virtual void __thiscall DialogButtonDepress(int DialogID, int ButtonID);

	virtual bool __thiscall Process(bool AllowSleep);// 001C
	virtual void __thiscall UpdateFrames();// 0020
	virtual bool __thiscall DoUpdateFrames();// 0024
	virtual void __thiscall DoUpdateFramesF(float Fraction);// 0028
	virtual void __thiscall MakeWindow();// 002C
	virtual void __thiscall EnforceCursor();// 0030
	virtual void __thiscall ReInitImages();// 0034
	virtual void __thiscall DeleteNativeImageData();// 0038
	virtual void __thiscall DeleteExtraImageData();// 003C
	virtual void __thiscall CheckUpdates();// 0040
	virtual ~SexyAppBase();// 0044
	virtual Sexy::MusicInterface* CreateMusicInterface(HWND Window);// 0048
	virtual void __thiscall InitHook();// 004C
	virtual void __thiscall D3DT2();// 0050
	virtual void __thiscall D3DT3();// 0054
	virtual void __thiscall LoadingThreadProc();// 0058
	virtual void __thiscall WriteToRegistery();// 005C
	virtual void __thiscall ReadFromRegistry();// 0060
	virtual UIDialog* __thiscall NewDialog(int ID, bool IsModal, const PopString& Header, const PopString& Content, const PopString& Footer, int ButtonLayout);// 0064
	virtual void __thiscall PreDisplayHook();// 0068
	virtual void __thiscall BeginPopup();// 006C
	virtual void __thiscall EndPopup();// 0070
	virtual void __thiscall WMsgBox(const PopWString& Text, const PopWString& Title, int Flags);// 0074
	virtual void __thiscall MsgBox(const PopString& Text, const PopString& Title, int Flags);// 0078
	virtual void __thiscall WPopup(const PopWString& Text);// 007C
	virtual void __thiscall Popup(const PopString& Text);// 0080
	virtual void __thiscall LogScreenSaverError(const PopString& Error);// 0084
	virtual void __thiscall SafeDeleteElement(UIElement* Element);// 0088
	virtual void __thiscall URLOpenFailed(const PopString& URL);// 008C
	virtual void __thiscall URLOpenSucceeded(const PopString& URL);// 0090
	virtual void __thiscall OpenURL(const PopString& URL, bool ShutdownAfter);// 0094
	virtual void __thiscall GetProductVersion(_Out_ PopString&& Out, const PopString& Path);// 0098
	virtual void __thiscall SEHOccured();// 009C
	virtual void __thiscall GetGameSEHInfo(_Out_ PopString&& Out);// 00A0
	virtual void __thiscall KeyUp(unsigned int KeyCode);// 00A4
	virtual void __thiscall ShutDown();// 00A8
	virtual void __thiscall DoParseCmdLine();// 00AC
	virtual void __thiscall ParseCmdLine(const PopString& Cmd);// 00B0
	virtual void __thiscall HandleCmdLineParam(const PopString& ParamName, const PopString& ParamValue);// 00B4
	virtual void __thiscall HandleNotifyGameMessage(int Type, int Param);// 00B8
	virtual void __thiscall HandleGameAlreadyRunning();// 00BC
	virtual void __thiscall Start();// 00C0
	virtual void __thiscall Init();// 00C4
	virtual void __thiscall D3DT6();// 00C8
	virtual void __thiscall D3DT7();// 00CC
	virtual void __thiscall ChangeDirHook(const char* Path);// 00D0
	virtual void __thiscall PlaySample(int SoundNum, int Pan);// 00D4
	virtual void __thiscall PlaySample(int SoundNum);// 00D8
	virtual double __thiscall GetMasterVolume();// 00DC
	virtual double __thiscall GetMusicVolume();// 00E0
	virtual double __thiscall GetSfxVolume();// 00E4
	virtual bool __thiscall IsMuted();// 00E8
	virtual void __thiscall SetMasterVolume(double Volume);// 00EC
	virtual void __thiscall SetMusicVolume(double Volume);// 00F0
	virtual void __thiscall SetSfxVolume(double Volume);// 00F4
	virtual void __thiscall Mute(bool AutoMute);// 00F8
	virtual void __thiscall Unmute(bool AutoMute);// 00FC
	virtual double GetLoadingThreadProgress();// 0100
	virtual DDImage* GetImage(const PopString& FileName, bool CommitBits);// 0104
	virtual SharedImageRef** __thiscall SetSharedImage(_Out_ SharedImageRef** Out, const PopString& FileName, const PopString& Variant, DDImage* Image, bool* IsNew);// 0108
	virtual SharedImage** __thiscall GetSharedImage(_Out_ SharedImageRef** Out, const PopString& FileName, const PopString& Variant, bool* IsNew);// 010C
	virtual void __thiscall SwitchScreenMode(bool WantWindowed, bool Is3D, bool Force);// 0110
	virtual void __thiscall SwitchScreenMode(bool WantWindowed);// 0114
	virtual void __thiscall SwitchScreenMode();// 0118
	virtual void __thiscall SetAlphaDisabled(bool Disabled);// 011C
	virtual UIDialog* __thiscall DoDialog(int DialogID, bool Modal, const PopString& Header, const PopString& Content, const PopString& Footer, int ButtonLayout);// 0120
	virtual UIDialog* __thiscall GetDialog(int DialogID);// 0124
	virtual void __thiscall AddDialog(UIDialog* ToAdd);// 0128
	virtual void __thiscall AddDialog(int DialogID, UIDialog* Dialog);// 012C
	virtual bool __thiscall KillDialog(UIDialog* Dialog);// 130
	virtual bool __thiscall KillDialog(int DialogID);// 134
	virtual bool __thiscall KillDialog(int DialogID, bool RemoveElement, bool DeleteElement);// 138
	virtual int __thiscall GetDialogCount();// 13C
	virtual void __thiscall D3DT8();// 0140
	virtual void __thiscall D3DT9();// 0144
	virtual void __thiscall D3DTA();// 0148
	virtual void __thiscall D3DTB();// 014C
	virtual void __thiscall IsAltKeyUsed(WPARAM Param);// 0150
	virtual bool __thiscall DebugKeyDown(unsigned int Key);// 0154
	virtual bool __thiscall DebugKeyDownAsync(unsigned int Key, bool CtrlDown, bool AltDown);// 0158
	virtual void __thiscall D3DTC();// 015C
	virtual void __thiscall D3DTD();// 0160
	virtual PopString&& __thiscall NotifyCrashHook(_Out_ PopString&& UploadFile);// 0164
	virtual bool __thiscall CheckSignature(const Buffer& Buffer, const PopString& FileName);// 0168
	virtual bool __thiscall DrawDirtyStuff();// 016C
	virtual void __thiscall Redraw(IRect* ClipRect = NULL);// 0170
	virtual void __thiscall D3DTE();// 0174
	virtual void __thiscall DoMainLoop();// 0178
	virtual bool __thiscall UpdateAppStep(bool* Updated);// 017C
	virtual void __thiscall UpdateApp();// 0180
	virtual bool __thiscall AppCanRestore();// 0184
	virtual bool __thiscall Unk();// 0188
#pragma endregion
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
#pragma region Fields
public:
	Lawn* Lawn;
	LoadingScreen* LoadingScreen;
	MainMenu* MainMenu;
	SeedChooser* SeedChooser;
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
#pragma endregion
#pragma region Virtual Functions

#pragma endregion
	static LawnApp* GetApp() { return *(LawnApp**)0x6A9EC0; }
};