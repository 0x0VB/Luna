#include <iostream>
#include <string>
#include <filesystem>
#include <format>

#include "LunaPack.h"
#include "LunaUtil/LunaFile.h"

enum LunaCLIMode {
    HELP,
    PACK_MOD,
    GET_INFO
};

struct LunaCLIOptions {
    LunaCLIMode Mode = HELP;
	LunaCLI::PackSettings Settings;
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

auto& Settings = Options.Settings;
void StartPacking()
{
	if (Settings.OutputPath == "")
		Settings.OutputPath = "Mod.luna";
	std::cout << "\n";
	std::cout << "Packing " << Settings.ScriptPath << " script file ...\n";

	const auto Status = LunaCLI::LunaPack(Settings);
	switch (Status)
	{
	case LunaCLI::PackStatus::Success:
		std::cout << "Successfully packed into " << Settings.OutputPath << std::endl;
		break;
	// TODO: Add more error messages based on the status
	default:
		std::cout << "Failed to pack into " << Settings.OutputPath << std::endl;
		break;
	}
}


std::string ReadableSize(size_t bytes) {
	const double KB = 1024.0;
	const double MB = KB * KB;
	const double GB = MB * KB;

	if (bytes < KB)
		return std::to_string(bytes) + " bytes";
	else if (bytes < MB)
		return std::to_string(bytes / KB) + " KB";
	else if (bytes < GB)
		return std::to_string(bytes / MB) + " MB";
	else
		return std::to_string(bytes / GB) + " GB";
}


void StartGettingInfo()
{
	std::cout << "\n";

	const auto Luna = LunaUtil::LunaFile::LoadFile(Settings.ScriptPath);
	if (Luna.Scripts.size() == 0)
	{
		std::cout << "Unable to load luna file " << Settings.ScriptPath << std::endl;
		return;
	}
	if (Luna.Version == -1 && Luna.MinorVersion == -1)
	{
		std::cout << "Corrupted luna file detected " << Settings.ScriptPath << std::endl;
		return;
	}

	std::cout << std::format("Luna Version: {}.{}\nAssets Number: {}\nScripts Number: {}\n\n", Luna.Version, Luna.MinorVersion, Luna.Assets.size(), Luna.Scripts.size());
	if (Luna.Assets.size() > 0)
	{
		std::cout << std::setw(15) << std::left << "#Assets";
		std::cout << std::setw(15) << std::left << "Identifier";
		std::cout << std::setw(15) << std::left << "Compressed Size" << std::endl;
		for (auto& Asset : Luna.Assets)
		{
			std::cout << std::setw(15) << std::left << "";
			std::cout << std::setw(15) << std::left << Asset.Identifier;
			std::cout << std::setw(15) << std::left << ReadableSize(Asset.CData.size()) << std::endl;
		}
		std::cout << "\n";
	}
	std::cout << std::setw(15) << std::left << "#Scripts";
	std::cout << std::setw(15) << std::left << "Identifier";
	std::cout << std::setw(15) << std::left << "Compressed Size" << std::endl;
	for (auto& Script : Luna.Scripts)
	{
		std::cout << std::setw(15) << std::left << "";
		std::cout << std::setw(15) << std::left << Script.Identifier;
		std::cout << std::setw(15) << std::left << ReadableSize(Script.CBytecode.size()) << std::endl;
		std::cout << std::endl;
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
				Settings.ScriptPath = arg;
				break;
			}

			if (arg == "-a" || arg == "--assets-path" && i + 1 < argc)
			{
				i++;
				Settings.AssetsPath = argv[i];
				
			}
			else if (arg == "-s" || arg == "--scripts-path" && i + 1 < argc)
			{
				i++;
				Settings.ScriptsPath = argv[i];
			}
			else if (arg == "-o" || arg == "--output-path" && i + 1 < argc)
			{
				i++;
				Settings.OutputPath = argv[i];
			}
			else
			{
				std::cout << "Invalid unpack option: " << arg << std::endl;
				return 2;
			}
		}

		if (Settings.ScriptPath == "")
		{
			std::cout << "No script path specified." << std::endl;
			return 1;
		}
		StartPacking();
	}
	case GET_INFO:
	{
		if (argc < 3)
		{
			std::cout << "No luna path specified." << std::endl;
			return 1;
		}
		Settings.ScriptPath = argv[2];
		StartGettingInfo();
		break;
	}
	default:
		break;
	}
}