---@diagnostic disable: undefined-global
local X = LunaClass.NewField(0, false, false, LunaClass.TypeCasts.Int);
local Y = LunaClass.NewField(4, false, false, LunaClass.TypeCasts.Int);
LunaClass.Register(
    "IVector2",
    {
        X = X; x = X;
        Y = Y; y = Y;

        DirectionTo = IV2DIRTO;
        DistanceFrom = IV2DIST;
        SetMagnitude = IV2SMAG;
        Magnitude = IV2MAG;
        Normal = IV2NORM;
        Nudge = IV2NUDGE;
        Rotate = IV2ROT;
        Unit = IV2UNIT;
        Lerp = IV2LERP;
        GetInverse = function(self, ...) return IVector2(-self.X, -self.Y); end;

        __mul = IV2MUL;
        __div = IV2DIV;
        __add = IV2ADD;
        __sub = IV2SUB;
        __unm = function(self) return IVector2(-self.X, -self.Y); end;
    },
    0x8,
    false,
    "FVector2"
);

ENV.IV2NUDGE = nil;
ENV.IV2DIRTO = nil;
ENV.IV2SMAG = nil;
ENV.IV2NORM = nil;
ENV.IV2UNIT = nil;
ENV.IV2DIST = nil;
ENV.IV2LERP = nil;
ENV.IV2ROT = nil;
ENV.IV2MAG = nil;
ENV.IV2MUL = nil;
ENV.IV2DIV = nil;
ENV.IV2ADD = nil;
ENV.IV2SUB = nil;