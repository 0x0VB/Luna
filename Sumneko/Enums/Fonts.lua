---@class FontBase
---@field LineHeight integer
---@field LinePadding integer
---@field Height integer
---@field LineSpacingOffset integer

---@class ImageFont: FontBase
---@field FontData FontData
---@field PointSize integer
---@field Scale number
---@field ForceWhiteColor boolean

---@class SysFont: FontBase

---@class FontData: BaseRes

---@alias Font FontBase | Fonts

---@enum (key) Fonts
Fonts =
{
    BTod16 = 0x2A7224;-- Loaded before anything else, used in the loading screen.
    BTod12 = 0x2A77F8;

    HouseOfTerror28 = 0x2A7714;
    HouseOfTerror20 = 0x2A75C8;
    HouseOfTerror16 = 0x2A74B0;

    Pix118Bold = 0x2A72D8;
    Pico129 = 0x2A7498;

    ContinuumBold14 = 0x2A7384;
    ContinuumBold14Outback = 0x2A7734;

    DwarvenTodcraft12 = 0x2A7630;
    DwarvenTodcraft15 = 0x2A72EC;
    DwarvenTodcraft18 = 0x2A7314;
    DwarvenTodcraft24 = 0x2A7A40;

    DwarvenTodcraft18BrightGreenInset = 0x2A7248;
    DwarvenTodcraft18GreenInset = 0x2A7AD4;
    DwarvenTodcraft18Yellow = 0x2A79F4;
    DwarvenTodcraft36BrightGreenInset = 0x2A75D4;
    DwarvenTodcraft36GreenInset = 0x2A77B8;
};