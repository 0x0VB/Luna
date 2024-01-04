---@meta

--#region FVector2

---Constructs an FVector2 value from the given X & Y Values.
---@param X number?
---@param Y number?
---@return FVector2
---@nodiscard
function FVector2(X, Y) return ({})[0]; end;

---@class FVector2: LunaStruct
---@field X number
---@field Y number
---@operator mul(number): FVector2
---@operator div(number): FVector2
---@operator add(VecComp): FVector2
---@operator sub(VecComp): FVector2
---@operator unm(): FVector2
local Struct = {};

---Converts this Vector2 value into its 3D equivalent, subsiting X for X, 0 for Y, and Y for Z.
---@return Vector3
---@nodiscard
function Struct:To3D() end;

---Changes this vector's magnitude to equal `NewMagnitude`, maintaining its old direction.
---@param NewMagnitude number
---@return FVector2
function Struct:SetMagnitude(NewMagnitude) return self; end;

---Converts this FVector2 value into its IVector2 equivalent and rounds the X and Y.
---@return IVector2
---@nodiscard
function Struct:ToIVector2() end;

---Converts this FVector2 value into its IVector2 equivalent and rounds the X and Y.
---@return IVector2
---@nodiscard
function Struct:ToInt() end;

---Returns the magnitude of this Vector value.
---@return number
---@nodiscard
function Struct:Magnitude() return 0; end;

---Returns a Vector value equivalent to this value's direction but with a magnitude of 1.
---@return FVector2
---@nodiscard
function Struct:Unit() end;

---Returns a Vector value perpendicular to this one.
---@return FVector2
---@nodiscard
function Struct:Normal() end;

---Returns an Vector2 value that points to the given target from this value. The value returned by this function has a magnitude of 1.
---@param Target VecComp
---@return FVector2
---@nodiscard
function Struct:DirectionTo(Target) end;

---Returns the distance between this value and the given Vector value.
---@param Target VecComp
---@return number
---@nodiscard
function Struct:DistanceFrom(Target) return 1 end;

---Sets this Vector value to the given `Other` Vector value by the given `Alpha` amount.<br>If `Alpha` is 0, the value is unchanged.<br>If `Alpha` is 1, the value becomes exactly equal to `Other`.<br><br><u>This function overwrites the original value. Use GetLerped if you do not want to alter this value.</u>
---@param Other VecComp
---@param Alpha number
---@return FVector2
function Struct:Lerp(Other, Alpha) end;

---Returns a lerped version of this value. Check the :Lerp function for more information about lerping.
---@param Other VecComp
---@param Alpha number
---@return FVector2
---@nodiscard
function Struct:GetLerped(Other, Alpha) end;

---Moves this Vector value to `Other` by the given amount.<br><br><u>This function overwrites the original value. Use GetNudged if you do not want to alter this value.</u>
---@param Other VecComp
---@param Amount number
---@return FVector2
function Struct:Nudge(Other, Amount) end;

---Returns a nudged version of this Vector value by the given amount.
---@param Other VecComp
---@param Amount number
---@return FVector2
---@nodiscard
function Struct:GetNudged(Other, Amount) end;

---Rotates this Vector value by the given angle.<br><br><u>This function overwrites the original value. Use GetRotated if you do not want to alter this value.</u>
---@param Angle number
---@return FVector2
function Struct:Rotate(Angle) end;

---Returns a rotated version of this Vector value by the given angle.
---@param Angle number
---@return FVector2
---@nodiscard
function Struct:GetRotated(Angle) end;

---Inverses this Vector value.<br><br><u>This function overwrites the original value. Use GetInverse if you do not want to alter this value.</u>
---@return FVector2
function Struct:Inverse() end;

---Returns an inversed version of this Vector value.
---@return FVector2
---@nodiscard
function Struct:GetInverse() end;

---Translates this value by the given X and Y amounts.<br><br><u>This function overwrites the original value. Use GetTranslated if you do not want to alter this value.</u>
---@param X number?
---@param Y number?
---@return FVector2
function Struct:Translate(X, Y) return self; end;

