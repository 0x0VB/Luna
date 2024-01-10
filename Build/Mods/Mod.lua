--// Luna V0.2.2 \\--
LawnApp.WindowTitle = "Luna!";
local UIRoot = LawnApp.UIRoot;

local SpeedButton = UI.New("StoneButton", UIRoot);
local CurrentSpeed = 1;
local Speeds = {1, 5, 10, 0.5, 0.25};

SpeedButton.Text = "1x";
SpeedButton:ResizeToFit();

function SpeedButton:OnMouseDown()
    CurrentSpeed += 1;
    CurrentSpeed = (CurrentSpeed > #Speeds and 1) or CurrentSpeed;
    local Speed = Speeds[CurrentSpeed];
    self.Text = Speed .. "x";
    self:ResizeToFit();
    LawnApp.Speed = Speed;
    print(LawnApp.Lawn);
end;

local GetSun = UI.New("StoneButton", UIRoot);
GetSun.Text = "Get Sun";
GetSun.Bounds = Rect(0, SpeedButton.Bounds.H);
GetSun:ResizeToFit();
function GetSun:OnMouseDown()
    LawnApp.Lawn:Test();
    LawnApp.Lawn.Sun += 500;
end;