#pragma once
class Sexy::UIButton : public Sexy::UIElement
{
public:
#pragma region Fields
	int ID;
	PopString* Label;
	int LabelJustify;
	Font* Font;
	Image* ButtonImage;
	Image* OverImage;
	Image* DownImage;
	Image* DisabledImage;
	IRect NormalRect;
	IRect OverRect;
	IRect DownRect;
	IRect DisabledRect;
	bool Inverted;
	bool NoDraw;
	bool FrameNoDraw;
	ButtonListener* Listener;
	double OverAlpha;
	double OverAlphaSpeed;
	double OverAlphaFadeSpeed;
#pragma endregion

#pragma region Virtual Functions
	virtual ~UIButton();
	virtual void DrawButtonImage(Graphics* G, Image* Image, IRect* Rect, int X, int Y);// 118
	virtual void SetFont(Sexy::Font* NewFont);// 11C
	virtual bool IsButtonDown();// 120
#pragma endregion
};