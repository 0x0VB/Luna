#pragma once
#include <vector>
#include <filesystem>

#define LUNA_DEBUG true

#define LUNA_VERSION 0
#define LUNA_MINOR_VERSION 2
#define LUNA_COMP_VERSION LUNA_VERSION * 10 + LUNA_MINOR_VERSION

#define LUNA_COMPRESSION_LEVEL 12

namespace LunaStatic
{
	std::string ReadFile(std::filesystem::path FilePath);
}