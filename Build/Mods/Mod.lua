--// Luna V0.2.2 \\--
print(function() end);
print(LawnApp);
print(LawnApp.WindowTitle);
print(LawnApp.OnUpdate)
LawnApp.WindowTitle = "Luna!";
LawnApp.Speed = 2;
LawnApp.OnUpdate:Connect(function()
    print(LawnApp.Age)
end);
print("Passed!");