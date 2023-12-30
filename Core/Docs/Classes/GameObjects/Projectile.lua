---@meta
---@class Projectile: GameObject
---@field CurrentTick integer
---@field MaxTicks integer
---@field AnimCounter integer
---@field Position Vector3
---@field Velocity Vector3
---@field Gravity number
---@field ShadowY number Equivalent to `Floor`. This indicates the location of this projectile's shadow, and its floor (the lowest point it can go before colliding.)
---@field Floor number Equivalent to `ShadowY`. This indicates the location of this projectile's shadow, and its floor (the lowest point it can go before colliding.)
---@field Dead boolean
---@field TicksPerFrame integer
---@field MotionStyle ProjectileMotionStyle
---@field ProjectileType ProjectileType
---@field Age integer
---@field Rotation number
---@field RotationSpeed number
---@field OnHighGround boolean
---@field DamageRangeFlags integer
---@field HitTorchwoodAt integer
---@field Attachment Attachment
---@field CobTargetLane integer
---@field CobTargetX number
---@field TargetZombie Zombie
---@field LastPortalX integer
local Projectile = {};

Projectile.MotionStyle = ProjectileMotionStyle.Linear;

---Makes this projectile move toward the given target by the given distance. The target can be a Vector2, Vector3, or an Entity.
---@param Target Vector2 | Vector3 | GameObject
---@param Distance number
function Projectile:MoveTowards(Target, Distance) end;

---Sets the direction of the projectile to face the given target. If `ResetAcceleration` is true, the function will nullify this projectil's acceleration.
---@param Target Vector2 | Vector3 | GameObject
---@param ResetAcceleration boolean
function Projectile:SetDirection(Target, ResetAcceleration) end;

---Influences this projectile's direction to point more towards the given target by the given amount.<br>The amount is a number between 0-1.
---@param Target Vector2 | Vector3 | GameObject
---@param Amount number
function Projectile:InfluenceDirection(Target, Amount) end;

---Forces this projectile to collide. If `Zombie` is not nil, the given zombie will take the damage of this projectile and effects will be played.
---@param Zombie Zombie?
function Projectile:Collide(Zombie) end;

---Influences the trajectory of this projectile by the given angle.
---@param Angle number
function Projectile:RotateDirection(Angle) end;

---Steers the direction of this projectile to point more towards the given target by the given Angle amount
---@param Target Vector2 | Vector3 | GameObject The target this projectile will home towards.
---@param Angle number The angle that will steer the direction towards the target.
---@param Move boolean? If set to `true`, the function will rotate the direction and move towards the target. If set to `false`, the function will only steer the velocity in the target's direction. Is true by default.
---@param RotateTowards boolean? If set to `true`, `self.Rotation` will also be altered to face the current direction. Is true by default.
function Projectile:HomeTowards(Target, Angle, Move, RotateTowards) end;