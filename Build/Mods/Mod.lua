--// Luna V0.2.2 \\--
print(Luna.GetLawnApp)
local LawnApp = Luna:GetLawnApp();
LawnApp.OnUpdate:Connect(function()
    print(LawnApp.Age)
end);