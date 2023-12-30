---@meta
---@class Game: UIElement
---@field LawnApp LawnApp
---@field CursorObject GameCursor
---@field CursorPreview CursorPreview
---@field Advice UIMessage
---@field SeedBank SeedBank
---@field MenuButton GameButton
---@field StoreButton GameButton
---@field IgnoreMouseUp boolean
---@field ToolTip UIToolTip
---@field DebugFont Font
---@field CutScene CutScene
---@field Challenge Challenge
---@field Paused boolean
---@field EnableGraveStones boolean
---@field SpecialGrave Vector2
---@field SpecialGraveX integer
---@field SpecialGraveY integer
---@field FogOffset number
---@field FogBlownTimer integer
---@field SunDropTimer integer
---@field SunsFallen integer
---@field ShakeTimer integer
---@field ShakeAmount FVector2
---@field ShakeAmountX number
---@field ShakeAmountY number
---@field Background GameBackground
---@field Level integer
---@field SodPosition integer
---@field LastMousePosition Vector2
---@field Sun integer
---@field SunCount integer
---@field WaveCount integer
---@field MainTimer integer
---@field EffectTimer integer
---@field DrawCount integer
---@field RiseFromGraveTimer integer
---@field OutOfMoneyNoticeTimer integer
---@field CurrentWave integer
---@field TotalSpawnedWaves integer
---@field TutorialState TutorialState
---@field TutorialTimer integer
---@field LastBungeeWave integer
---@field NextWaveHPThreshold integer
---@field MaxWaveHP integer
---@field NextWaveTimer integer
---@field MaxWaveTimer integer
---@field HugeWaveTimer integer
---@field AdviceIndex AdviceIndex
---@field FinalBossKilled boolean
---@field ShowShovel boolean
---@field CoinBankFadeTimer integer
---@field DebugTextMode DebugTextMode
---@field LevelComplete boolean
---@field GameFadeTimer integer
---@field NextSurvivalStageTimer integer
---@field ScoreNextMowerTimer integer
---@field LevelAwardSpawned boolean
---@field ProgressMeterWidth integer
---@field FlagsRaisedCount integer
---@field ZombieFreezeTimer integer
---@field RandomSeed integer
---@field TimeStopTimer integer
---@field CoinsDropping boolean
---@field FinalWaveSoundTimer integer
---@field CobCannonCursorDelay integer
---@field CobCannonMouse Vector2
---@field CobCannonMouseX integer
---@field CobCannonMouseY integer
---@field KilledYeti boolean
---@field MustacheMode boolean
---@field SuperMowerMode boolean
---@field FutureMode boolean
---@field PinataMode boolean
---@field DaisyMode boolean
---@field SukhbirMode boolean
---@field PreviousGameResult GameResult
---@field TriggeredLawnMowers integer
---@field ActivePlayTime integer
---@field InactivePlayTime integer
---@field MaxSunPlants integer
---@field MaxSunProducers integer
---@field StartDrawTime integer
---@field IntervalDrawTime integer
---@field IntervalDrawCountStart integer
---@field PreloadTime integer
---@field GameID integer
---@field GravesCleared integer
---@field PlantsEaten integer
---@field PlantsShoveled integer
---@field CoinsCollected integer
---@field DiamondsCollected integer
---@field ZenGardenPlantsCollected integer
---@field ChocolateCollected integer
---@field Exists boolean `true` when a game exists.
---@field Created GameCreated
---@field Killed GameKilled
---@field Update GameUpdate
Game = {};

---Creates and returns a new projectile of the given type at the given coordinates. If `Lane` is nil, it's calculated automatically according to the `Y` position. If `ZIndex` is nil, it's assumed to be 1.
---@param Type ProjectileType
---@param X integer
---@param Y integer
---@param Lane integer?
---@param ZIndex integer?
---@return Projectile
function Game:AddProjectile(Type, X, Y, Lane, ZIndex) end;

---Creates a new plant of the given type at the given grid coordinates. ImitaterType is provided only when planting an Imitater. It represent the plant it will turn into.
---@param Type SeedType
---@param X integer
---@param Y integer
---@param ImitaterType SeedType?
---@return Plant
function Game:AddPlant(Type, X, Y, ImitaterType) end;

---Returns the (Column, Lane) pair that corresponds with this (X, Y) pixel pair.
---@param X integer?
---@param Y integer?
---@return IVector2
function Game:PixelToLawn(X, Y) return Vector2(); end;

---Returns the (X, Y) pixel pair that corresponds with this (Column, Lane) pair.
---@param Column any
---@param Lane any
---@return IVector2
function Game:LawnToPixel(Column, Lane) return Vector2(); end;

---@class GameCreated: LunaEvent
local GameCreated = {};

---Fired after a new game has been created but before it updates for the first time.
---@param Function fun()
function GameCreated:Connect(Function) end;

---@class GameKilled: LunaEvent
local GameKilled = {};

---Fired before the game is killed (destroyed and removed.) If this function returns `false`, the deletion of the game is discarded.
---@param Function fun(): boolean?
function GameKilled:Connect(Function) end;

---@class GameUpdate: LunaEvent
local GameUpdate = {};

---Fired each frame to update the game. If the connected function returns `true`, the update for that frame is skipped.
---@param Function fun(): boolean?
function GameUpdate:Connect(Function) end;