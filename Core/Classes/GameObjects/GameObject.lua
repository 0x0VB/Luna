---@diagnostic disable: undefined-global
local NewField = LunaClass.NewField;
local TypeCasts = LunaClass.TypeCasts;
local Game = NewField(0x4, true, true, "Game");
local Hitbox = NewField(0x8, false, false, TypeCasts.Rect);
LunaClass.Register(
    "GameObject",
    {
        LawnApp = NewField(0x0, true, true, "LawnApp");
        Game = Game;
        Board = Game;
        Level = Game;
        Bounds = Hitbox;
        Hitbox = Hitbox;
        Visible = NewField(0x18, false, false, TypeCasts.Bool);
        Lane = NewField(0x1C, false, false, TypeCasts.Int);
        RenderOrder = NewField(0x20, false, false, TypeCasts.Int);

        GetProjectilesInRadius = OBJ_PROJ3D;
        GetNearestZombie = OBJ_GETNZOMBIE;
    },
    0x24,
    true
);

ENV.OBJ_PROJ3D = nil;
ENV.OBJ_GETNZOMBIE = nil;