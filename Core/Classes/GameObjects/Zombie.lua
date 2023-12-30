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
    "Zombie",
    {
        ZombieType = NewField(0x24, false, false, Int);
        Phase = NewField(0x28, false, false, Int);
        Position = NewField(0x2C, false, false, FVector2);
        VelocityX = NewField(0x34, false, false, Int);
        AnimCounter = NewField(0x38, false, false, Int);
        GroanTimer = NewField(0x3C, false, false, Int);
        AnimTicksPerFrame = NewField(0x40, false, false, Int);
        AnimTicks = NewField(0x44, false, false, Int);
        CurrentTick = NewField(0x48, false, false, Int);
        PreviousTick = NewField(0x4C, false, false, Int);
        IsVariant = NewField(0x50, false, false, Bool);
        IsEating = NewField(0x51, false, false, Bool);
        Variant = NewField(0x52, false, false, Word);

        TookDamageTimer = NewField(0x54, false, false, Int);
        ShieldTookDamageTimer = NewField(0x58, false, false, Int);
        ShieldRecoilTimer = NewField(0x5C, false, false, Int);
        Age = NewField(0x60, false, false, Int);
        ZombieHeight = NewField(0x64, false, false, Int);
        PhaseTimer = NewField(0x68, false, false, Int);
        SourceWave = NewField(0x6C, false, false, Int);
        DroppedLoot = NewField(0x70, false, false, Bool);

        Fade = NewField(0x74, false, false, Int);
        FlatTires = NewField(0x78, false, false, Bool);
        UsedLadderAt = NewField(0x7C, false, false, Int);
        TargetColumn = NewField(0x80, false, false, Int);
        Altitude = NewField(0x84, false, false, Float);
        HitUmbrella = NewField(0x88, false, false, Bool);
        ZombieBounds = NewField(0x8C, false, false, Rect);
        AttackBounds = NewField(0x9C, false, false, Rect);
        
        ChilledTimer = NewField(0xAC, false, false, Int);
        ButteredTimer = NewField(0xB0, false, false, Int);
        FrozenTimer = NewField(0xB4, false, false, Int);
        Hypnotized = NewField(0xB8, false, false, Bool);
        BlowingAway = NewField(0xB9, false, false, Bool);
        HasHead = NewField(0xBA, false, false, Bool);
        HasArm = NewField(0xBB, false, false, Bool);
        HasObject = NewField(0xBC, false, false, Bool);
        InPool = NewField(0xBD, false, false, Bool);
        OnHighGround = NewField(0xBC, false, false, Bool);
        YuckyFace = NewField(0xBF, false, false, Bool);
        YuckyFaceTimer = NewField(0xC0, false, false, Int);
        
        HelmetType = NewField(0xC4, false, false, Int);
        BodyHP = NewField(0xC8, false, false, Int);
        BodyMaxHP = NewField(0xCC, false, false, Int);
        HelmetHP = NewField(0xD0, false, false, Int);
        HelmetMaxHP = NewField(0xD4, false, false, Int);
        ShieldType = NewField(0xD8, false, false, Int);
        ShieldHP = NewField(0xDC, false, false, Int);
        ShieldMaxHP = NewField(0xE0, false, false, Int);
        FlyingHP = NewField(0xE4, false, false, Int);
        FlyingMaxHP = NewField(0xE8, false, false, Int);
        Dead = NewField(0xEC, false, false, Bool);

        RelatedZombie = NewField(0xF0, true, true, "Zombie");
        FrontFollower = NewField(0xF4, true, true, "Zombie");
        RightFollower = NewField(0xF8, true, true, "Zombie");
        BackFollower = NewField(0xFC, true, true, "Zombie");
        LeftFollower = NewField(0x100, true, true, "Zombie");

        PlayingSong = NewField(0x104, false, false, Bool);
        ParticleOffset = NewField(0x108, false, false, FVector2);
        Attachment = NewField(0x110, false, false, Attachment);
        SummonTimer = NewField(0x114, false, false, Int);
        BodyAnimation = NewField(0x118, false, false, Reanimation);
        Scale = NewField(0x11C, false, false, Float);
        VelocityZ = NewField(0x120, false, false, Float);
        OriginalAnimationRate = NewField(0x124, false, false, Float);
        TargetPlant = NewField(0x128, true, true, "Plant");
        BossMode = NewField(0x12C, false, false, Int);
        TargetLane = NewField(0x130, false, false, Int);
        BossBungeeTimer = NewField(0x134, false, false, Int);
        BossStompTimer = NewField(0x138, false, false, Int);
        BossVulnerableTimer = NewField(0x13C, false, false, Int);
        BossBall = NewField(0x140, false, false, Reanimation);
        SpecialHead = NewField(0x144, false, false, Reanimation);
        BossBallLane = NewField(0x148, false, false, Int);
        IsFireball = NewField(0x14C, false, false, Bool);
        MowedAnimation = NewField(0x150, false, false, Reanimation);
        LastPortalX = NewField(0x154, false, false, Int);

        TakeDamage = ZOM_TAKEDMG;
    },
    0x158,
    true,
    "GameObject"
);

local ZombieSystem =
{
    ZombieCreated = ZOM_NEW;
    ZombieUpdating = ZOM_UPDATE;
    GetZombies = ZOM_GETALL;
};
ENV.LawnApp.ZombieSystem = ZombieSystem;
ENV.ZombieSystem = LawnApp.ZombieSystem;

ENV.ZOM_TAKEDMG = nil;
ENV.ZOM_UPDATE = nil;
ENV.ZOM_GETALL = nil;
ENV.ZOM_NEW = nil;

return ZombieSystem;