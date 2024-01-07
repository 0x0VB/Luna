#pragma once
#include "Definitions.h"
class Sexy::Image
{
public:
	bool Drawn;
	PopString FilePath;
	IVector2 Size;
	int RowCount;
	int ColCount;
	AnimInfo* AnimInfo;

	virtual ~Image();// 00
	virtual bool PolyFill3D(IVector2* Vertices, int VertexCount, IRect* ClipRect, Color* Color, int DrawMode, int Tx, int Ty, bool Convex);// 04
	virtual void FillRect(IRect* Rect, Color* Color, int DrawMode);// 08
	virtual void DrawRect(IRect* Rect, Color* Color, int DrawMode);// 0C
	virtual void ClearRect(IRect* Rect);// 10
	virtual void DrawLine(double Sx, double Sy, double Ex, double Ey, Color* Color, int DrawMode);// 14
	virtual void DrawLineAA(double Sx, double Sy, double Ex, double Ey, Color* Color, int DrawMode);// 18
	virtual void FillScanLines(Span* Spans, int SpanCount, Color* Color, int DrawMode);// 1C
	virtual void FillScanLinesWithCoverage(Span* Spans, int SpanCount, Color* Color, int DrawMode, char* Coverage, int Cx, int Cy, int Cw, int Ch);// 20
	virtual void DrawImage(Image* Other, int X, int Y, IRect* Source, Color* Color, int DrawMode);// 24
};

class Sexy::MemoryImage : public Sexy::Image
{
public:
	unsigned long* Bits;
	int BitsChangedCount;
	void* D3DData;
	unsigned long D3DFlags;
	unsigned long* ColorTable;
	unsigned char* ColorIndices;
	bool ForcedMode;
	bool HasTrans;
	bool HasAlpha;
	bool IsVolatile;
	bool PurgeBits;
	bool WantPal;
	unsigned long* NativeAlphaData;
	unsigned char* RLAlphaData;
	unsigned char* RLAdditiveData;
	bool BitsChanged;
	SexyAppBase* App;
};

class Sexy::DDImage : public Sexy::MemoryImage
{
public:
	DDInterface* DDInterface;
	IDirectDrawSurface* Surface;
	bool SurfaceSet;
	bool NoLock;
	bool VideoMemory;
	bool FirstPixelTrans;
	bool WantDDInterface;
	bool DrawToBits;
	int LockCount;
	_DDSURFACEDESC LockedSurfaceDesc;
};