#pragma once

#include "Definitions.h"
#include "UIRoot.h"

struct Sexy::Edge
{
	long double X;
	long double DX;
	int i;
	long double b;
};

struct Sexy::TriVertex
{
	float X;
	float Y;
	float U;
	float V;
	unsigned long Color;
};

struct Sexy::GraphicsState
{
	Sexy::Image* DestImage;
	FVector2 Translation;
	FVector2 Scale;
	FVector2 ScaleOrigin;
	IRect ClipRect;
	Color Color;
	Sexy::Font* Font;
	int DrawMode;
	bool ColorizeImages;
	bool FastStretch;
	bool WriteColoredText;
	bool LinearBlend;
	bool Is3D;
};

class Sexy::Graphics
{
public:
	virtual ~Graphics() = 0;

	GraphicsState State;
	Edge* PFActiveEdgeList;
	int PFNumActiveEdges;
	int PFNumVertices;
	PopList<GraphicsState> StateStack;

#pragma region Functions
	__thiscall Graphics(const Graphics& Old)
	{
		CONST DWORD Function = 0x5869B0;
		__asm
		{
			push ecx
			mov edi, this
			push Old
			call Function
			pop ecx
		}
	}
	__thiscall Graphics(Image* Dest)
	{
		CONST DWORD Function = 0x586A30;
		__asm
		{
			push ecx
			push ecx
			mov ecx, Dest
			call Function
			pop ecx
		}
	}
	void PushState()
	{
		CONST DWORD Function = 0x586B40;
		__asm
		{
			push this
			call Function
		}
	}
	void PopState()
	{
		CONST DWORD Function = 0x586BD0;
		__asm
		{
			mov edi, this
			call Function
		}
	}
	Graphics* __thiscall Create(Graphics* Old)
	{
		CONST DWORD Function = 0x586C30;
		__asm
		{
			push Old
			call Function
		}
	}
	void FillRect(int X, int Y, int W, int H)
	{
		CONST DWORD Function = 0x586D50;
		__asm
		{
			mov eax, this
			push H
			push W
			push Y
			push X
			call Function
		}
	}
	void FillRect(const IRect& Rect)
	{
		CONST DWORD Function = 0x586DC0;
		__asm
		{
			push this
			mov eax, Rect
			call Function
		}
	}
	void DrawRect(int X, int Y, int W, int H)
	{
		CONST DWORD Function = 0x586DE0;
		__asm
		{
			push H
			push W
			push Y
			push X
			mov eax, this
			call Function
		}
	}
	void DrawRect(const IRect& Rect)
	{
		CONST DWORD Function = 0x586EF0;
		__asm
		{
			push this
			mov eax, Rect
			call Function
		}
	}
	void DrawString(const PopString& String, int X, int Y)
	{
		CONST DWORD Function = 0x587120;
		__asm
		{
			mov eax, this
			push Y
			push X
			push String
			call Function
		}
	}
	void DrawImage(Image* Image, int X, int Y)
	{
		CONST DWORD Function = 0x587150;
		__asm
		{
			mov eax, this
			mov ebx, Image
			push Y
			push X
			call Function
		}
	}
	void DrawImage(const IRect& Source, Image* Image, int X, int Y)
	{
		CONST DWORD Function = 0x587270;
		__asm
		{
			mov ecx, this
			mov eax, Source
			push Y
			push X
			push Image
			call Function
		}
	}
	void DrawImageMirror(Image* Image, const IRect& Dest, const IRect& Source, bool Mirror)
	{
		CONST DWORD Function = 0x587490;
		__asm
		{
			mov eax, this
			mov ebx, Image
			mov edi, Dest
			push Source
			push Mirror
			call Function
		}
	}
	void DrawImage(Image* Image, int X, int Y, int W, int H)
	{
		CONST DWORD Function = 0x587520;
		__asm
		{
			mov eax, this
			mov edi, Image
			push H
			push W
			push Y
			push X
			call Function
		}
	}
	void DrawImage(Image* Image, const IRect& Dest, const IRect& Source)
	{
		CONST DWORD Function = 0x5875B0;
		__asm
		{
			mov eax, Dest
			push Source
			push Image
			call Function
		}
	}
	void DrawImageF(Image* Image, float X, float Y)
	{
		CONST DWORD Function = 0x587630;
		__asm
		{
			mov eax, this
			mov edx, Image
			push Y
			push X
			call Function
		}
	}
	void DrawImageF(Image* Image, float X, float Y, const IRect& Source)
	{
		CONST DWORD Function = 0x5876B0;
		__asm
		{
			mov eax, this
			push Source
			push Y
			push X
			push Image
			call Function
		}
	}
	void DrawTrianglesTex(Image* Texture, const TriVertex Vertices[][3], int TriNum)
	{
		CONST DWORD Function = 0x587710;
		__asm
		{
			mov eax, this
			push TriNum
			push Vertices
			push Texture
			call Function
		}
	}
	void ClearClipRect()
	{
		CONST DWORD Function = 0x587760;
		__asm { call Function }
	}
	void SetClipRect(int X, int Y, int W, int H)
	{
		CONST DWORD Function = 0x587790;
		__asm
		{
			mov esi, this
			push H
			push W
			push Y
			push X
			call Function
		}
	}
	void SetClipRect(const IRect& Clip)
	{
		CONST DWORD Function = 0x587820;
		__asm
		{
			mov esi, this
			mov eax, Clip
			call Function
		}
	}

#pragma endregion
};