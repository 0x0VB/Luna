---@diagnostic disable: undefined-global
local X = LunaClass.NewField(0, false, false, LunaClass.TypeCasts.Float);
local Y = LunaClass.NewField(4, false, false, LunaClass.TypeCasts.Float);
LunaClass.Register(
    "FVector2",
    {
        X = X; x = X;
        Y = Y; y = Y;

        DirectionTo = FV2DIRTO;
        DistanceFrom = FV2DIST;
        SetMagnitude = FV2SMAG;
        Magnitude = FV2MAG;
        Normal = FV2NORM;
        Nudge = FV2NUDGE;
        Rotate = FV2ROT;
        Unit = FV2UNIT;
        Lerp = FV2LERP;

        ToInt = function(self) return IVector2(self.X, self.Y); end;
        To3D = function(self) return Vector3(self.X, 0, self.Y); end;
        ToIVector2 = function(self) return IVector2(self.X, self.Y); end;
        GetLerped = function(self, ...) return self:Copy():Lerp(...);  end;
        GetNudged = function(self, ...) return self:Copy():Nudge(...); end;
        GetRotated = function(self, ...) return self:Copy():Rotate(...); end;
        GetInverse = function(self, ...) return FVector2(-self.X, -self.Y); end;
        Inverse = function(self) self.X = - self.X; self.Y = - self.Y; return self; end;
        Translate = function(self, X, Y) self.X = self.X + (X or 0); self.Y = self.Y + (Y or 0); return self; end;
        GetTranslated = function(self, X, Y) return self:Copy():Translate(); end;

        __mul = FV2MUL;
        __div = FV2DIV;
        __add = FV2ADD;
        __sub = FV2SUB;
        __unm = function(self) return FVector2(-self.X, -self.Y); end;
        __tostring = function(self)
            return type(self).."("..
            tostring(self.X) .. ", "..
            tostring(self.Y)..")";
        end;
    },
    0x8
);

ENV.FV2NUDGE = nil;
ENV.FV2DIRTO = nil;
ENV.FV2SMAG = nil;
ENV.FV2NORM = nil;
ENV.FV2UNIT = nil;
ENV.FV2DIST = nil;
ENV.FV2LERP = nil;
ENV.FV2ROT = nil;
ENV.FV2MAG = nil;
ENV.FV2MUL = nil;
ENV.FV2DIV = nil;
ENV.FV2ADD = nil;
ENV.FV2SUB = nil;