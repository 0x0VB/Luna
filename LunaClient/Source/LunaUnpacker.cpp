#include "stdafx.h"
#include "LunaUnpacker.h"

#include "Zstd/zstd.h"

bool Luna::LoadCompressedBytecode(lua_State* L, LunaStatic::LunaFile* LunaMod, size_t Index)
{
    if (Index >= LunaMod->Scripts.size())
        return false;

    const auto& Identifier = LunaMod->Scripts[Index].Identifier;
    auto& CBytecode = LunaMod->Scripts[Index].CBytecode;
    const auto CSize = CBytecode.size();

    auto const rSize = ZSTD_getFrameContentSize(CBytecode.data(), CSize);
    if (rSize == ZSTD_CONTENTSIZE_ERROR)
    {
        std::cout << Identifier << ": not compressed by LunaCLI!" << std::endl;
        return false;
    }
    if (rSize == ZSTD_CONTENTSIZE_UNKNOWN)
    {
        std::cout << Identifier << ": original size unknown!" << std::endl;
        return false;
    }

    char* const rBuff = new char[(size_t)rSize];
    size_t const dSize = ZSTD_decompress(rBuff, rSize, CBytecode.data(), CSize);

    std::string ChunkName = "=" + Identifier;
    const auto LoadRes = luau_load(L, ChunkName.data(), rBuff, dSize, 0);

    // Cleanup
    delete[] rBuff;
    CBytecode.clear();

    return LoadRes == 0;
}
