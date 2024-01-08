#include "stdafx.h"
#include "LunaLawn.h"

#include "LunaApi/LunaStructs/Rect/Rect.h"
#include "LunaApi/LunaUtil/LunaUtil.h"
#include "LunaApi/LunaIO/LunaIO.h"

#include "PvZ/UIElement.h"
#include "PvZ/UIRoot.h"
#include "PvZ/Lawn.h"
#include "Luna.h"

#include "LunaBase.h"
#include "UIElementClass.h"
#include "UIContainerClass.h"
#include "StoneButtonClass.h"
#include "ImageClass.h"

using namespace Luna::Class;
using namespace Fields;

namespace
{
	int NextZombie(lua_State* L)
	{
		auto Lawn = Luna::App->Lawn;
		Zombie* Current = NULL;
		while (Lawn->Zombies.Next(&Current))
			std::cout << Current << "\n";

		return 0;
	}
}

LunaClass* LunaLawn::Source = new LunaClass();
int LunaLawn::Init(lua_State* L)
{
	Source->AllowsInjection = true;
	Source->SetName("Lawn");
	Source->AddSubClass("Game");
	Source->AddSubClass("Board");
	Source->AddSubClass("Level");
	Source->Inherit(LunaUIElement::Source);

	BlnField::New("Paused", 0x164, Source);
	FltField::New("FogOffset", 0x5D0, Source);
	IntField::New("FogBlowTimer", 0x5D4, Source);
	IntField::New("BonusLawnMowers", 0x608, Source);
	IntField::New("SunTimer", 0x5538, Source);
	IntField::New("SunsFallen", 0x553C, Source);
	IntField::New("ShakeTimer", 0x5540, Source);
	IV2Field::New("ShakeOffset", 0x5544, Source);
	IntField::New("Level", 0x5550, Source);
	IntField::New("Sun", 0x5560, Source);
	IntField::New("WaveCount", 0x5564, Source);
	IntField::New("ActiveAge", 0x5568, Source);
	IntField::New("EffectTimer", 0x556C, Source);
	IntField::New("DrawCount", 0x5570, Source);
	IntField::New("AmbushTimer", 0x5574, Source);
	IntField::New("CoinBankFlashTimer", 0x5578, Source);
	IntField::New("CurrentWave", 0x557C, Source);
	IntField::New("TotalWavesSpawned", 0x5580, Source);
	IntField::New("LastBungeeWave", 0x5590, Source);
	IntField::New("WaveHPThreshold", 0x5594, Source);
	IntField::New("WaveMaxHP", 0x5598, Source);
	IntField::New("WaveTiemr", 0x559C, Source);
	IntField::New("MaxWaveTimer", 0x55A0, Source);
	IntField::New("FlagTimer", 0x55A4, Source);
	BlnField::New("BossKilled", 0x55F0, Source);
	BlnField::New("ShowShovel", 0x55F1, Source);
	IntField::New("CoinBankFadeTimer", 0x55F4, Source);
	BlnField::New("LevelComplete", 0x55FC, Source);
	IntField::New("LawnFadeTimer", 0x5600, Source);
	IntField::New("NextSurvivalWaveTimer", 0x5604, Source);
	BlnField::New("LevelAwardSpawned", 0x560C, Source);
	IntField::New("ProgressBarWidth", 0x5610, Source);
	IntField::New("RaisedFlags", 0x5614, Source);
	BlnField::New("CoinsUnlocked", 0x574C, Source);
	IntField::New("ThudTimer", 0x5750, Source);
	IV2Field::New("CobCursorPosition", 0x5758, Source);
	BlnField::New("YetiKilled", 0x5760, Source);

	Source->Methods["Test"] = NextZombie;

	return 0;
}