--// Luna V0.2.2 \\--
--#region SpeedButton stuff, don't mind this
LawnApp.WindowTitle = "Luna!";
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
--#endregion

