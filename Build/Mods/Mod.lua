--// Luna V0.2.2 \\--
print(LawnApp.WindowTitle);
LawnApp.WindowTitle = "Luna!";
print(LawnApp.WindowTitle);


local UIRoot = LawnApp.UIRoot;

local SpeedButton = UI.New("StoneButton", UIRoot);
local CurrentSpeed = 1;
local Speeds = {5, 1, 2};

SpeedButton.Text = "1x";
SpeedButton:ResizeToFit();

function SpeedButton:OnMouseDown()
    CurrentSpeed += 1;
    CurrentSpeed = (CurrentSpeed > #Speeds and 1) or CurrentSpeed;
    local Speed = Speeds[CurrentSpeed];
    self.Text = Speed .. "x";
    self:ResizeToFit();
    LawnApp.Speed = Speed;
end;

LawnApp.OnNewGame:Connect(function(Lawn)
    local Plant = Lawn:AddPlant("Imitater", 2, 0, "SnowPea");
    Plant.X += 100;
end);