#include <iostream>
#include <string>
#include <filesystem>

enum LunaCLIMode {
    HELP,
    PACK_MOD,
    GET_INFO
};

struct LunaCLIOptions {
    LunaCLIMode Mode = HELP;
    std::string OutputPath = "Mod.luna";
    std::string ScriptPath = "";
    std::string AssetsPath = "";
} Options;

void ShowHelp()
{
	std::cout << "Usage: LunaCLI <mode> <options>\n\n";
	std::cout << "Modes:" << std::endl;
	std::cout << " -h, --help: Show this help message.\n";
	std::cout << " -i, --info: Get information about a Luna file.\n";
	std::cout << " -p, --pack: Pack a Luna script into a luna file.\n";
	std::cout << "     -a --assets-path [AssetsPath]\n";
	std::cout << "     -o --output-path [OutputPath]\n";
	std::cout << "     [!ScriptPath]\n\n";
	std::cout << "Example:\n";
	std::cout << "         LunaCLI -p Mods/MyMod.lua\n";
	std::cout << "         LunaCLI -p --assets-path Mods/MyModAssets --output-path MyMod.luna Mods/MyMod.lua\n";
}

void LunaPack()
{
	std::cout << "\n";
	if (Options.AssetsPath != "")
		std::cout << "Assets Path: " << Options.AssetsPath << std::endl;
	if (Options.OutputPath != "")
		std::cout << "Output Path: " << Options.OutputPath << std::endl;
	std::cout << "Packing " << Options.ScriptPath << " script file ..." << std::endl;
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
				Options.ScriptPath = arg;
				break;
			}

			if (arg == "-a" || arg == "--assets-path" && i + 1 < argc)
			{
				i++;
				Options.AssetsPath = argv[i];
				
			}
			else if (arg == "-o" || arg == "--output-path" && i + 1 < argc)
			{
				i++;
				Options.OutputPath = argv[i];
			}
		}

		if (Options.ScriptPath == "")
		{
			std::cout << "No script path specified." << std::endl;
			return 1;
		}
		LunaPack();
	}
	case GET_INFO:
	{
		break;
	}
	default:
		break;
	}
}