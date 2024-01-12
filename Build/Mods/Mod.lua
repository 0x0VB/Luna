--// Luna V0.2.2 \\--
LawnApp.WindowTitle = "Luna!";
LawnApp.Speed = 5;
print(type(LawnApp));
local UIRoot = LawnApp.UIRoot;

local SpeedButton = UI.New("StoneButton", UIRoot);
local CurrentSpeed = 1;
local Speeds = {5, 1, 2};

SpeedButton.Text = "5x";
SpeedButton:ResizeToFit();

function SpeedButton:OnMouseDown()
    CurrentSpeed += 1;
    CurrentSpeed = (CurrentSpeed > #Speeds and 1) or CurrentSpeed;
    local Speed = Speeds[CurrentSpeed];
    self.Text = Speed .. "x";
    self:ResizeToFit();
    LawnApp.Speed = Speed;
end;

print("State");
print(Enum);
print(Enum.PlantState);
print(Enum.PlantState.Ready);
print(Enum.PlantState.Ready.Value);
print(Enum.PlantState.Ready.Name);

Plant.OnUpdate:Connect(function(Plant, Table)
    print(Plant.Type);
    print(Type(Plant));
    Table.Skip = true;
end);