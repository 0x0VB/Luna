---@diagnostic disable: undefined-global
local X = LunaClass.NewField(0x0, false, false, LunaClass.TypeCasts.Float);
local Y = LunaClass.NewField(0x4, false, false, LunaClass.TypeCasts.Float);
local Z = LunaClass.NewField(0x8, false, false, LunaClass.TypeCasts.Float);
LunaClass.Register(
    "Vector3",
    {
        X = X; x = X;
        Y = Y; y = Y;
        Z = Z; z = Z;

        DistanceFrom = VEC3DIST;
        SetMagnitude = VEC3SMAG;
        DirectionFrom = VEC3DIR;
        Magnitude = VEC3MAG;
        Project = VEC3PROJ;
        Nudge = VEC3NUDGE;
        Normal = VEC3NORM;
        Rotate = VEC3ROT;
        Unit = VEC3UNIT;
        Lerp = VEC3LERP;

        __add = VEC3ADD;
        __sub = VEC3SUB;
        __mul = VEC3MUL;
        __div = VEC3DIV;
        __unm = function(self) return self:Copy():Inverse(); end;

        Inverse = function(self) self.X = -self.X; self.Y = -self.Y; self.Z = -self.Z; return self; end;
        Translate = function(self, X, Y, Z) return self + Vector3(X, Y, Z); end;
        ToInt2D = function(self) return IVector2(self.X, self.Y); end;
        To2D = function(self)  return FVector2(self.X, self.Y); end;

        GetRotated = function(self, ...) return self:Copy():Rotate(...); end;
        GetNudged = function(self, ...) return self:Copy():Nudge(...); end;
        GetLerped = function(self, ...) return self:Copy():Lerp(...); end;
        GetInversed = function(self) return self:Copy():Inverse(); end;

        __tostring = function(self)
            return "Vector3("..
            tostring(self.X)..", "..
            tostring(self.Y)..", "..
            tostring(self.Z)..")";
        end;
    },
    0xC,
    false
);

ENV.VEC3NUDGE = nil;
ENV.VEC3PROJ = nil;
ENV.VEC3NORM = nil;
ENV.VEC3DIST = nil;
ENV.VEC3UNIT = nil;
ENV.VEC3LERP = nil;
ENV.VEC3SMAG = nil;
ENV.VEC3DIR = nil;
ENV.VEC3MAG = nil;
ENV.VEC3ROT = nil;
ENV.VEC3ADD = nil;
ENV.VEC3SUB = nil;
ENV.VEC3MUL = nil;
ENV.VEC3DIV = nil;