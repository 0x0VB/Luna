#include "pch.h"
#include "Common.h"


std::vector<char> LunaUtil::ReadFile(std::filesystem::path FilePath)
{
    std::ifstream File(FilePath.c_str());
    File.seekg(0, std::ios::end);
    std::streampos fileSize = File.tellg();
    File.seekg(0, std::ios::beg);

    std::vector<char> Source(static_cast<std::size_t>(fileSize));
    File.read(Source.data(), fileSize);

	return Source;
}
