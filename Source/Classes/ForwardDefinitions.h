#pragma once
// Structs
template <typename T>
struct Vector2;
struct Color;
struct Pad;

// Luna Class
namespace Luna::Class
{
	class LunaClass;
	class BaseLunaField;
	class BaseLunaInstance;

	template <typename T>
	class LunaField;

	template <typename T>
	class LunaInstance;

	std::map<DWORD, LunaClass*> UIVFTables = {};

	LunaClass* LunaUIContainer;
	LunaClass* LunaUIElement;
	LunaClass* LunaLawnApp;
	LunaClass* LunaUIRoot;
}
#define IVector2 Vector2<int>
#define FVector2 Vector2<float>
#define DVector2 Vector2<double>

class LawnApp;

// Game Objects
class Lawn;
class Plant;
class Zombie;
class Pickups;
class GridItem;
class LawnMower;
class Projectile;

// Screens
class ChooseYourSeeds;
class ChallengeScreen;
class CreditScreen;
class TitleScreen;
class AwardScreen;
class MainMenu;


// Systems
class SoundSystem;
class EffectSystem;

// Other
class ReanimatorCache;
class ProfileManager;
class TypingCheck;
class LevelStats;
class PoolEffect;
class ZenGarden;
class CrazyDave;
class Graphics;
class UserData;
class PopDRM;
class Music;

// Sexy
namespace Sexy
{
	class SexyAppBase;
	class SexyApp;

	class UIRoot;
	class Font;

	class UIElement;
	class UIContainer;
	class UIButton;
	class UIDialog;
	class UIDialogButton;
	class PreModalInfo;
	class ButtonListener;
	class LawnStoneButton;

	class Image;
	class MemoryImage;
	class SharedImage;

	class DDInterface;
	class MusicInterface;
	class SoundManager;
	class UISafeDeleteInfo;
	class Buffer;

	class ResourceManager;
	class InternetManager;
	class BetaSupport;
}