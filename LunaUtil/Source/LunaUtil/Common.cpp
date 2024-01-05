#include "pch.h"
#include "Common.h"

std::string LunaUtil::ReadFile(std::filesystem::path FilePath)
{
	std::ifstream File(FilePath.c_str());
	std::string Source((std::istreambuf_iterator<char>(File)), std::istreambuf_iterator<char>());
	return Source;
}
