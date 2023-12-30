---@diagnostic disable: undefined-global
local NewField = LunaClass.NewField;
local TypeCasts = LunaClass.TypeCasts;
local Int = TypeCasts.Int;
local Bool = TypeCasts.Bool;
local UI = TypeCasts.UI;

LunaClass.Register(
    "UIContainer",
    {
        UIRoot = NewField(0x10, true, true, "UIRoot");
        Parent = NewField(0x14, true, false, UI);
        NoAutoDestroy = NewField(0x19, false, false, Bool);
        Dirty = NewField(0x2C, false, false, Bool);

        Bounds = NewField(0x30, false, false, TypeCasts.Rect);
        Size = NewField(0x38, false, false, TypeCasts.IVector2);
        HasAlpha = NewField(0x40, false, false, Bool);
        ClipToBounds = NewField(0x41, false, false, Bool);

        Priority = NewField(0x4C, false, false, Int);
        ZIndex = NewField(0x50, false, false, Int);

        Destroy = UIC_DESTROY;
        ClearChildren = UIC_CLRCHILD;
        GetChildren = UIC_GETCHLDN;
        GetChild = UIC_GETCHILD;
        AddChild = UIC_ADDCHILD;
        RemoveChild = UIC_REMCHILD;
        Contains = UIC_CONTAINS;

        BringToFront = UIC_TOFRONT;
        BringToBack = UIC_BTOBACK;
        IsBehind = UIC_ISBEHIND;
        PutInFront = UIC_INFRONT;
        PutBehind = UIC_PBEHIND;

        Intersects = UIC_INTERSECTS;
        GetAbsolutePosition = UIC_GETABSPOS;
    },
    0x54,
    true
);

ENV.UIC_DESTROY = nil;
ENV.UIC_CLRCHILD = nil;
ENV.UIC_GETCHLDN = nil;
ENV.UIC_GETCHILD = nil;
ENV.UIC_ADDCHILD = nil;
ENV.UIC_REMCHILD = nil;

ENV.UIC_TOFRONT = nil;
ENV.UIC_BTOBACK = nil;
ENV.UIC_INFRONT = nil;
ENV.UIC_PBEHIND = nil;
ENV.UIC_ISBEHIND = nil;

ENV.UIC_INTERSECTS = nil;
ENV.UIC_GETABSPOS = nil;

LunaClass.Register(
    "UIElement",
    {
        Visible = NewField(0x54, false, false, Bool);
        MouseVisible = NewField(0x55, false, false, Bool);
        Disabled = NewField(0x56, false, false, Bool);
        HasFocus = NewField(0x57, false, false, Bool);
        IsDown = NewField(0x58, false, false, Bool);
        Hovered = NewField(0x59, false, false, Bool);
        HasTransparencies = NewField(0x5A, false, false, Bool);

        MousePadding = NewField(0x6C, false, false, TypeCasts.Pad);
        WantsFocus = NewField(0x7D, false, false, Bool);

        Next = NewField(0x80, true, false, UI);
        Prev = NewField(0x84, true, false, UI);
    },
    0x88,
    true,
    "UIContainer"
);