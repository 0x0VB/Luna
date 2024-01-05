#pragma once
#include <filesystem>
#include <string>

namespace LunaUtil
{
	std::string LunaPack(std::string ScriptBytecode, std::filesystem::path AssetsPath, std::filesystem::path OutputPath);
}