--// Luna V0.2.1 Beta \\--
LawnApp.WindowTitle = "Luna!";
LawnApp.Speed = 2;

LawnApp.OnUpdate:Connect(function ()
    if (LawnApp.Age == 1000) then LawnApp:MessageBox("Test!"); end;
end);