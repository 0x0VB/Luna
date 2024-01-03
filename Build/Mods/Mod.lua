--// Luna V0.2.2 \\--
print(function() end);
print(LawnApp);
print(LawnApp.WindowTitle);
LawnApp.WindowTitle = "Luna!";
LawnApp.Speed = 2;
LawnApp.OnUpdate:Connect(function()
    print("A");
    for _, V in pairs(LawnApp.UIRoot:GetChildren()) do
        V.Position += Vector2(math.random(-2, 2), math.random(-2, 2));
    end;
end);
print("Passed!");