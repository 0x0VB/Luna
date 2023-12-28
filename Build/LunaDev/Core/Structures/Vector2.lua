---@meta
---@alias Vector Vector2 | Vector3

---Constructs a new Vector2 value with the given X and Y components.
---@param X number?
---@param Y number?
---@return Vector2
function Vector2(X, Y) end;

---@class Vector2
---@field X number The horizontal component of the vector.
---@field Y number The vertical component of the vector.
---@operator add(Vector2): Vector2
---@operator sub(Vector2): Vector2
---@operator mul(number): Vector2
---@operator div(number): Vector2
---@operator unm(): Vector2
local Vector2 = {};

---Returns a new Vector2 value maintaining the direction of this one, but with the given magnitude.
---@param NewMag number
---@return Vector2
function Vector2:SetMagnitude(NewMag) end;

---Returns the distance between this Vector2 value and the `Other` Vector value.
---@param Other Vector
---@return number
function Vector2:DistanceFrom(Other) end;

---Returns a Vector2 value that is the direction from this Vector2 value to the given `Target` Vector value.
---@param Target Vector
---@return Vector2
function Vector2:DirectionTo(Target) end;

---Returns the magnitude of this Vector value.
---@return number
function Vector2:Magnitude() end;

---Returns a rotated version of this Vector value by the given `Angle` amount.
---@param Angle number
---@return Vector2
function Vector2:Rotate(Angle) end;

---Returns the normal of this vector,
---@return Vector2
function Vector2:Normal() end;

---Returns a Vector value nudged by the given `Amount` towards the `Other` vector value.
---@param Other number
---@param Amount Vector
---@return Vector2
function Vector2:Nudge(Other, Amount) end;

---Returns a floored version of this Vector2 value.
---@return Vector2
function Vector2:ToInt() end;

---Returns a Vector value equivalent to this Vector's direction but with a magnitude of 1.
---@return Vector2
function Vector2:Unit() end;

---Returns a Vector2 value lerped between this one and `Other` by the given `Alpha` amount. `Alpha` is a number between 0 - 1 and is 0.5 by default.
---@param Other Vector
---@param Alpha number
function Vector2:Lerp(Other, Alpha) end;

---Returns a Vector3 value of this Vector2 with a Z component of 0.
---@return Vector3
function Vector2:To3D() end;