#include "stdafx.h"
#include "Plant.h"

void Plant::Die()
{
	((Die_Type)(0x4679B0))(this);
}

void Plant::Fire(Zombie* Target, int TargetLane, bool IsSecondary)
{
	TargetLane = (TargetLane == -1) ? Lane : TargetLane;
	((Fire_Type)(0x466E00))(this, Target, TargetLane, IsSecondary);
}