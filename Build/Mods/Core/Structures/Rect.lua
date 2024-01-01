---@meta

---Constructs a new rectangle with the given components.
---@param X integer?
---@param Y integer?
---@param W integer?
---@param H integer?
---@return Rect
function Rect(X, Y, W, H) end;

---@class Rect
---@field X integer The horizontal position of the rectangle.
---@field Y integer The vertical position of the rectangle.
---@field W integer The width of the rectangle.
---@field H integer The height of the rectangle.
---@field P Vector2 [READ-ONLY] The position of the rectangle.
---@field S Vector2 [READ-ONLY] [/b]The size of the rectangle.
---@operator add(Rect): Rect
---@operator sub(Rect): Rect
---@operator mul(number): Rect
---@operator div(number): Rect
---@operator unm: Rect
local Rect = {};

---Returns the overlap between the two rectangles.
---@param Other Rect
---@return Rect
function Rect:GetIntersection(Other) end;

---Returns a rectangle with the size of this rectangle and the position of the given Vector2 value.
---@param Position Vector2
---@return Rect
function Rect:SetPosition(Position) end;

---Returns `true` if this rectangle intersects the given rectangle, `false` otherwise.
---@param Other Rect
---@return boolean
function Rect:Intersects(Other) end;

---Returns a Vector2 value at the center of this rectangle.
---@return Vector2
function Rect:GetCenter() end;

---Returns a new rectangle with this rectangle's size at the given NewCenter.
---@param NewCenter Vector2
function Rect:SetCenter(NewCenter) end;

---Returns `true` if this rectangle completely envelops the `Other` rectangle or point (if a Vector2 value is provided.)
---@param Other Rect | Vector2
function Rect:Contains(Other) end;

---Returns the area of this rectangle.
---@return integer
function Rect:GetArea() end;

---Returns a new rectangle with this rectangle's position but the given `Size` Vector2 value.
---@return Rect
function Rect:SetSize(Size) end;

---Returns a new rectangle lerped to the `Other` rectangle by the given `Alpha` value. `Alpha` should be between 0 and 1 and is  0.5 by default.
---@param Other Rect
---@param Alpha number?
function Rect:Lerp(Other, Alpha) end;