---@meta
---@class UIRoot: UIContainer
---@field DefaultTab UIElement
---@field CurrentGraphics Graphics
---@field LawnApp LawnApp
---@field Image MemoryImage
---@field TransientImage MemoryImage
---@field LastHadTransients boolean
---@field PopupCommandElement UIElement
---@field HasFocus boolean
---@field FocusedElement UIElement
---@field LastDownElement UIElement
---@field HoveredElement UIElement
---@field BaseModalElement UIElement
---@field MouseDest Rect
---@field MouseSource Rect
---@field MouseIn boolean
---@field MousePosition Vector2
---@field MouseX integer
---@field MouseY integer
---@field LastInputTimeStamp integer
---@field LastDownButtonID integer
---@field ElementFlags integer
---@field KeyDown KeyDown
---@field KeyUp KeyUp
---@field MouseDown MouseDown
---@field MouseUp MouseUp
---@field MouseWheel MouseWheel
local UIRoot = {};

---Returns `true` if the given key is currently held down.
---@param KeyCode KeyCode
---@return boolean
function UIRoot:IsKeyDown(KeyCode) return true; end;

---Returns `true` if the given MouseButton is currently held down.
---@param Button MouseButton
---@return boolean
function UIRoot:IsMouseButtonDown(Button) return true; end;

---@class KeyDown: LunaEvent
local KeyDown = {};
---Fired whenever a key is pressed when the game window is focused.
---@param Function fun(Key: KeyCode)
function KeyDown:Connect(Function) end;

---@class KeyUp: LunaEvent
local KeyUp = {};
---Fired whenever a key is released when the game window is focused.
---@param Function fun(Key: KeyCode)
function KeyUp:Connect(Function) end;

---@class MouseDown: LunaEvent
local MouseDown = {};
---Fired whenever a mouse button is pressed on the game window.
---@param Function fun(PressCode: MousePress, X: integer, Y: integer)
function MouseDown:Connect(Function) end;

---@class MouseUp: LunaEvent
local MouseUp = {};
---Fired whenever a mouse button is released on the game window.
---@param Function fun(PressCode: MousePress, X: integer, Y: integer)
function MouseUp:Connect(Function) end;

---@class MouseWheel: LunaEvent
local MouseWheel = {};
---Fired whenever the mouse wheel is scrolled while the game window is focused. Delta represents the direction of scrolling and the amount.
---@param Function fun(Delta: integer)
function MouseWheel:Connect(Function) end;