#include "Resources.h"

#include "Common.h"
#include "Luau/Compiler.h"

const std::vector<std::string> SupportedAssets = { ".png", ".jpg", ".mp3", ".wav", ".json" };

const Luau::CompileOptions CompileOptions = { 2,0 };
LunaCLI::Resources LunaCLI::CreateResources(PackSettings Settings)
{
    Resources Res;
    size_t MaxFileSize = 0;

    if (!Settings.AssetsPath.empty())
        for (const auto& entry : std::filesystem::directory_iterator(Settings.AssetsPath)) {
        
            const auto AssetPath = Settings.AssetsPath / entry.path().filename();
            const auto Extension = AssetPath.extension();
            if (std::find(SupportedAssets.begin(), SupportedAssets.end(), Extension) == SupportedAssets.end())
				continue;
            Res.Assets.push_back(AssetPath);

            const auto FileSize = std::filesystem::file_size(AssetPath);
            if (FileSize > MaxFileSize)
                MaxFileSize = FileSize;
        }

    // add main script
    const auto MainSource = LunaStatic::ReadFile(Settings.ScriptPath);
    const auto MainBytecode = Luau::compile(MainSource.data(), CompileOptions);
    if (MainBytecode.size() > MaxFileSize)
        MaxFileSize = MainBytecode.size();
    Res.Scripts.push_back({ Settings.ScriptPath, MainBytecode });

    // load all scripts
    if (!Settings.ScriptsPath.empty())
        for (const auto& entry : std::filesystem::directory_iterator(Settings.ScriptsPath)) {

            const auto LuaPath = Settings.ScriptsPath / entry.path().filename();
            if (LuaPath.extension() != ".lua")
                continue;

            const auto Source = LunaStatic::ReadFile(LuaPath);
            const auto Bytecode = Luau::compile(Source.c_str(), CompileOptions);
            Res.Scripts.push_back({ LuaPath, Bytecode });

            const auto DataSize = Bytecode.size();
            if (DataSize > MaxFileSize)
                MaxFileSize = DataSize;
        }

    Res.DCapacity = MaxFileSize;
    Res.CCapacity = ZSTD_compressBound(MaxFileSize);

    Res.DBuffer = new char[Res.DCapacity];
    Res.CBuffer = new char[Res.CCapacity];
    Res.CCTX = ZSTD_createCCtx();
    ZSTD_CCtx_setParameter(Res.CCTX, ZSTD_c_checksumFlag, 1);

    return Res;
}

std::string LunaCLI::Resources::CompressData(const char* Data, size_t DataSize)
{
    memcpy_s(DBuffer, DCapacity, Data, DataSize);
    size_t cSize = ZSTD_compressCCtx(CCTX, CBuffer, CCapacity, DBuffer, DataSize, LUNA_COMPRESSION_LEVEL);
    if (ZSTD_isError(cSize)) {
		printf("Compression failed: %s\n", ZSTD_getErrorName(cSize));
		return "";
	}
    return std::string(CBuffer, CBuffer + cSize);
}