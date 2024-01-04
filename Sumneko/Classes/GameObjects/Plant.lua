---@diagnostic disable: undefined-global
local NewField = LunaClass.NewField;
local TypeCasts = LunaClass.TypeCasts;
local Int = TypeCasts.Int;
local Long = TypeCasts.Long;
local Double = TypeCasts.Double;
local Bool = TypeCasts.Bool;
local Word = TypeCasts.Word;
local Float = TypeCasts.Float;
local String = TypeCasts.String;
local Rect = TypeCasts.RVector4;
local Vec2 = TypeCasts.IVector2;
local UI = TypeCasts.UI;
local Attachment = TypeCasts.Attachment;
local Reanimation = TypeCasts.Reanimation;

LunaClass.Register(
    "Plant",
    {
        SeedType = NewField(0x24, false, false, Int);
        Column = NewField(0x28, false, false, Int);
        AnimTimer = NewField(0x2C, false, false, Int);
        CurrentFrame = NewField(0x30, false, false, Int);
        TicksPerFrame = NewField(0x34, false, false, Int);
        FrameCount = NewField(0x38, false, false, Int);
        CurrentTick = NewField(0x3C, false, false, Int);

        HP = NewField(0x40, false, false, Int);
        MaxHP = NewField(0x44, false, false, Bool);
        Offensive = NewField(0x48, false, false, Bool);
        VanishTimer = NewField(0x4C, false, false, Int);
        DetonationTimer = NewField(0x50, false, false, Int);
        ArmingTimer = NewField(0x54, false, false, Bool);
        ActionTimer = NewField(0x58, false, false, Int);
        ActionRate = NewField(0x5C, false, false, Int);
        MaxActionTimer = NewField(0x5C, false, false, Int);
        PlantRect = NewField(0x60, false, false, Rect);
        AttackRect = NewField(0x70, false, false, Rect);
        Target = NewField(0x80, false, false, Vec2);
        StartLane = NewField(0x88, false, false, Int);
        Particles = NewField(0x8C, true, true, "ParticleSystem");
        FireTimer = NewField(0x90, false, false, Int);
        
        BodyAnimation = NewField(0x94, false, false, Reanimation);
        HeadAnimation = NewField(0x98, false, false, Reanimation);
        Head2Animation = NewField(0x9C, false, false, Reanimation);
        Head3Animation = NewField(0xA0, false, false, Reanimation);
        BlinkAnimation = NewField(0xA4, false, false, Reanimation);
        LightAnimation = NewField(0xA8, false, false, Reanimation);
        SleepAnimation = NewField(0xAC, false, false, Reanimation);
        BlinkTimer = NewField(0xB0, false, false, Int);
        RecentlyEatenTimer = NewField(0xB4, false, false, Int);
        FlashTimer = NewField(0xB8, false, false, Int);
        GlowTimer = NewField(0xBC, false, false, Int);
        ShakeOffset = NewField(0xC0, false, false, TypeCasts.FVector2);
        TargetZombie = NewField(0x12C, true, true, "Zombie");
        WakingTimer = NewField(0x130, false, false, Int);
        BungeeState = NewField(0x134, false, false, Int);
        ImitaterType = NewField(0x138, false, false, Int);
        ZenGardenIndex = NewField(0x13C, false, false, Int);
        AnimationPing = NewField(0x140, false, false, Bool);
        Dead = NewField(0x141, false, false, Bool);
        Smashed = NewField(0x142, false, false, Bool);
        Asleep = NewField(0x143, false, false, Bool);
        InGame = NewField(0x144, false, false, Bool);
        Highlighted = NewField(0x145, false, false, Bool);

        Fire = PLANT_FIRE;
    },
    0x148,
    true,
    "GameObject"
);

local PlantSystem =
{
    PlantUpdating = PLANT_UPDATE;
    PlantFiring = PLANT_FIRING;
    PlantCreated = PLANT_NEW;
};
ENV.PlantSystem = PlantSystem;
ENV.LawnApp.PlantSystem = PlantSystem;

ENV.PLANT_UPDATE = nil;
ENV.PLANT_FIRING = nil;
ENV.PLANT_NEW = nil;
ENV.PLANT_FIRE = nil;