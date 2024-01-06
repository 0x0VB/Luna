#pragma once
#include <filesystem>
#include <string>

namespace LunaCLI
{
	enum PackStatus
	{
		Success, // must be first
		FailedOpenScript,
		FailedOpenOut,
		FailedAssetsPathIsNotADirectory,
		Unknown
	};

	struct PackSettings
	{
		std::filesystem::path ScriptPath;
		std::filesystem::path ScriptsPath;
		std::filesystem::path AssetsPath;
		std::filesystem::path OutputPath;
	};

	PackStatus LunaPack(PackSettings Settings);
}