#include "pch.h"
#include "Common.h"


std::string LunaStatic::ReadFile(std::filesystem::path FilePath)
{
    std::ifstream File(FilePath.c_str());
    File.seekg(0, std::ios::end);
    std::streampos fileSize = File.tellg();
    File.seekg(0, std::ios::beg);

    std::string Source;
    Source.resize(fileSize);
    File.read(Source.data(), fileSize);

	return Source;
}
