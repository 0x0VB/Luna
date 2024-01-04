---@meta
---@class ZombieSystem
---@field ZombieUpdating ZombieUpdating
---@field ZombieCreated ZombieCreated
ZombieSystem = {};

---Returns a table of all the zombies currently in the game.
---@return Zombie[]
function ZombieSystem:GetZombies() end;

---@class ZombieUpdating: LunaEvent
local ZombieUpdating = {};

---Fired every frame for every zombie. Used to update the zombie before rendering. If the connected functiion returns `true`, the update for the current zombie will be skipped for this frame.
---@param Function fun(Zombie: Zombie): boolean?
function ZombieUpdating:Connect(Function) end;

---@class ZombieCreated: LunaEvent
local ZombieCreated = {};

---Fired whenever a new zombie is initiated.
---@param Function fun(Zombie: Zombie)
function ZombieCreated:Connect(Function) end;