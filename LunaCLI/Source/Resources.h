#pragma once

#include <filesystem>
#include <tuple>

#include "Zstd/zstd.h"
#include "LunaPack.h"

// define ScriptTuple
typedef std::tuple<std::filesystem::path, std::string> ScriptData;

namespace LunaCLI
{
    class Resources {
    public:
        char* DBuffer = nullptr;      // DataBuffer
        char* CBuffer = nullptr;      // CompressedBuffer
        size_t DCapacity = 0;       // DataSize
        size_t CCapacity = 0;             // CompressedSize
        ZSTD_CCtx* CCTX = nullptr;    // Compression Context

        std::vector<std::filesystem::path> Assets = {};     // LunaAssets
        std::vector<ScriptData> Scripts = {};              // LunaScripts

        ~Resources() {
            delete[] DBuffer;
            delete[] CBuffer;
            ZSTD_freeCCtx(CCTX);
        }

        std::string CompressData(const char* Data, size_t DataSize);
    };

    Resources CreateResources(PackSettings Settings);
}