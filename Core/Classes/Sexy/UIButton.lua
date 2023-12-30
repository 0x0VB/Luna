local NewField = LunaClass.NewField;
local TypeCasts = LunaClass.TypeCasts;
local Int = TypeCasts.Int;
local Bool = TypeCasts.Bool;
local String = TypeCasts.String;
local Rect = TypeCasts.Rect;

local Text = NewField(0x90, false, false, String);
LunaClass.Register(
    "UIButton",
    {
        ID = NewField(0x88, false, false, Int);
        Text = Text;
        Label = Text;
        Justify = NewField(0xA8, false, false, Int);
        Font = NewField(0xAC, true, true, "Font");
        Image = NewField(0xB0, true, true, "Image");
        HoveredImage = NewField(0xB4, true, true, "Image");
        DownImage = NewField(0xB8, true, true, "Image");
        DisabledImage = NewField(0xBC, true, true, "Image");
        Bounds = NewField(0xC0, false, false, Rect);
        HoveredBounds = NewField(0xD0, false, false, Rect);
        DownBounds = NewField(0xE0, false, false, Rect);
        DisabledBounds = NewField(0xF0, false, false, Rect);
        Inverted = NewField(0x100, false, false, Bool);
        NoDraw = NewField(0x101, false, false, Bool);
    },
    0x120,
    true,
    "UIElement"
);