---@meta
---@class UIContainer: LunaClass
---@field UIRoot UIRoot
---@field Parent UIContainer
---@field NoAutoDestroy boolean
---@field Dirty boolean
---@field Bounds Rect
---@field Size IVector2
---@field HasAlpha boolean
---@field ClipToBounds boolean
---@field Priority integer
---@field ZIndex integer
local UIContainer = {};

---Destroys this UIElement and all of its children unless `DestroyChildren` is false.
---@param DestroyChildren boolean?
function UIContainer:Destroy(DestroyChildren) end;

---Removes all of this element's children and destroys them if `Destroy` is true. If `Recursive` is true, it clears all descendants.
---@param Destroy boolean?
---@param Recursive boolean?
function UIContainer:ClearChildren(Destroy, Recursive) end;
function UIContainer:BringToFront() end;
function UIContainer:BringToBack() end;

---Retrieves and returns all children of this UIElement.
---@return UIElement[]
function UIContainer:GetChildren() return {}; end;

---Returns `true` if the given UIContainer intersects this one.
---@param Other UIContainer
---@return boolean
function UIContainer:Intersects(Other) return true; end;

---@param Child UIElement
---@return UIElement
function UIContainer:AddChild(Child) return Child; end;

---Returns `true` if the given UIElement is a child of this one.
---@param Child UIElement
---@return boolean
function UIContainer:Contains(Child) return true; end;

---Removes the given element from this UIContainer. If `Destroy` is true, it also destroys the child.
---@param Child UIElement
---@param Destroy boolean?
function UIContainer:RemoveChild(Child, Destroy) end;

---Returns true if this UIElement is behind `Other`.
---@param Other UIElement
---@return boolean
function UIContainer:IsBehind(Other) return true; end;

---Places this UIElement in fron of `Other`. If the elements do not share the same parent, Luna will put `Other` in this 
---element's parent and give it the same ZIndex.
---@param Other UIElement
function UIContainer:PutInFront(Other) end;

---Puts this UIElement behind `Other`. If the elements do not share the same parent, Luna will put `Other` in this 
---element's parent and give it the same ZIndex.
---@param Other UIElement
function UIContainer:PutBehind(Other) end;

---Gets the position of this UIElement relative to the game window as opposed to relative to its parent.
---@return IVector2
function UIContainer:GetAbsolutePosition() return IVector2(); end;

---Gets the Index'th child in this element. Returns nil if there is no such child.
---@param Index integer?
---@return UIElement
function UIContainer:GetChild(Index) return self:GetChildren()[Index]; end;


---@class UIElement: UIContainer
---@field Visible boolean
---@field MouseVisible boolean
---@field Disabled boolean
---@field HasFocus boolean
---@field IsDown boolean
---@field Hovered boolean
---@field HasTransparencies boolean
---@field Padding Pad
---@field WantsFocus boolean
---@field Prev UIElement
---@field Next UIElement