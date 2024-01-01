---@meta
---@class LunaEvent
local LunaEvent = {}

---Connects the given function to this event.
---@param Function function
function LunaEvent:Connect(Function) end;

---Disconnects the given function from this event if it is connected. Does not throw an error if it is not connected.
---@param Function function
function LunaEvent:Disconnect(Function) end;

---Disconnects all connected functions from this event.
function LunaEvent:DisconnectAll() end;

---Calls this event with the given parameters.
---@param ... any
function LunaEvent:Call(...) end;