--// Luna V0.2.2 \\--
LawnApp.WindowTitle = "Luna!";
LawnApp.Speed = 2;
local UIRoot = LawnApp.UIRoot;
local A = UI.New("StoneButton");

function A:OnMouseDown(X, Y, Button, DoubleClick)
    if (Button == 1) then
        A.Text ..= "!";
    end;
end;

LawnApp.OnUpdate:Connect(function ()
    if (LawnApp.Loaded) then
        A:ResizeToFit();
        A.Parent = UIRoot;
    end;
end);