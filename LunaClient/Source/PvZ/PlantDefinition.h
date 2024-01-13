#pragma once
#include "Plant.h"

struct PlantDefinition
{
	SeedType SeedType;
	Sexy::Image** PlantImage;
	ReanimationType ReanimType;
	int PacketIndex;
	int SunCost;
	int Cooldown;
	bool Offensive;
	int ActionRate;
	const char* PlantName;
};

PlantDefinition* PlantDefinitions = (PlantDefinition*)0x69F2B0;
CONST DWORD PLANT_DEF_SIZE = (0x69FA24 - 0x69F2B0);
CONST DWORD References = {

};
void ReplaceDefinitions()
{

}