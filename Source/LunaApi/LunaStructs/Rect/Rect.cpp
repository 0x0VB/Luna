#include "stdafx.h"
#include "Rect.h"

#include "LunaApi/LunaStructs/Vector2/Vector2.h"

#include "LunaApi/LunaUtil/LunaUtil.h"
#include "LunaApi/LunaIO/LunaIO.h"
#include "Luna.h"

#pragma region Struct Functions
template <typename T>
void Rect<T>::PushPosition() { NewVector2(X, Y); }
template <typename T>
void Rect<T>::PushSize() { NewVector2(W, H); }
template <typename T>
void Rect<T>::Push() { NewRect(X, Y, W, H); }
#pragma endregion

#pragma region C++ Functions
IRect GetRect(int Idx)
{
	AssertType(Idx, "Rect", "arg#" + std::to_string(Idx));
	return *(IRect*)lua_touserdata(LUNA_STATE, Idx);
}
IRect* NewRect(int X, int Y, int W, int H)
{
	auto New = (IRect*)lua_newuserdata(LUNA_STATE, sizeof(IRect));
	LunaUtil::Local("RectMeta");
	lua_setmetatable(LUNA_STATE, -2);

	New->X = X;
	New->Y = Y;
	New->W = W;
	New->H = H;

	return New;
}
IRect* GetRectSelf() { return (IRect*)lua_touserdata(LUNA_STATE, 1); }
#pragma endregion

#pragma region Lua Functions
int Luna::Structs::Rect::Constructor(lua_State* L)
{
	auto X = GetInt(1);
	auto Y = GetInt(2);
	auto W = GetInt(3);
	auto H = GetInt(4);
	NewRect(X, Y, W, H);
	return 1;
}

int Luna::Structs::Rect::GetIntersection(lua_State* L)
{
	auto self = GetRect(1);
	auto Other = GetRect(2);
	self.GetIntersection(Other).Push();
	return 1;
}
int Luna::Structs::Rect::SetPosition(lua_State* L)
{
	auto self = GetRect(1);
	auto NewPos = GetVector2(2).ToInt();
	self.SetPosition(NewPos).Push();
	return 1;
}
int Luna::Structs::Rect::Intersects(lua_State* L)
{
	auto self = GetRect(1);
	auto Other = GetRect(2);
	lua_pushboolean(L, self.Intersects(Other));
	return 1;
}
int Luna::Structs::Rect::GetCenter(lua_State* L)
{
	auto self = GetRect(1);
	self.GetCenter().Push();
	return 1;
}
int Luna::Structs::Rect::SetCenter(lua_State* L)
{
	AssertType(2, "Vector2", "NewCenter");
	auto self = GetRect(1);
	auto NewCenter = GetVector2(2);
	self.SetCenter(NewCenter.ToInt()).Push();
	return 1;
}
int Luna::Structs::Rect::Contains(lua_State* L)
{
	std::string OType = LunaUtil::Type(2);
	auto self = GetRect(1);
	
	if (OType == "Rect")
	{
		auto Other = GetRect(2);
		lua_pushboolean(L, self.Contains(Other));
	}
	else if (OType == "Vector2")
	{
		auto Other = GetVector2(2).ToInt();
		lua_pushboolean(L, self.Contains(Other));
	}
	else LunaIO::ThrowError("Expected a Rect or Vector2 value for arg#2, got " + OType + ".");

	return 1;
}
int Luna::Structs::Rect::GetArea(lua_State* L)
{
	auto self = GetRect(1);
	lua_pushinteger(L, self.GetArea());
	return 1;
}
int Luna::Structs::Rect::SetSize(lua_State* L)
{
	auto self = GetRect(1);
	auto NewSize = GetVector2(2).ToInt();
	self.SetSize(NewSize).Push();
	return 1;
}
int Luna::Structs::Rect::Lerp(lua_State* L)
{
	auto self = GetRect(1);
	auto Other = GetRect(2);
	auto Alpha = GetFloat(3, 0.5);
	self.Lerp(Other, Alpha).Push();
	return 1;
}
#pragma endregion

