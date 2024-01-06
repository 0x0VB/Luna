#pragma once
#include <stdint.h>
#include <vector>

namespace LunaUtil
{
	/*
	LunaFile:
		[LUNA_VERSION]
		[LUNA_MINOR_VERSION]
		[LUNA_ASSETS_NUMBER]
		...
		[ASSET_IDENTIFIER_SIZE]
		[ASSET_IDENTIFIER]
		[COMPRESSED_ASSET_SIZE]
		[COMPRESSED_ASSET_DATA]
		...
		[LUNA_SCRIPTS_NUMBER]	// first script is the main script
		...
		[LUNA_SCRIPT_IDENTIFIER_SIZE]
		[LUNA_SCRIPT_IDENTIFIER]
		[LUNA_COMPRESSED_BYTECODE_SIZE]
		[LUNA_COMPRESSED_BYTECODE]
		...
	*/

	class LunaScript
	{
	public:
		std::string Identifier;
		std::string Bytecode;
	};
	class LunaAsset
	{
	public:
		std::string Identifier;
		std::string Data;
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