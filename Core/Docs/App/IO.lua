---@meta

---Outputs its parameters into the console.
---@param ... any
function print(...) end;

---Outputs its parameters as orange text to the console.
---@param ... any
function warn(...) end;

---Outputs its parameters as blue text to the console.
---@param ... any
function info(...) end;

---Outputs its parameters as violet text to the console. Used by internal Luna functions to indicate that this message is from Luna's core.
---@param ... any
function core(...) end;