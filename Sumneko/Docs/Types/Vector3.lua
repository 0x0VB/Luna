---@meta
---Creates a Vector3 value with the given parameters.
---@param X number?
---@param Y number?
---@param Z number?
---@return Vector3
function Vector3(X, Y, Z) return ({})[0]; end;

---@class Vector3: LunaStruct
---@field X number
---@field Y number
---@field Z number
---@operator add(VecComp): Vector3
---@operator sub(VecComp): Vector3
---@operator mul(number): Vector3
---@operator div(number): Vector3
---@operator unm(): Vector3
local Vec3 = {};

---Changes this vector's magnitude to equal `NewMagnitude`, maintaining its old direction.
---@param NewMagnitude number
---@return Vector3
function Vec3:SetMagnitude(NewMagnitude) return self; end;

---Returns a Vector3 value perpendicular to this one.
---@return Vector3
function Vec3:Normal() return self; end;

---Returns a Vector3 value equivalent to this one directionally but with a magnitude of 1.
---@return Vector3
function Vec3:Unit() return self; end;

---Returns the magnitude of this Vector3 value.
---@return number
function Vec3:Magnitude() return 0; end;

---Returns a 2D equivalent of this Vector3 value, discarding the Z component.
---@return FVector2
function Vec3:To2D() return FVector2(); end;

---Returns an integer 2D equivalent of this Vector3 value, discarding the Z component.
---@return IVector2
function Vec3:ToInt2D() return IVector2() end;

---Returns a 2D equivalent of this Vector3 value projected onto the screen. The projection is calculated by (X, Y - Z).
---@return FVector2
function Vec3:Project() return FVector2() end;

---Returns the distance between this Vector3 value and the given Vector value. If a 2D value is provided, the Z is assumed to be 0.
---@param Other VecComp
---@return number
function Vec3:DistanceFrom(Other) return 0; end;

---Returns the direction needed to reach the given `Target` from this vector's position. If a 2D value is provided, the Z is assumed to be 0.<br><br><u>The value returned by this function will always have a magnitude of 1.</u>
---@param Target VecComp
---@return Vector3
function Vec3:DirectionFrom(Target) return Vector3(); end;

---Rotates this Vector3 value from the Z-Axis by the given `Angle`.<br><br><u>This function overwrites the original value. Use GetRotated if you do not want to alter this value.</u>
---@param Angle any
---@return Vector3
function Vec3:Rotate(Angle) return self; end;

---Returns a rotated version of this vector value rotated by the given `Angle`.
---@param Angle any
---@return Vector3
---@nodiscard
function Vec3:GetRotated(Angle) return self; end;

---Sets this Vector value to the given `Other` Vector value by the given `Alpha` amount.<br>If `Alpha` is 0, the value is unchanged.<br>If `Alpha` is 1, the value becomes exactly equal to `Other`. If a 2D value is provided, the Z component is assumed to be 0.<br><br><u>This function overwrites the original value. Use GetLerped if you do not want to alter this value.</u>
---@param Other VecComp
---@param Alpha number
---@return Vector3
function Vec3:Lerp(Other, Alpha) end;

---Returns a lerped version of this vector value to the given vector by the given `Alpha` amount.
---@param Other VecComp
---@param Alpha number
---@return Vector3
---@nodiscard
function Vec3:GetLerped(Other, Alpha) end;

---Moves this Vector value to `Other` by the given amount.<br><br><u>This function overwrites the original value. Use GetNudged if you do not want to alter this value.</u>
---@param Other VecComp
---@param Amount number
---@return Vector3
function Vec3:Nudge(Other, Amount) end;

---Returns a nudged version of this vector value
---@param Other VecComp
---@param Amount number
---@return Vector3
---@nodiscard
function Vec3:GetNudged(Other, Amount) end;

---Inverses this Vector value.<br><br><u>This function overwrites the original value. Use GetInverse if you do not want to alter this value.</u>
---@return Vector3
function Vec3:Inverse() end;

---Returns an inversed version of this vector value.
---@return Vector3
---@nodiscard
function Vec3:GetInversed() end;

---Translates this value by the given X, Y, and Z amounts.<br><br><u>This function overwrites the original value. Use GetTranslated if you do not want to alter this value.</u>
---@param X number?
---@param Y number?
---@param Z number?
---@return Vector3
function Vec3:Translate(X, Y, Z) return self; end;

---Returns a translated version of this vector value by the given X, Y, and Z values.
---@param X number?
---@param Y number?
---@param Z number?
---@return Vector3
---@nodiscard
function Vec3:GetTranslated(X, Y, Z) return self; end;