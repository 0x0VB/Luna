#pragma once

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

	DWORD MaxAddress() { return (DWORD)(Block + MaxUsedCount); }
	T* TryToGet(int ID)
	{
		auto NID = (ID & 0xFFFF);
		if (ID == 0 || (NID > MaxSize)) return NULL;
		DataArrayItem<T> Item = Block[NID];
		if (Item)
			return Item;
		return nullptr;
	}
	T* Alloc()
	{
		DataArrayItem<T>* New;

		int FreeListOG = FreeListHead;
		if (FreeListHead == MaxUsedCount)
		{
			MaxUsedCount++;
			FreeListHead++;
		}
		else
			FreeListHead = Block[FreeListOG].ID;
		
		New = Block + FreeListOG;
		memset(New, 0, sizeof(T));
		New->ID = NextKey << 0x10 | FreeListOG;
		NextKey++;

		if (NextKey == 0x10000) NextKey = 1;
		Size++;
		
		auto Item = new (&New->Item) T();
		return Item;
	}
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