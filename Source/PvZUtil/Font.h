#pragma once
struct Sexy::ActiveFontLayer
{
	FontLayer* mBaseFontLayer;
	Image* ScaledImage;
	bool OwnsImage;
	PopMap<char, IRect> ScaledCharImageRects;

	virtual ~ActiveFontLayer();
};


class Sexy::Font
{
public:
	int Ascent;
	int AscentPadding;
	int Height;
	int LineSpacingOffset;

	Font()
	{
		CONST DWORD Function = 0x586780;
		__asm
		{
			push this
			mov eax, this
			call Function
			pop this
		}
	}

#pragma region Virtual Functions
	virtual __thiscall ~Font();// 00
	virtual int GetAscent();// 04
	virtual int GetAscentPadding();// 08
	virtual int GetDescent();// 0C
	virtual int GetHeight();// 10
	virtual int GetLineSpacingOffset();// 14
	virtual int GetLineSpacing();// 18
	virtual int TextWidth(const PopString& Text);// 1C
	virtual int CharWidth(char Char);// 20
	virtual int CharWidthKern(char PrevChar, char Char);// 24
	virtual void DrawString(Graphics* G, int X, int Y, const PopString& Text, const Color& Color, const IRect& Clip);// 28
#pragma endregion
};

class Sexy::ImageFont : public Sexy::Font
{
public:
	FontData* FontData;
	int PointSize;
	PopVector<PopString> TagVector;
	bool ActivateAllLayers;
	bool ActiveListValid;
	PopList<Sexy::ActiveFontLayer> mActiveLayerList;
	double Scale;
	bool ForceScaledImagesWhite;

	ImageFont()
	{
		CONST DWORD Function = 0x58D010;
		__asm
		{
			push this
			call Function
			mov this, eax
		}
	}

#pragma region Virtual Functions
	virtual ImageFont* Duplicate();// 2C
	virtual void GenerateActiveFontLayers();// 30
	virtual void DrawStringEx(Graphics* G, int X, int Y, const PopString& Text, const Color& Color, const IRect* ClipRect, PopList<IRect>* DrawnAreas = NULL, int* OutWidth = NULL);// 34
	virtual void SetPointSize(int PointSize);// 38
	virtual int GetPointSize();// 3C
	virtual void SetScale(double NewScale);// 40
	virtual int GetDefaultPointSize();// 44
	virtual void AddTag(const PopString& TagName);// 48
	virtual void RemoveTag(const PopString& TagName);// 4C
	virtual bool HasTag(const PopString& TagName);// 50
	virtual PopString&& GetDefine(_Out_ const PopString&& ElementString, const PopString& Name);// 54
	virtual void Prepare();// 58
	virtual void WriteToCache(const PopString& FilePath, const PopString& GroupName);// 5C
#pragma endregion
};