#pragma once
#include <vector>
#include <filesystem>

#define LUNA_VERSION 0
#define LUNA_MINOR_VERSION 2
#define LUNA_COMPRESSION_LEVEL 12

namespace LunaUtil
{
	std::vector<char> ReadFile(std::filesystem::path FilePath);
}