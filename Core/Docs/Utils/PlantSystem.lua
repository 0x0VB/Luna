---@meta
---@class PlantSystem
---@field PlantUpdating PlantUpdating
---@field PlantFiring PlantFiring
---@field PlantCreated PlantCreated
PlantSystem = {};

---@class PlantUpdating: LunaEvent
local PlantUpdating = {};

---Fired every frame for every plant. Used to update the plant before rendering. If the connected functiion returns `true`, the update for the current zombie will be skipped for this frame.
---@param Function fun(Plant: Plant): boolean?
function PlantUpdating:Connect(Function) end;

---@class PlantFiring: LunaEvent
local PlantFiring = {};

---Fired whenever a plant fires its shots. `Target` will be `nil` most of the time unless the plant requires a target, like CatTail.
---@param Function fun(Plant: Plant, Target: Zombie?, Lane: integer, SecondaryWeapon: boolean): boolean?
function PlantFiring:Connect(Function) end;

---@class PlantCreated: LunaEvent
local PlantCreated = {};

---Fired whenever a new plant is created.
---@param Function fun(Plant: Plant)
function PlantCreated:Connect(Function) end;