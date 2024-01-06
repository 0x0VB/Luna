#include "LunaPack.h"
#include "Resources.h"
#include "LunaUtil/Common.h"

#include <iostream>
#include <string>
#include <fstream>

#include "Zstd/zstd.h"

#include "Luau/Compiler.h"

using std::filesystem::path;
using LunaCLI::PackSettings;

class LunaOutStream {
public:
    LunaOutStream(std::ostream& stream) : stream_(stream) {}

    template <typename T>
    void Write(const T& data) {
        stream_.write(reinterpret_cast<const char*>(&data), sizeof(T));
    }

    void WriteVarInt(unsigned int value)
    {
        do
        {
            Write<uint8_t>((value & 127) | ((value > 127) << 7));
            value >>= 7;
        } while (value);
    }

    void WriteAsset(LunaCLI::Resources* Res, const std::filesystem::path Path)
	{
		const auto AssetName = Path.filename().string();
		WriteVarInt(AssetName.size()); 		        // [ASSET_IDENTIFIER_SIZE]
		stream_ << AssetName;                       // [ASSET_IDENTIFIER]
		auto AssetData = LunaUtil::ReadFile(Path);
		const auto CompressedAssetData = Res->CompressData(AssetData.data(), AssetData.size());
		WriteVarInt(CompressedAssetData.size());    // [COMPRESSED_ASSET_SIZE]
		stream_ << CompressedAssetData;             // [COMPRESSED_ASSET_DATA]
	}

    void WriteScript(LunaCLI::Resources* Res, const ScriptData& Data)
    {
        const auto ScriptName = std::get<0>(Data).filename().string();
        WriteVarInt(ScriptName.size()); 		    // [LUNA_SCRIPT_IDENTIFIER_SIZE]
        stream_ << ScriptName;                      // [LUNA_SCRIPT_IDENTIFIER]
        auto Bytecode = std::get<1>(Data);
        const auto CompressedBytecode = Res->CompressData(Bytecode.c_str(), Bytecode.size());
        WriteVarInt(CompressedBytecode.size());     // [LUNA_COMPRESSED_BYTECODE_SIZE]
        stream_ << CompressedBytecode;              // [LUNA_COMPRESSED_BYTECODE]
    }

private:
    std::ostream& stream_;
};

LunaCLI::PackStatus LunaCLI::LunaPack(PackSettings Settings)
{
    if (!std::filesystem::exists(Settings.ScriptPath))
        return PackStatus::FailedOpenScript;

    std::ofstream OutputFile(Settings.OutputPath, std::ios::binary, std::ios::trunc);
    if (!OutputFile.is_open())
        return PackStatus::FailedOpenOut;

    auto Res = CreateResources(Settings);

    LunaOutStream OutputStream(OutputFile);
    OutputStream.Write<uint8_t>(LUNA_VERSION);              // [LUNA_VERSION]
    OutputStream.Write<uint8_t>(LUNA_MINOR_VERSION);        // [LUNA_MINOR_VERSION]

    OutputStream.WriteVarInt(Res.Assets.size());            // [LUNA_ASSETS_NUMBER]
    for (const auto& Asset : Res.Assets)
        OutputStream.WriteAsset(&Res, Asset);               // [ASSET]

    OutputStream.WriteVarInt(Res.Scripts.size());           // [LUNA_SCRIPTS_NUMBER]
    for (const auto& Script : Res.Scripts)
		OutputStream.WriteScript(&Res, Script);             // [SCRIPT]

    OutputFile.close();
    return PackStatus::Success;
}