#pragma region Meta Methods
int Luna::Structs::Rect::__index(lua_State* L)
{
	auto self = GetRectSelf();
	auto Field = GetString(2);

	if (Field.length() != 1) goto FIDX;
	switch (Field[0])
	{
	case 'X':
		lua_pushinteger(L, self->X);
		return 1;
	case 'Y':
		lua_pushinteger(L, self->Y);
		return 1;
	case 'W':
		lua_pushinteger(L, self->W);
		return 1;
	case 'H':
		lua_pushinteger(L, self->H);
		return 1;
	case 'P':
		self->PushPosition();
		return 1;
	case 'S':
		self->PushSize();
		return 1;
	default:
		LunaIO::ThrowError(Field + " is not a valid member of Rect.");
	}
FIDX:
	LunaUtil::Local("RectMeta");
	lua_pushvalue(L, 2);
	lua_gettable(L, -2);
	if (lua_isnil(L, -1)) LunaIO::ThrowError(Field + " is not a valid member of Rect.");
	return 1;
}
int Luna::Structs::Rect::__newindex(lua_State* L)
{
	if (!lua_isnumber(L, 3)) LunaIO::ThrowError("Rect only accepts number fields.");
	auto self = GetRectSelf();
	auto Field = GetString(2);
	auto Value = GetInt(3);
	if (Field.length() != 1) LunaIO::ThrowError(Field + " is not a valid member of Rect or is read-only.");
	switch (Field[0])
	{
	case 'X':
		self->X = Value;
		return 0;
	case 'Y':
		self->Y = Value;
		return 0;
	case 'W':
		self->W = Value;
		return 0;
	case 'H':
		self->H = Value;
		return 0;
	}
	LunaIO::ThrowError(Field + " is not a valid member of Rect or is read-only.");
	return 0;
}
int Luna::Structs::Rect::__tostring(lua_State* L)
{
	auto self = GetRectSelf();
	std::string ToStr =
		"Rect(" + std::to_string(self->X) + ", " + 
		std::to_string(self->Y) + ", " + 
		std::to_string(self->W) + ", " + 
		std::to_string(self->H) + ")";
	lua_pushstring(L, ToStr.c_str());
	return 1;
}

int Luna::Structs::Rect::__add(lua_State* L)
{
	auto OType = LunaUtil::Type(2);
	if (OType != "Rect") LunaIO::ThrowError("Unable to add Rect and " + OType + ".");

	auto self = GetRect(1);
	auto Other = GetRect(2);
	(self + Other).Push();
	return 1;
}
int Luna::Structs::Rect::__sub(lua_State* L)
{
	auto OType = LunaUtil::Type(2);
	if (OType != "Rect") LunaIO::ThrowError("Unable to subtract " + OType + " from Rect.");

	auto self = GetRect(1);
	auto Other = GetRect(2);
	(self - Other).Push();
	return 1;
}
int Luna::Structs::Rect::__mul(lua_State* L)
{
	if (!lua_isnumber(L, 2)) LunaIO::ThrowError("Unable to multiply Rect by " + LunaUtil::Type(2) + ".");

	auto self = GetRect(1);
	auto Factor = (float)lua_tonumber(L, 2);
	(self * Factor).Push();
	return 1;
}
int Luna::Structs::Rect::__div(lua_State* L)
{
	if (!lua_isnumber(L, 2)) LunaIO::ThrowError("Unable to divide Rect by " + LunaUtil::Type(2) + ".");

	auto self = GetRect(1);
	auto Factor = (float)lua_tonumber(L, 2);
	(self / Factor).Push();
	return 1;
}
int Luna::Structs::Rect::__unm(lua_State* L)
{
	auto self = GetRect(1);
	(-self).Push();
	return 1;
}
int Luna::Structs::Rect::__eq(lua_State* L)
{
	if (LunaUtil::Type(2) != "Rect") { lua_pushboolean(L, false); return 1; }

	auto self = GetRect(1);
	auto Other = GetRect(2);
	lua_pushboolean(L, self == Other);
	return 1;
}
int Luna::Structs::Rect::__gc(lua_State* L)
{
	auto self = GetRectSelf();
	delete self;
	return 0;
}
#pragma endregion

int Luna::Structs::Rect::Init(lua_State* L)
{
	lua_newtable(L);

	lua_pushstring(L, "__type");
	lua_pushstring(L, "Rect");
	lua_settable(L, -3);

	SetMeta(__index);
	SetMeta(__newindex);
	SetMeta(__tostring);

	SetMeta(__add);
	SetMeta(__sub);
	SetMeta(__mul);
	SetMeta(__div);
	SetMeta(__unm);
	SetMeta(__eq);

	SetMeta(Lerp);
	SetMeta(GetArea);
	SetMeta(SetSize);
	SetMeta(Contains);
	SetMeta(GetCenter);
	SetMeta(SetCenter);
	SetMeta(Intersects);
	SetMeta(SetPosition);
	SetMeta(GetIntersection);

	LunaUtil::Local("RectMeta", -1);
	return 0;
}