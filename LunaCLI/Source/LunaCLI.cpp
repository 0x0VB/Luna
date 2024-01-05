#include <iostream>
#include <string>
#include <filesystem>

#include "LunaPack.h"

enum LunaCLIMode {
    HELP,
    PACK_MOD,
    GET_INFO
};

struct LunaCLIOptions {
    LunaCLIMode Mode = HELP;
	LunaCLI::PackSettings PackSettings;
} Options;

void ShowHelp()
{
	std::cout << "Usage: LunaCLI <mode> <options>\n\n";
	std::cout << "Modes:" << std::endl;
	std::cout << " -h, --help: Show this help message.\n";
	std::cout << " -i, --info: Get information about a Luna file.\n";
	std::cout << " -p, --pack: Pack a Luna script into a luna file.\n";
	std::cout << "     -s --scripts-path [ScriptsPath]\n";
	std::cout << "     -a --assets-path [AssetsPath]\n";
	std::cout << "     -o --output-path [OutputPath]\n";
	std::cout << "     [!ScriptPath]\n\n";
	std::cout << "Example:\n";
	std::cout << "         LunaCLI -p Mods/MyMod.lua\n";
	std::cout << "         LunaCLI -p -a Mods/MyModAssets -s Mods/MyLuaScripts -o MyMod.luna Mods/MyMod.lua\n";
}

auto& PackSettings = Options.PackSettings;
void StartPacking()
{
	if (PackSettings.OutputPath == "")
		PackSettings.OutputPath = "Mod.luna";
	std::cout << "\n";
	std::cout << "Packing " << PackSettings.ScriptPath << " script file ...\n";

	const auto Status = LunaCLI::LunaPack(PackSettings);
	switch (Status)
	{
	case LunaCLI::PackStatus::Success:
		std::cout << "Successfully packed into " << PackSettings.OutputPath << std::endl;
		break;
	// TODO: Add more error messages based on the status
	default:
		std::cout << "Failed to pack into " << PackSettings.OutputPath << std::endl;
		break;
	}
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
		ShowHelp();
		return 0;
	 }

	std::string Mode = argv[1];

	if (Mode == "-h" || Mode == "--help")
	{
		ShowHelp();
	}
	else if (Mode == "-i" || Mode == "--info")
	{
		Options.Mode = GET_INFO;
	}
	else if (Mode == "-p" || Mode == "--pack")
	{
		Options.Mode = PACK_MOD;
	}
	else
	{
		std::cout << "Invalid mode: " << Mode << std::endl;
		return 1;
	}

	switch (Options.Mode)
	{
	case PACK_MOD:
	{
		// load options
		for (int i = 2; i < argc; i++)
		{
			std::string arg = argv[i];

			if (i == argc - 1)
			{
				PackSettings.ScriptPath = arg;
				break;
			}

			if (arg == "-a" || arg == "--assets-path" && i + 1 < argc)
			{
				i++;
				PackSettings.AssetsPath = argv[i];
				
			}
			else if (arg == "-s" || arg == "--scripts-path" && i + 1 < argc)
			{
				i++;
				PackSettings.ScriptsPath = argv[i];
			}
			else if (arg == "-o" || arg == "--output-path" && i + 1 < argc)
			{
				i++;
				PackSettings.OutputPath = argv[i];
			}
		}

		if (PackSettings.ScriptPath == "")
		{
			std::cout << "No script path specified." << std::endl;
			return 1;
		}
		StartPacking();
	}
	case GET_INFO:
	{
		break;
	}
	default:
		break;
	}
}