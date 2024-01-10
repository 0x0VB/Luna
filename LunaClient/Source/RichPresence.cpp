#include "stdafx.h"
#include "RichPresence.h"

#include "Enums/GameModes.h"
#include "Enums/GameScenes.h"
#include "Luna.h"

discord::Core* Luna::Discord::Core = nullptr;

void Luna::Discord::Initialize()
{
	auto result = discord::Core::Create(1194424199855476737, DiscordCreateFlags_Default, &Core);
}

std::string GameModeToString(GameMode Mode)
{
	if (Mode == GameMode::GAMEMODE_ADVENTURE)
		return "Adventure";
	if (Mode >= GameMode::GAMEMODE_SURVIVAL_NORMAL_STAGE_1 && Mode <= GameMode::GAMEMODE_SURVIVAL_ENDLESS_STAGE_5)
		return "Survival";
	if (Mode >= GameMode::GAMEMODE_CHALLENGE_WAR_AND_PEAS && Mode <= GameMode::GAMEMODE_CHALLENGE_SQUIRREL)
		return "Challenge";
	if (Mode == GameMode::GAMEMODE_TREE_OF_WISDOM)
		return "Tree of Wisdom";
	if (Mode >= GameMode::GAMEMODE_SCARY_POTTER_1 && Mode <= GameMode::GAMEMODE_SCARY_POTTER_ENDLESS)
		return "Scary Potter";
	if (Mode >= GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_1 && Mode <= GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_ENDLESS)
		return "Puzzle";
	return "Unknown";
}

GameScene LastScene = GameScene::SCENE_LOADING;
std::chrono::system_clock::time_point LastTimestamp = std::chrono::system_clock::now();
void Luna::Discord::Tick()
{
	auto& ActivityManager = Core->ActivityManager();
	
	discord::Activity Activity{};
	Activity.SetType(discord::ActivityType::Playing);

	auto& Assets = Activity.GetAssets();
	Assets.SetLargeImage("pvz");
	Assets.SetLargeText("Plants vs. Zombies: Game of the Year");
	Assets.SetSmallImage("lunaxl");
	Assets.SetSmallText("Luna Client");

	auto& Timestamps = Activity.GetTimestamps();
	auto Now = std::chrono::system_clock::now();

	if (LastScene != App->GameScene)
	{
		LastScene = App->GameScene;
		LastTimestamp = Now;
	}
	
	const std::string ElapsedText = std::format("Elapsed {:02d}:{:02d}",
		std::chrono::duration_cast<std::chrono::minutes>(Now - LastTimestamp).count() % 60,
		std::chrono::duration_cast<std::chrono::seconds>(Now - LastTimestamp).count() % 60
	);
	Activity.SetDetails(ElapsedText.c_str());

	switch(App->GameScene)
	{
		case GameScene::SCENE_LEVEL_INTRO:
		case GameScene::SCENE_PLAYING:
		{
			Activity.SetState(std::format("Playing {}", GameModeToString(App->GameMode)).c_str());
			break;
		}
		case GameScene::SCENE_MENU:
		{
			Activity.SetState("In Menu");
			break;
		}
		case GameScene::SCENE_LOADING:
		default:
		{
			Activity.SetState("Loading..");
			break;
		}
	}

	ActivityManager.UpdateActivity(Activity, [](discord::Result result) {
		if (result != discord::Result::Ok)
			std::cout << "Failed to update activity\n";
	});

	Core->RunCallbacks();
}
