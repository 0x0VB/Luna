#pragma once
#include "Definitions.h"

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

	Font();

#pragma region Virtual Functions
	virtual __thiscall ~Font() {};// 00
	virtual int GetAscent() = 0;// 04
	virtual int GetAscentPadding()  = 0;// 08
	virtual int GetDescent() = 0;// 0C
	virtual int GetHeight() = 0;// 10
	virtual int GetLineSpacingOffset() = 0;// 14
	virtual int GetLineSpacing() = 0;// 18
	virtual int TextWidth(const PopString& Text) = 0;// 1C
	virtual int CharWidth(char Char) = 0;// 20
	virtual int CharWidthKern(char PrevChar, char Char) = 0;// 24
	virtual void DrawString(Graphics* G, int X, int Y, const PopString& Text, const Color& Color, const IRect& Clip) = 0;// 28
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

	ImageFont();

#pragma region Virtual Functions
	virtual ImageFont* Duplicate() = 0;// 2C
	virtual void GenerateActiveFontLayers() = 0;// 30
	virtual void DrawStringEx(Graphics* G, int X, int Y, const PopString& Text, const Color& Color, const IRect* ClipRect, PopList<IRect>* DrawnAreas = NULL, int* OutWidth = NULL)  = 0;// 34
	virtual void SetPointSize(int PointSize) = 0;// 38
	virtual int GetPointSize() = 0;// 3C
	virtual void SetScale(double NewScale)  = 0;// 40
	virtual int GetDefaultPointSize() = 0;// 44
	virtual void AddTag(const PopString& TagName) = 0;// 48
	virtual void RemoveTag(const PopString& TagName) = 0;// 4C
	virtual bool HasTag(const PopString& TagName) = 0;// 50
	virtual PopString&& GetDefine(_Out_ const PopString&& ElementString, const PopString& Name)  = 0;// 54
	virtual void Prepare() = 0;// 58
	virtual void WriteToCache(const PopString& FilePath, const PopString& GroupName) = 0;// 5C
#pragma endregion
};