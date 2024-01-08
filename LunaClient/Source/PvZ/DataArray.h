#pragma once
#include "Definitions.h"

template <typename T>
struct DataArrayItem
{
	T Item;
	unsigned int ID;

	bool IsDead() { return (ID & 0xFFFF0000) == 0; }
	DWORD Address() { return (DWORD)this; }
	T* GetItem() { return &Item; }
	operator T* () { return &Item; }
};

template <typename T>
struct DataArray
{
	DataArrayItem<T>* Block;
	unsigned int MaxUsedCount;
	unsigned int MaxSize;
	unsigned int FreeListHead;
	unsigned int Size;
	unsigned int NextKey;
	const char* Name;

	T* TryToGet(int ID)
	{
		auto NID = (ID & 0xFFFF);
		if (ID == 0 || (NID > MaxSize)) return NULL;
		DataArrayItem<T> Item = Block[NID];
		return Item & (Item.ID != ID) - 1;
	}

	DWORD MaxAddress() { return (DWORD)(Block + MaxUsedCount); }

	bool Next(T** Last)
	{
		DataArrayItem<T>* Current;
		if (*Last == NULL) Current = Block;
		else Current = ((DataArrayItem<T>*) * Last) + 1;

		while (Current->IsDead())
		{
			Current++;
			if (Current->Address() > MaxAddress()) return false;// Reched the end
		}

		*Last = Current->GetItem();
		return true;
	}
};