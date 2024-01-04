---@alias VecComp IVector2 | FVector2 | Vector3 | Rect | Pad
---@alias Vector  IVector2 | FVector2 | Vector3
---@alias Vector2 IVector2 | FVector2

LunaClass.TypeCasts.Rect = LunaClass.TypeCasts.RVector4;
LunaClass.TypeCasts.Pad = LunaClass.TypeCasts.PVector4;

local _require = require;
function require(Module) _require("Luna."..Module); end;