---Returns a copy offset this value translated by the given X and Y amounts.
---@param X number?
---@param Y number?
---@return FVector2
---@nodiscard
function Struct:GetTranslated(X, Y) return self; end;
--#endregion

--#region IVector2

---Constructs an IVector2 value from the given X & Y Values.
---@param X number?
---@param Y number?
---@return IVector2
---@nodiscard
function IVector2(X, Y) return ({})[0]; end;

---An adaptive function that returns an IVector2 value if both its arguments are an integer (or nil), and an FVector2 value otherwise.
---@param X integer?
---@param Y integer?
---@return IVector2
---@overload fun(X: number, Y: number): FVector2
function Vector2(X, Y) return ({})[0]; end;

---@class IVector2: LunaStruct
---@field X number
---@field Y number
---@operator mul(number): FVector2
---@operator div(number): FVector2
---@operator add(VecComp): IVector2
---@operator sub(VecComp): IVector2
local Struct = {};

---Converts this Vector2 value into its 3D equivalent, subsiting X for X, 0 for Y, and Y for Z.
---@return Vector3
---@nodiscard
function Struct:To3D() end;

---Changes this vector's magnitude to equal `NewMagnitude`, maintaining its old direction.
---@param NewMagnitude number
---@return IVector2
function Struct:SetMagnitude(NewMagnitude) return self; end;

---Converts this IVector2 value into its FVector2 equivalent.
---@return IVector2
---@nodiscard
function Struct:ToFVector2() end;

---Converts this IVector2 value into its FVector2 equivalent.
---@return IVector2
---@nodiscard
function Struct:ToFloat() end;

---Returns the magnitude of this Vector value.
---@return number
---@nodiscard
function Struct:Magnitude() return 0; end;

---Returns a Vector value equivalent to this value's direction but with a magnitude of 1.
---@return FVector2
---@nodiscard
function Struct:Unit() end;

---Returns a Vector value perpendicular to this one.
---@return IVector2
---@nodiscard
function Struct:Normal() end;

---Returns an Vector2 value that points to the given target from this value. The value returned by this function has a magnitude of 1.
---@param Target VecComp
---@return FVector2
---@nodiscard
function Struct:DirectionTo(Target) end;

---Returns the distance between this value and the given Vector value.
---@param Target VecComp
---@return number
---@nodiscard
function Struct:DistanceFrom(Target) return 1 end;

---Sets this value to the given `Other` Vector value by the given `Alpha` amount.<br>If `Alpha` is 0, the value is unchanged.<br>If `Alpha` is 1, the value becomes exactly equal to `Other`.
---@param Other VecComp
---@param Alpha number
---@return IVector2
function Struct:Lerp(Other, Alpha) end;

---Returns a lerped version of this Vector value. Check the :Lerp function for more information about lerping.
---@param Other VecComp
---@param Alpha number
---@return IVector2
---@nodiscard
function Struct:GetLerped(Other, Alpha) end;

---Moves this Vector value to `Other` by the given amount.
---@param Other VecComp
---@param Amount number
---@return IVector2
function Struct:Nudge(Other, Amount) end;

---Returns a nudged version of this Vector value by the given amount.
---@param Other VecComp
---@param Amount number
---@return IVector2
---@nodiscard
function Struct:GetNudged(Other, Amount) end;

---Rotates this Vector value by the given angle.
---@param Angle number
---@return IVector2
function Struct:Rotate(Angle) end;

---Returns a rotated version of this Vector value by the given angle.
---@param Angle number
---@return IVector2
---@nodiscard
function Struct:GetRotated(Angle) end;

---Inverses this Vector value.
---@return IVector2
function Struct:Inverse() end;

---Returns an inversed version of this Vector value.
---@return IVector2
---@nodiscard
function Struct:GetInverse() end;

---Translates this value by the given X and Y amounts.
---@param X number?
---@param Y number?
---@return IVector2
function Struct:Translate(X, Y) return self; end;

---Returns a copy offset this value translated by the given X and Y amounts.
---@param X number?
---@param Y number?
---@return IVector2
function Struct:GetTranslated(X, Y) return self; end;
--#endregion
