---@diagnostic disable: undefined-global
---@meta

local W = LunaClass.NewField(0x8, false, false, LunaClass.TypeCasts.Int);
local H = LunaClass.NewField(0xC, false, false, LunaClass.TypeCasts.Int);
LunaClass.Register(
    "Rect",
    {
        W = W; Width = W; w = W;
        H = H; Height = H; h = H;
        Size = LunaClass.NewField(0x8, false, true, "IVector2");

        Area = RECTAREA;
        Lerp = RECTLERP;
        Center = RECTCENT;
        GetArea = RECTAREA;
        Contains = RECTCONT;
        ReCenter = RECTRECEN;
        Intersects = RECTINTR;

        GetReCentered = function(self, ...) return self:Copy():ReCenter(...); end;

        __add = RECTADD;
        __sub = RECTSUB;
        __mul = RECTMUL;
        __div = RECTDIV;
        __unm = function(self) return Rect(-self.X, -self.Y, -self.W, -self.H); end;
        __tostring = function(self)
            return "Rect("..
            tostring(self.X)..", "..
            tostring(self.Y)..", "..
            tostring(self.W)..", "..
            tostring(self.H)..")";
        end;
    },
    0x10,
    false,
    "IVector2"
);

ENV.RECTRECEN = nil;
ENV.RECTAREA = nil;
ENV.RECTLERP = nil;
ENV.RECTAREA = nil;
ENV.RECTCONT = nil;
ENV.RECTINTR = nil;
ENV.RECTCENT = nil;
ENV.RECTADD = nil;
ENV.RECTSUB = nil;
ENV.RECTMUL = nil;
ENV.RECTDIV = nil;