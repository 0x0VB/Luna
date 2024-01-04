---@meta
---Creates a rectangle with the given X, Y, W, & H components.
---@param X integer?
---@param Y integer?
---@param W integer?
---@param H integer?
---@return Rect
---@nodiscard
function Rect(X, Y, W, H) return ({})[0]; end;

---@class Rect: IVector2
---@field X integer The horizontal offset of the rectangle
---@field Y integer The vertical offset of the rectangle
---@field W integer The width of the rectangle
---@field H integer The height of the rectangle
---@field Width integer Equivalent to Rect.W
---@field Height integer Equivalent to Rect.H
---@field Size IVector2 The size of the rectangle as an IVector2 value
---@operator add(VecComp): Rect
---@operator sub(VecComp): Rect
---@operator mul(number): Rect
---@operator div(number): Rect
---@operator unm(): Rect
local Struct = {};

---Returns the area of this rectangle.
---@return number
function Struct:Area() return 0; end;
---Returns the area of this rectangle.
---@return number
function Struct:GetArea() return 0; end;

---Returns the center of this rectangle.
---@return IVector2
function Struct:Center() return IVector2(); end;

---Determines whether the given `Other` rectangle intersects this one.
---@param Other Rect
---@return boolean
function Struct:Intersects(Other) return true; end;

---Determines whether the given Vector2 point is in this rectangle.
---@param Point Vector2
---@return boolean
function Struct:Contains(Point) return true; end;

---Determines whether the given Vector3's projection point is in this rectangle.
---@param Point Vector3
---@return boolean
function Struct:Contains(Point) return true; end;

---Determines whether the given `Other` rectangle is <u>completely</u> contained within this rectangle.
---@param Other Rect
---@return boolean
function Struct:Contains(Other) return true; end;

---Centers this rectangle at the given `NewCenter` value, maintaining its old width and height.
---@param NewCenter VecComp
---@return Rect
function Struct:ReCenter(NewCenter) return self; end;

---Returns a version of this rectangle centered at the given `NewCenter`, maintaining its width and height.
---@param NewCenter any
---@return Rect
function Struct:GetReCentered(NewCenter) return self; end;

---Rotates only the position of this rectangle by the given angle and leaves the width and height as is.
---@param Angle number
---@return Rect
function Struct:Rotate(Angle) return self; end;

---Returns a rotated version of this angle. Only the position of this rectangle is rotated while the width and height are unaffected.
---@param Angle number
---@return Rect
function Struct:GetRotated(Angle) return self; end;

---Sets this value to the given `Other` Vector value by the given `Alpha` amount.<br>If `Alpha` is 0, the value is unchanged.<br>If `Alpha` is 1, the value becomes exactly equal to `Other`.
---@param Target VecComp
---@param Alpha number
---@return Rect
function Struct:Lerp(Target, Alpha) return self; end;

---Translates this value by the given X and Y amounts.
---@param X number?
---@param Y number?
---@return Rect
function Struct:Translate(X, Y) return self; end;

---Returns a copy offset this value translated by the given X and Y amounts.
---@param X number?
---@param Y number?
---@return Rect
function Struct:GetTranslated(X, Y) return self; end;