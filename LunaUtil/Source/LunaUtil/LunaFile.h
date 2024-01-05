#pragma once
#include <stdint.h>
#include <vector>

namespace LunaUtil
{
	/*
	LunaFile:
		[LUNA_VERSION]
		[LUNA_MINOR_VERSION]
		[LUNA_COMPRESSED_BYTECODE_SIZE]
		[LUNA_COMPRESSED_BYTECODE]
		[LUNA_ASSETS_NUMBER]
		...
		[ASSET_IDENTIFIER_SIZE]
		[ASSET_IDENTIFIER]
		[ASSET_SIZE]
		[COMPRESSED_ASSET_DATA]
		...
		[INTEGRITY_CHECK] // CRC32
	*/

	class LunaAsset
	{
	public:
		std::string Identifier;
		uint32_t CompressedSize;
		std::string CompressedData;
	};

	class LunaFile
	{
	public:
		uint8_t Version;
		uint8_t MinorVersion;
		uint32_t CompressedBytecodeSize;
		std::string CompressedBytecode;
		std::vector<LunaAsset> Assets;
		uint32_t CRC32;

		// Methods
		std::string DecompressBytecode();
	};
}