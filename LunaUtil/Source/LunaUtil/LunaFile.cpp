#include "pch.h"
#include "LunaFile.h"

using namespace LunaUtil;

class LunaInStream {
public:
    LunaInStream(std::istream& stream) : stream_(stream) {}

    template <typename T>
    void Read(T& data) {
        stream_.read(reinterpret_cast<char*>(&data), sizeof(T));
    }

    void ReadVarInt(unsigned int& data)
    {
        data = 0;
        unsigned int shift = 0;
        uint8_t byte;

        do
        {
            Read<uint8_t>(byte);
            data |= (byte & 127) << shift;
            shift += 7;
        } while (byte & 128);
    }


    LunaAsset ReadAsset()
    {
		LunaAsset Asset = LunaAsset();

		uint32_t AssetNameSize;
		ReadVarInt(AssetNameSize);                      // [ASSET_IDENTIFIER_SIZE]
		std::string AssetName;
		AssetName.resize(AssetNameSize);
		stream_.read(AssetName.data(), AssetNameSize);  // [ASSET_IDENTIFIER]
		Asset.Identifier = AssetName;

		uint32_t CompressedAssetSize;
        ReadVarInt(CompressedAssetSize);                // [COMPRESSED_ASSET_SIZE]
		std::string CompressedAssetData;
		CompressedAssetData.resize(CompressedAssetSize);
		stream_.read(CompressedAssetData.data(), CompressedAssetSize); // [COMPRESSED_ASSET_DATA]
		Asset.CData = CompressedAssetData;

		return Asset;
	}

    LunaScript ReadScript()
    {
        LunaScript Script = LunaScript();

        uint32_t ScriptNameSize;
        ReadVarInt(ScriptNameSize);                     // [LUNA_SCRIPT_IDENTIFIER_SIZE]
        std::string ScriptName;
        ScriptName.resize(ScriptNameSize);
        stream_.read(ScriptName.data(), ScriptNameSize);// [LUNA_SCRIPT_IDENTIFIER]
        Script.Identifier = ScriptName;
        uint32_t CompressedBytecodeSize;
        ReadVarInt(CompressedBytecodeSize);             // [LUNA_COMPRESSED_BYTECODE_SIZE]
        std::string CompressedBytecode;
        CompressedBytecode.resize(CompressedBytecodeSize);
        stream_.read(CompressedBytecode.data(), CompressedBytecodeSize); // [LUNA_COMPRESSED_BYTECODE]
        Script.CBytecode = CompressedBytecode;

        return Script;
    }

private:
    std::istream& stream_;
};

LunaFile LunaUtil::LunaFile::LoadFile(std::filesystem::path Path)
{
    LunaFile Luna = LunaFile();

    // check if file exists
    if (!std::filesystem::exists(Path))
        return Luna;

    // open file
    std::ifstream File(Path, std::ios::binary);
    if (!File.is_open())
        return Luna;
    
    LunaInStream Stream(File);
    Stream.Read<uint8_t>(Luna.Version);
    Stream.Read<uint8_t>(Luna.MinorVersion);

    // check if version is supported
    if (Luna.Version * 10 + Luna.MinorVersion > LUNA_COMP_VERSION)
		return Luna;

    // read assets
    uint32_t AssetsNumber;
    Stream.ReadVarInt(AssetsNumber);

    for (uint32_t i = 0; i < AssetsNumber; i++)
		Luna.Assets.push_back(Stream.ReadAsset());

    // read scripts
    uint32_t ScriptsNumber;
    Stream.ReadVarInt(ScriptsNumber);

    for (uint32_t i = 0; i < ScriptsNumber; i++)
        Luna.Scripts.push_back(Stream.ReadScript());

    // check if stream ended
    if (File.peek() != EOF)
		return LunaFile();

    return Luna;
}
