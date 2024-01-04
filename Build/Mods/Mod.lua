--// Luna V0.2.2 \\--
LawnApp.WindowTitle = "Luna!";
LawnApp.Speed = 2;
local Root = LawnApp.UIRoot;
LawnApp.OnUpdate:Connect(function ()
    local Children = LawnApp.UIRoot:GetChildren();
    for _, Element in pairs(Children) do
        Element.InitPos = Element.InitPos or Element.Position;
        Element.Position = Element.Position + Vector2(math.random(-2, 2), math.random(-2, 2));
    end;
end)