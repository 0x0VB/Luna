--// Luna V0.2.2 \\--
--#region SpeedButton code, don't mind this
LawnApp.WindowTitle = "Luna!";
local UIRoot = LawnApp.UIRoot;

local SpeedButton = UI.New("StoneButton", UIRoot);
local CurrentSpeed = 1;
local Speeds = {1, 2, 5};

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

LawnApp.FreePlantingCheat = true;
Plant.OnEaten:Connect(function(Plant, Zombie)-- When a plant is eaten,
    local Grave = Plant:SpawnGrave();-- Spawn a grave at its location and save the grave in the variable "Grave"
    Grave:SpawnZombie(Zombie.Type);-- Then spawn a zombie from the grave, with the same type as the zombie that ate the plant.
end);

Zombie.OnDeath:Connect(function(Zombie)
    Zombie:SpawnGrave();
end);