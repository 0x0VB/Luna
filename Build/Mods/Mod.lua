--// Luna V0.2.2 \\--
LawnApp.WindowTitle = "Luna!";

LawnApp.OnUpdate:Connect(function()
    for _, V in pairs(LawnApp.UIRoot:GetChildren()) do
        V.Position += Vector2(math.random(-2, 2), math.random(-2, 2));
    end;
end);