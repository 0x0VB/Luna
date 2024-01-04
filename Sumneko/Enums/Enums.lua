---@meta
local OldReq = require;
require = function(Name) return OldReq("Luna.Core.Enums."..Name); end;

require("ProjectileMotionStyle");
require("ProjectileType");

require("SeedType");
require("PlantState");
require("MagnetItemType");

require("InputEnums");