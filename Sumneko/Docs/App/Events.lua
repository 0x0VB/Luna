---@meta

---Halts game execution for the given amount of milliseconds
---@param Milliseconds integer
function Sleep(Milliseconds) end;

---@class LunaEvent: LunaClass
---@field GetConnectedFunction fun(self: LunaEvent): function Returns the function connected to this event.
---@field Name string The name of this event.
local LunaEvent = {};

---Connects the given function to this event and disconnects the previous one.
---@param Function function
function LunaEvent:Connect(Function) end;

---Disconnects the connected function from this event if it exists.
function LunaEvent:Disconnect() end;

---Returns the function currently connected to this event.
---@return function
function LunaEvent:GetConnectedFunction() end;