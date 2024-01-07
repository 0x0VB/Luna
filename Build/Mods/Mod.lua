--// Luna V0.2.2 \\--
LawnApp.WindowTitle = "Luna!";
LawnApp.Speed = 2;
local UIRoot = LawnApp.UIRoot;
local TheButton = UI.New("StoneButton", UIRoot);
local ButtonCount = 1;
TheButton.Dirty = true;
print(TheButton.Parent);

function TheButton:OnMouseDown(X, Y, Button, DoubleClick)
    local ThisCount = ButtonCount;
    local NB = UI.New("UIButton");-- Create new button
    local Img = Luna:LoadImage("images/DiscordButton");
    --NB.NormalImage = Img;
    NB.Text = "New Button " .. ButtonCount;-- Set its text
    ButtonCount += 1;-- Add 1 to the button count
    NB.Parent = UIRoot;
    NB.Position = Vector2(math.random(0, 600), math.random(0, 550));-- Give it a random position
    NB:PutBehind(self);
    
    function NB:OnMouseDown()
        print(ThisCount);
    end;

    print(LawnApp.WindowBounds);
    LawnApp.WindowTitle ..= "!";
    LawnApp.WindowBounds += Rect(10, 10, 0, 0);
    --Luna:PromptDiscordInvite("BVcCAFXe4B");
end;
