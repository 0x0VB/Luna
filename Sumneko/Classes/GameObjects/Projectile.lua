---@diagnostic disable: undefined-global
local NewField = LunaClass.NewField;
local TypeCasts = LunaClass.TypeCasts;
local Int = TypeCasts.Int;
local Float = TypeCasts.Float;
local Bool = TypeCasts.Bool;
local Attachment = TypeCasts.Attachment;
local Vec3 = TypeCasts.FVector3;
LunaClass.Register(
    "Projectile",
    {
        CurrentTick = NewField(0x24, false, false, Int);
        MaxTicks = NewField(0x28, false, false, Int);
        AnimCounter = NewField(0x2C, false, false, Int);
        Position = NewField(0x30, false, false, Vec3);
        Velocity = NewField(0x3C, false, false, Vec3);
        Gravity = NewField(0x48, false, false, Float);
        ShadowY = NewField(0x4C, false, false, Float);
        Floor = NewField(0x4C, false, false, Float);
        Dead = NewField(0x50, false, false, Bool);
        TicksPerFrame = NewField(0x54, false, false, Int);
        MotionStyle = NewField(0x58, false, false, Int);
        ProjectileType = NewField(0x5C, false, false, Int);
        Age = NewField(0x60, false, false, Int);
        Rotation = NewField(0x68, false, false, Float);
        RotationSpeed = NewField(0x6C, false, false, Float);
        OnHighGround = NewField(0x70, false, false, Bool);
        DamageRangeFlags = NewField(0x74, false, false, Int);
        HitTorchwoodAt = NewField(0x78, false, false, Int);
        Attachment = NewField(0x7C, false, false, Attachment);
        CobTargetX = NewField(0x80, false, false, Float);
        CobTargetLane = NewField(0x84, false, false, Int);
        TargetZombie = NewField(0x88, true, true, "Zombie");
        LastPortalX = NewField(0x8C, false, false, Int);

        MoveTowards = PROJ_MOVETO;
        Collide = PROJ_COLLIDE;
        InfluenceDirection = PROJ_INFLUENCE;
        RotateDirection = PROJ_ROTATEDIR;
        HomeTowards = PROJ_ROTATEDTO;
    },
    0x90,
    true,
    "GameObject"
);

local ProjectileSystem =
{
    LinearSpeed = 3.33;
    HomingSteer = 2;
    ProjectileUpdating = PROJ_UPDATE;
    ProjectileMovingForward = PROJ_FUPDATE;
    ProjectileMovingBackward = PROJ_FUPDATE;
    GetProjectiles = PROJ_GETALL;
    ProjectileCreated = PROJ_CREATED;
};
ENV.LawnApp.ProjectileSystem = ProjectileSystem;
ENV.ProjectileSystem = ProjectileSystem;

ENV.PROJ_PROJ_INFLUENCE = nil;
ENV.PROJ_ROTATEDTO = nil;
ENV.PROJ_ROTATEDIR = nil;
ENV.PROJ_GETALL = nil;
ENV.PROJ_COLLIDE = nil;
ENV.PROJ_UPDATE = nil;
ENV.PROJ_MOVETO = nil;
ENV.PROJ_FUPDATE = nil;
ENV.PROJ_BUPDATE = nil;
ENV.PROJ_CREATED = nil;

return LawnApp.ProjectileSystem;