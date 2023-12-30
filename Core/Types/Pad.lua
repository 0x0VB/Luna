--#region Autofill Data
goto Pad;

---@class Pad: LunaStruct
---@field Left integer
---@field Top integer
---@field Right integer
---@field Bottom integer

---Creates a Pad value.
---@param Left integer?
---@param Top integer?
---@param Right integer?
---@param Bottom integer?
---@return Pad
---@nodiscard
---@overload fun(Pixels: integer?): Pad
---@overload fun(Horizontal: integer?, Vertical: integer?): Pad
function Pad(Left, Top, Right, Bottom) return ({})[0]; end;

--#endregion

::Pad::
LunaClass.Register(
    "Pad",
    {
        Left = LunaClass.NewField(0x0, false, false, LunaClass.TypeCasts.Int);
        Top = LunaClass.NewField(0x4, false, false, LunaClass.TypeCasts.Int);
        Right = LunaClass.NewField(0x8, false, false, LunaClass.TypeCasts.Int);
        Bottom = LunaClass.NewField(0xC, false, false, LunaClass.TypeCasts.Int);
        __tostring = function(self)
            return
            "Left: "..tostring(self.Left).." "..
            "Top: "..tostring(self.Top).." "..
            "Right: "..tostring(self.Right).." "..
            "Bottom: "..tostring(self.Bottom);
        end;
    },
    0x10
);