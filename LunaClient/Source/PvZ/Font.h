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

	Font() {};

#pragma region Virtual Functions
	virtual __thiscall ~Font(){};// 00
	virtual int GetAscent(){ return 0; };// 04
	virtual int GetAscentPadding() { return 0; };// 08
	virtual int GetDescent(){ return 0; };// 0C
	virtual int GetHeight(){ return 0; };// 10
	virtual int GetLineSpacingOffset(){ return 0; };// 14
	virtual int GetLineSpacing(){ return 0; };// 18
	virtual int TextWidth(const PopString& Text) { return 0; };// 1C
	virtual int CharWidth(char Char){ return 0; };// 20
	virtual int CharWidthKern(char PrevChar, char Char){ return 0; };// 24
	virtual void DrawString(Graphics* G, int X, int Y, const PopString& Text, const Color& Color, const IRect& Clip){};// 28
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
	ImageFont(Image* Image, PopString FontDataFile)
	{
		CONST DWORD Function = 0x58D280;
		__asm
		{
			push this
			push Image
			push FontDataFile
			call Function
		}
	}

#pragma region Virtual Functions
	virtual ImageFont* Duplicate(){};// 2C
	virtual void GenerateActiveFontLayers(){};// 30
	virtual void DrawStringEx(Graphics* G, int X, int Y, const PopString& Text, const Color& Color, const IRect* ClipRect, PopList<IRect>* DrawnAreas = NULL, int* OutWidth = NULL) {};// 34
	virtual void SetPointSize(int PointSize){};// 38
	virtual int GetPointSize(){ return 0; };// 3C
	virtual void SetScale(double NewScale) {};// 40
	virtual int GetDefaultPointSize(){ return 0; };// 44
	virtual void AddTag(const PopString& TagName){};// 48
	virtual void RemoveTag(const PopString& TagName){};// 4C
	virtual bool HasTag(const PopString& TagName){};// 50
	virtual PopString&& GetDefine(_Out_ const PopString&& ElementString, const PopString& Name) {};// 54
	virtual void Prepare(){};// 58
	virtual void WriteToCache(const PopString& FilePath, const PopString& GroupName){};// 5C
#pragma endregion
};

class Sexy::SysFont : public Sexy::Font
{
public:
	HFONT Font;
	SexyAppBase* App;
	bool DrawShadow;
	bool Bold;

	SysFont(PopString TypeFace, int PointSize, bool Bold, bool Italic, bool Underline)
	{
		CONST DWORD Function = 0x599C30;
		__asm
		{
			mov eax, this
			push TypeFace
			mov edx, PointSize
			push Bold
			push Italic
			push Underline
			call Function
		}
	}
};