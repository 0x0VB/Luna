---@meta
---@class LawnApp : LunaClass
---@field Seed integer The game's random seed.
---@field WindowTitle string The title of the game window.
---@field RegisteryKey string The registery key the game uses to store registery values.
---@field WindowBounds Rect The position and size of the window.
---@field MusicVolume number The music volume.
---@field SFXVolume number The sound effects volume.
---@field IsBeta boolean Whether the game is a beta build or not.
---@field IsWindowed boolean [READ-ONLY] Whether the game is windowed or fullscreen.
---@field Initialized boolean Whether the game has been initialized or not.
---@field TimeLoaded number How much time has passed since the game finished loading.
---@field InputDisabled boolean Disabled all user input when set to `true`.
---@field TabletPC boolean `true` when the current device is a TabletPC.
---@field FrameTime integer How many milliseconds to wait between frames. This value is divided by `LawnApp.Speed`.
---@field IsDrawing boolean `true` when the game is currently drawing graphics.
---@field DrawCount integer How many times the game has drawn frames.
---@field UpdateCount integer How many times the game has updated thus far.
---@field UpdateState integer The current update state.
---@field UpdateDepth integer The depth of the current update.
---@field Speed number The speed of the game. 1 by default.
---@field AppPaused boolean Pauses the *entire app* when true. Changing this is not recommended as it stops the entire app, not just the game.
---@field MouseIn boolean `true` when the mouse is on the game window.
---@field Active boolean `true` when the game window is active.
---@field Minimized boolean `true` when the game window is minimized.
---@field HasFocus boolean `true` when the game window is the focused window.
---@field Loaded boolean `true` once the game finishes loading. All fonts are loaded by this point.
---@field CtrlDown boolean `true` if the control button is held down.
---@field AltDown boolean `true` if the alt button is held down.
---@field AllowAltEnter boolean Whether to allow the user to type new lines using the Alt+Enter combo.
---@field ZombiesLoaded boolean `true` after the zombies finish loading.
---@field NewUser boolean `true` when the user is playing the game for the first time and is inputting a name.
---@field GamePlayed integer How many games the user played.
---@field EasyPlantingCheat boolean Makes all plants free and have no recharge when set to `true`.
---@field CloseRequest boolean `true` when the user requests a close.
---@field Age integer How many frames the game has been alive for.
---@field MustacheMode boolean Gives zombies mustaches.
---@field SuperMowerMode boolean Changes the appearance of lawn mowers to make them look cooler.
---@field FutureMode boolean Gives the zombies cool futuristic glasses.
---@field PinataMode boolean Makes a candy explosion whenever zombies die.
---@field DaisyMode boolean Makes diasies in the place of zombies' death.
---@field SukhbirMode boolean Makes the zombies groan turn into a "Suck their brains".
---@field DanceMode boolean Makes the zombies dance!
LawnApp = {};

---Creates a Windows MessageBox.
---@param Message string
---@param Title string?
function LawnApp:MessageBox(Message, Title) end;

---@type LunaEvent
LawnApp.OnUpdate = {};

---@type LunaEvent
LawnApp.OnLoad = {};

---Connects the given function to this event. This event is fired each frame before the LawnApp updates.
---@param Function fun()
function LawnApp.OnUpdate:Connect(Function) end;

---Connects the given function to this event. This event is fired once the game finishes loading initial resources.
---@param Function fun()
function LawnApp.OnLoad:Connect(Function) end;