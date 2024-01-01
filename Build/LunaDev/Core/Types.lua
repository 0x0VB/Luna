---@meta
---@class LunaClass
local LunaClass = {};

---Determines if this class belongs to a particular SubClass.
---@param SubClass SubClass
function LunaClass:IsA(SubClass) end;

---@enum (key) SubClass
local SubClass = {
    UIContainer = "SubClass";
    SexyAppBase = "SubClass";
    LunaBase = "SubClass";
    SexyApp = "SubClass";
    LawnApp = "SubClass";
    UIBase = "SubClass";
    UIRoot = "SubClass";
};