--// Luna V0.2.2 \\--
LawnApp.WindowTitle = "Luna!";
LawnApp.Speed = 2;
local Root = LawnApp.UIRoot;
LawnApp.OnUpdate:Connect(function ()
    local Children = LawnApp.UIRoot:GetChildren();
    if (#Children >= 2) then
        Children[2].Parent = nil;
    end;
end);