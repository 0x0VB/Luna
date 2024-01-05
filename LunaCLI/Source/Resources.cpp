#include "Resources.h"

#include "LunaUtil/Common.h"
#include "Luau/Compiler.h"

const Luau::CompileOptions CompileOptions = { 2,0 };
LunaCLI::Resources LunaCLI::CreateResources(PackSettings Settings)
{
    Resources Res;
    size_t MaxFileSize = 0;

    if (!Settings.AssetsPath.empty())
        for (const auto& entry : std::filesystem::directory_iterator(Settings.AssetsPath)) {
        
            const auto AssetPath = Settings.AssetsPath / entry.path().filename();
            if (AssetPath.extension() != ".png")
                continue;
            Res.Assets.push_back(AssetPath);

            const auto FileSize = std::filesystem::file_size(AssetPath);
            if (FileSize > MaxFileSize)
                MaxFileSize = FileSize;
        }

    // add main script
    const auto MainSource = LunaUtil::ReadFile(Settings.ScriptPath);
    const auto MainBytecode = Luau::compile(MainSource, CompileOptions);
    Res.Scripts.push_back({ Settings.ScriptPath, MainBytecode });

    // load all scripts
    if (!Settings.ScriptsPath.empty())
        for (const auto& entry : std::filesystem::directory_iterator(Settings.ScriptsPath)) {

            const auto LuaPath = Settings.ScriptsPath / entry.path().filename();
            if (LuaPath.extension() != ".lua")
                continue;

            const auto Source = LunaUtil::ReadFile(LuaPath);
            const auto Bytecode = Luau::compile(Source, CompileOptions);
            Res.Scripts.push_back({ LuaPath, Bytecode });

            const auto FileSize = Bytecode.size();
            if (FileSize > MaxFileSize)
                MaxFileSize = FileSize;
        }

    Res.MaxDataSize = MaxFileSize;
    Res.CSize = ZSTD_compressBound(MaxFileSize);

    Res.DBuffer = new char[Res.MaxDataSize];
    Res.CBuffer = new char[Res.CSize];
    Res.CCTX = ZSTD_createCCtx();
    ZSTD_CCtx_setParameter(Res.CCTX, ZSTD_c_checksumFlag, 1);

    return Res;
}

std::string LunaCLI::Resources::CompressData(std::string Data)
{
    strcpy_s(DBuffer, Data.size(), Data.c_str());
    size_t const cSize = ZSTD_compressCCtx(CCTX, CBuffer, CSize, DBuffer, Data.size(), LUNA_COMPRESSION_LEVEL);
    std::string CompressedData(CBuffer, cSize);
    return CompressedData;
}