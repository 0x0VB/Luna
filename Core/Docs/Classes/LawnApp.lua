---@meta

--#region Events
---@class LawnAppCreated: LunaEvent
local LawnAppCreatedEvent = {};

---Fired when the LawnApp is created.
---@param Function fun(App: LawnApp)
function LawnAppCreatedEvent:Connect(Function) end;


---@class LawnAppLoaded: LunaEvent
local LawnAppLoadedEvent = {};

--[[
    Fired when the LawnApp loads all resources necessary to start. All fonts are loaded by this time.
    <br><br>If the connected function returns `false`, then `LawnApp.Loaded` will not be set to true.
    This event will keep getting fired until `LawnApp.Loaded` becomes `true`.
]]
---@param Function fun(): boolean
function LawnAppLoadedEvent:Connect(Function) end;


---@class LawnAppUpdate: LunaEvent
local LawnAppUpdateEvent = {};

---Fired when the LawnApp is updating.
---@param Function fun(Count: integer, UpdateState: integer)
function LawnAppUpdateEvent:Connect(Function) end;
--#endregion

---@class LawnApp: LunaClass, table
--#region Fields
---@field RandomSeed number
---@field CompanyName string
---@field FullCompanyName string
---@field ProductName string
---@field WindowTitle string The window's title. If you want to change this, do so in the Events.LawnAppCreated event.
---@field RegisteryKey string
---@field GameDirectory string The directory where the .exe file is.
---@field WindowBounds Rect The window rectangle. If you want to change this, do so in the Events.LawnAppCreated event.
---@field WindowPosition Vector2
---@field WindowSize Vector2
---@field MusicVolume number The in-game music volume.
---@field SFXVolume number The in-game SFX volume.
---@field AllowOnlyOneProcess boolean Allows only one PvZ to run at a time when set to true.
---@field IsBeta boolean Displays the beta distribution warning text when set to true.
---@field UIRoot UIRoot Handles input and UI elements.
---@field Shutdown boolean Closes the game when set to `true`.
---@field IsWindowed boolean Whether the game is windowed or not. This field is read-only.
---@field IsFullScreen boolean Whether the game is fullscreen or not. This field is read-only.
---@field Initialized boolean Whether LawnApp has been initialized or not.
---@field TimeLoaded number How long it has been since the game loaded.
---@field InputDisabled boolean Disables all input to the game.
---@field TabletPC boolean Whether the current device is a TabletPC or not.
---@field ExitToMainMenu boolean Exits to the Main Menu on the next update.
---@field ProductVersion string PvZ Version.
---@field Cursor Cursor The current cursor icon.
---@field MuteOnFocusLost boolean If set to true, the game will automatically mute when unfocused.
---@field FrameDelta integer The minimum amount of time between each frame (in centiseconds).
---@field IsDrawing boolean `true` when the game is drawing graphics.
---@field LastInputTime number The time of the user's last input.
---@field DrawCount integer The number of times the game has rendered.
---@field UpdateCount integer The number of times the game has updated.
---@field Speed number The speed of the game. This can also be changed via altering the `LawnApp.FrameDelta` property.
---@field Paused boolean Whether the game is paused or not.
---@field LastDrawTime number The time of the last draw.
---@field SystemCursor SystemCursor The cursor code. Values can be found in SystemCursor.
---@field MouseInWindow boolean Whether the mouse is in the PvZ window or not.
---@field Active boolean `true` when the game window is active.
---@field HasFocus boolean `true` when the game window is focused.
---@field Minimized boolean `true` when the game window is minimized. It will stop rendering and input interception.
---@field Loaded boolean `true` when the game has finished loading the resources.
---@field DebugKeysEnabled boolean Turns on debug keys when `true`.
---@field EnableMaximizeButton boolean Enables the maximize button and toggles FullScreen mode when it's pressed. If you want to change this, connect to the Events.LawnAppCreated event.
---@field CtrlDown boolean Whether the control key is down or not.
---@field AltDown boolean Whether the alt key is down or not.
---@field ResourceManager ResourceManager
---@field BuildNumber integer
---@field BuildDate string
---@field Game Game The game object. `nil` when there's no game currently.
---@field Level Game The current level. `nil` when there's no game currently. Redirects directly to LawnApp.Game.
---@field TitleScreen TitleScreen
---@field MainMenu MainMenu
---@field ChooseYourSeeds ChooseYourSeeds
---@field AwardScreen AwardScreen
---@field CreditScreen CreditScreen
---@field ChallengeScreen ChallengeScreen
---@field SoundSystem SoundSystem
---@field GameMode GameMode
---@field Scene GameScene
---@field NewUser boolean `true` When the user is being prompted for a username.
---@field GamesPlayed integer
---@field MaxExecutions integer
---@field MaxTime integer
---@field EasyPlantingCheat boolean
---@field PoolEffect PoolEffect
---@field ZenGarden ZenGarden
---@field EffectSystem EffectSystem
---@field ProfileManager ProfileManager
---@field CurrentUserData UserData The save data of the current user.
---@field LevelStats LevelStats
---@field ShutdownRequest boolean If set to `true`, the game will close upon the next update starting.
---@field AppCounter integer A counter that consistently goes up. You can use this as an internal clock.
---@field Music Music
---@field CrazyDaveAnimation Reanimation
---@field CrazyDaveBlinkAnimation Reanimation
---@field CrazyDaveState CrazyDaveState
---@field CrazyDaveBlinkTimer integer Crazy Dave will blink when this timer reaches 1, and it will restart back.
---@field CrazyDaveMessageIndex integer
---@field CrazyDaveMessage string The message that crazy dave is currently saying. Changing this to an empty string will make the text bubble vanish.
---@field GameResult GameResult The result of the previous game.
---@field MustacheMode boolean
---@field SuperMowerMode boolean
---@field FutureMode boolean
---@field PinataMode boolean
---@field DaisyMode boolean
---@field SukhbirMode boolean
--#endregion
--#region Events
---@field Created LawnAppCreated Goes off after tha LawnApp is created.
---@field OnLoaded LawnAppLoaded Goes off after the LawnApp finishes loading its resources.<br>Fonts and most Images are initialized after this event is called.<br>If this event returns `false`, Luna prevents the game from registering the LawnApp as loaded. This event will be called each frame until `LawnApp.HasLoaded` equals true.
---@field Updating LawnAppUpdate Goes off each frame before the LawnApp updates before rendering.
--#endregion
--#region Systems
---@field ProjectileSystem ProjectileSystem
---@field ZombieSystem ZombieSystem
---@field PlantSystem PlantSystem
--#endregion
LawnApp = {};