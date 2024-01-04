---@diagnostic disable: undefined-global, assign-type-mismatch
local NewField = LunaClass.NewField;
local TypeCasts = LunaClass.TypeCasts;
local Int = TypeCasts.Int;
local Bool = TypeCasts.Bool;
local Rect = TypeCasts.Rect;
local UI = TypeCasts.UI;
local Vector2 = TypeCasts.IVector2;
LunaClass.Register(
    "UIRoot",
    {
        DefaultTab = NewField(0x54, true, false, UI);
        CurrentGraphics = NewField(0x58, true, true, "Graphics");
        LawnApp = NewField(0x5C, true, true, "LawnApp");
        Image = NewField(0x60, true, true, "MemoryImage");
        TransientImage = NewField(0x64, true, true, "MemoryImage");
        LastHadTransients = NewField(0x68, false, false, Bool);

        PopupCommandElement = NewField(0x6C, true, false, UI);
        HasFocus = NewField(0x84, false, false, Bool);
        FocusedElement = NewField(0x88, true, false, UI);
        LastDownElement = NewField(0x8C, true, false, UI);
        HoveredElement = NewField(0x90, true, false, UI);
        BaseModalElement = NewField(0x94, true, false, UI);
        MouseDest = NewField(0xBC, false, false, Rect);
        MouseSource = NewField(0xCC, false, false, Rect);
        MouseIn = NewField(0xDC, false, false, Bool);
        MousePosition = NewField(0xE0, false, false, IVector2);
        LastInputTimeStamp = NewField(0xF0, false, false, Int);
        LastDownButtonID = NewField(0x1F4, false, false, Int);
        ElementFlags = NewField(0x1F8, false, false, Int);

        IsKeyDown = ROOT_ISKD;
        IsMouseButtonDown = ROOT_ISMBD;

        KeyDown = ROOT_KEYDOWN;
        KeyUp = ROOT_KEYUP;
        MouseDown = ROOT_MOUSEDOWN;
        MouseUp = ROOT_MOUSEUP;
        MouseWheel = ROOT_MOUSEWHEEL;
    },
    0x1FC,
    true,
    "UIContainer"
);

---@type UIRoot
UIRoot = LunaClass.Create("UIRoot", 0x100);

ENV.ROOT_ISKD = nil;
ENV.ROOT_ISMBD = nil;

ENV.ROOT_KEYDOWN = nil;
ENV.ROOT_KEYUP = nil;
ENV.ROOT_MOUSEDOWN = nil;
ENV.ROOT_MOUSEUP = nil;
ENV.ROOT_MOUSEWHEEL = nil;