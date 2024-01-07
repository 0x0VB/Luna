#include "pch.h"
#include "LunaFile.h"

using namespace LunaStatic;

class LunaInStream {
public:
    LunaInStream(std::istream& stream) : stream_(stream) {}

    template <typename T>
    void Read(T& data) {
        stream_.read(reinterpret_cast<char*>(&data), sizeof(T));
    }

    LunaAsset ReadAsset()
    {
		LunaAsset Asset = LunaAsset();

        size_t AssetNameSize;
		Read<size_t>(AssetNameSize);                      // [ASSET_IDENTIFIER_SIZE]
		std::string AssetName;
		AssetName.resize(AssetNameSize);
		stream_.read(AssetName.data(), AssetNameSize);  // [ASSET_IDENTIFIER]
		Asset.Identifier = AssetName;

        size_t CompressedAssetSize;
        Read<size_t>(CompressedAssetSize);                // [COMPRESSED_ASSET_SIZE]
		std::string CompressedAssetData;
		CompressedAssetData.resize(CompressedAssetSize);
		stream_.read(CompressedAssetData.data(), CompressedAssetSize); // [COMPRESSED_ASSET_DATA]
		Asset.CData = CompressedAssetData;

		return Asset;
	}

    LunaScript ReadScript()
    {
        LunaScript Script = LunaScript();

        size_t ScriptNameSize;
        Read<size_t>(ScriptNameSize);                     // [LUNA_SCRIPT_IDENTIFIER_SIZE]
        std::string ScriptName;
        ScriptName.resize(ScriptNameSize);
        stream_.read(ScriptName.data(), ScriptNameSize);// [LUNA_SCRIPT_IDENTIFIER]
        Script.Identifier = ScriptName;
        size_t CompressedBytecodeSize;
        Read<size_t>(CompressedBytecodeSize);             // [LUNA_COMPRESSED_BYTECODE_SIZE]
        std::string CompressedBytecode;
        CompressedBytecode.resize(CompressedBytecodeSize);
        stream_.read(CompressedBytecode.data(), CompressedBytecodeSize); // [LUNA_COMPRESSED_BYTECODE]
        Script.CBytecode = CompressedBytecode;

        return Script;
    }

private:
    std::istream& stream_;
};

LunaFile LunaStatic::LunaFile::LoadFile(std::filesystem::path Path)
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
    size_t AssetsNumber;
    Stream.Read<size_t>(AssetsNumber);

    for (size_t i = 0; i < AssetsNumber; i++)
		Luna.Assets.push_back(Stream.ReadAsset());

    // read scripts
    size_t ScriptsNumber;
    Stream.Read<size_t>(ScriptsNumber);

    for (size_t i = 0; i < ScriptsNumber; i++)
        Luna.Scripts.push_back(Stream.ReadScript());

    // check if stream ended
    if (File.peek() != EOF)
		return LunaFile();

    return Luna;
}

const bool LunaStatic::LunaFile::IsValid()
{
    return ((Version * 10 + MinorVersion <= LUNA_COMP_VERSION) && (Scripts.size() >= 1));
}
