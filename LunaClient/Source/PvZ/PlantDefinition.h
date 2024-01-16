#pragma once
#include "Definitions.h"
#include "Plant.h"

PlantDefinition* PlantDefinitions = (PlantDefinition*)0x69F2B0;
CONST DWORD PLANT_DEF_SIZE = (0x69FA24 - 0x69F2B0);
CONST SIZE_T PLANT_DEF_REF_COUNT = 0x0;
CONST DWORD References[20] = {
	0x4024BD + 3,
	0x45DCBC + 3,
	0x45FF70 + 3,
	0x463F47 + 3,
	0x465AF8 + 3,
	0x467C26 + 3,
	0x467C86 + 3,
	0x467DD0 + 3,
	0x4681E3 + 3,
	0x46F5EF + 3,
	0x439D62 + 1,
	0x43A048 + 1,
	0x45FF66 + 3,
	0x465AF8 + 3,
	0x4662F6 + 2
};