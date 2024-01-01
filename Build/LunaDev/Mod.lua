--// Luna V0.2.1 Beta \\--
LawnApp.WindowTitle = "Luna!";
LawnApp.Speed = 2;
local Root = LawnApp.UIRoot;
LawnApp.OnUpdate:Connect(function ()
    local Children = LawnApp.UIRoot:GetChildren();
    for _, Element in pairs(Children) do
        Element.InitPos = Element.InitPos or Element.Position;
        Color();
    end;
end)