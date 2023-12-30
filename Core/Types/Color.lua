--#region Autofill Data
goto Color;

---@class Color: LunaStruct
---@field R integer
---@field G integer
---@field B integer
---@field A integer The opacity of the color from 0-255
---@field Red integer Equivalent to Color.R
---@field Green integer Equivalent to Color.G
---@field Blue integer Equivalent to Color.B
---@field Alpha integer Equivalent to Color.A
---@field GetHexString fun(self: Color): string Creates the

---Creates a Color value with the given RGBA components.
---@param R integer?
---@param G integer?
---@param B integer?
---@param A integer?
---@return Color
---@nodiscard
function Color(R, G, B, A) return ({})[0]; end;

--#endregion

::Color::
---Creates a Color value using the color's hex code.
---@param Str string
---@return Color
---@nodiscard
function Hex(Str)
    -- Remove the '#' character if it exists
    Str = (Str or "000"):gsub("#", "");

    -- If the hex string is only 3 characters long, expand it to 6 characters
    if (#Str == 3) then
        Str = Str:gsub("(.)", "%1%1");
    end;

    -- Convert the hex string to RGBA values
    local R = tonumber(Str:sub(1, 2), 16) or 0;
    local G = tonumber(Str:sub(3, 4), 16) or 0;
    local B = tonumber(Str:sub(5, 6), 16) or 0;
    local A = tonumber(Str:sub(7, 8), 16) or 255;

    return Color(R, G, B, A);
end;

local R = LunaClass.NewField(0x0, false, false, LunaClass.TypeCasts.Int);
local G = LunaClass.NewField(0x4, false, false, LunaClass.TypeCasts.Int);
local B = LunaClass.NewField(0x8, false, false, LunaClass.TypeCasts.Int);
local A = LunaClass.NewField(0xC, false, false, LunaClass.TypeCasts.Int);

local Format = string.format;
---Converts this color to a hex code string
---@param self Color
---@return string
local function GetHexString(self) return "#"..Format("%X", self.R)..Format("%X", self.G)..Format("%X", self.B)..Format("%X", self.A); end;
LunaClass.Register(
    "Color",
    {
        R = R; Red = R;
        G = G; Green = G;
        B = B; Blue = B;
        A = A; Alpha = A;
        GetHexString = GetHexString;
        __tostring = GetHexString;
    },
    0x10
);