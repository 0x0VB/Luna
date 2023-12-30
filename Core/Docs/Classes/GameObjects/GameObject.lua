---@meta
---@class GameObject: LunaGameObject
---@field LawnApp LawnApp
---@field Game Game
---@field Bounds Rect
---@field Hitbox Rect
---@field Visible boolean
---@field Lane integer
---@field RenderOrder integer
local GameObject = {};

---Gets all projectiles in the given radius around this entity. The radius is in pixels and is treated as a 3D Sphere.
---@param Radius integer
---@return Projectile[] Projectiles The list of projectiles in the radius.
function GameObject:GetProjectilesInRadius(Radius) return ({})[0]; end;

---Returns the nearest zombie to this object, and the distance between the zombie and this object as the second return.
---@param MustHaveHead boolean? When true, the function disqualifies all zombies who lost their head. Is true by default.
---@return Zombie Zombie The closest zombie.
---@return number Distance The distance between this object and the zombie.
function GameObject:GetNearestZombie(MustHaveHead) end;