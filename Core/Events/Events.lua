---@diagnostic disable: undefined-global
LunaClass.Register(
    "LunaEvent",
    {
        Name = LunaClass.NewField(0x0, true, false, LunaClass.TypeCasts.CArr);
        Connect = LUNA_EVENT_CONNECT;
        Disconnect = LUNA_EVENT_DISCONNECT;
        GetConnectedFunction = LUNA_EVENT_GET_FUNCTION;
        __tostring = function(self) return self.Name; end;
    },
    0x4
);

ENV.LUNA_EVENT_CONNECT = nil;
ENV.LUNA_EVENT_DISCONNECT = nil;
ENV.LUNA_EVENT_GET_FUNCTION = nil;