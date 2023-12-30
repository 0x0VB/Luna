---@meta
--#region Events
---@class ProjectileUpdating: LunaEvent
local ProjectileUpdating = {};

--[[
    Fired each frame to update the projectile.
    <br><br>If the connected function returns `false`, the update is skipped for that frame.
]]
---@param Function fun(Projectile: Projectile): boolean?
function ProjectileUpdating:Connect(Function) end;


---@class ProjectileMovingForward: LunaEvent
local ProjectileMovingForward = {};

--[[
    Fired when a projectile of motion type `Linear`, `Expiring`, or `Spreading` is updating its position.
    <br><br>If the connected function returns `false`, the projectile's position is not updated.
]]
---@param Function fun(Projectile: Projectile): boolean?
function ProjectileMovingForward:Connect(Function) end;


---@class ProjectileMovingBackward: LunaEvent
local ProjectileMovingBackward = {};

--[[
    Fired when a projectile of type `Backwards` is updating its position.
    <br><br>If the connected function returns `true`, the projectile's position is not updated.
]]
---@param Function fun(Projectile: Projectile): boolean?
function ProjectileMovingBackward:Connect(Function) end;
--#endregion

---@class ProjectileCreated: LunaEvent
local ProjectileCreated = {};

---Fired whenever a new projectile is created.
---@param Function fun(Projectile: Projectile)
function ProjectileCreated:Connect(Function) end;

---@class ProjectileSystem
---@field ProjectileUpdating ProjectileUpdating
---@field ProjectileMovingForward ProjectileMovingForward
---@field ProjectileMovingBackward ProjectileMovingBackward
---@field ProjectileCreated ProjectileCreated
---@field LinearSpeed number The default speed of projectiles of motion type `Linear`, `Spreading`, `Expiring`, and `Backwards`.
---@field HomingSteer number The default max steering angle that a projectile of type `Homing` can steer each frame.
ProjectileSystem = {};

---Returns a table containing all projectiles currently in the game.
---@return Projectile[]
function ProjectileSystem:GetProjectiles() end;