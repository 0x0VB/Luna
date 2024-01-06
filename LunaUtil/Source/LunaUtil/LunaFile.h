#pragma once
#include "Common.h"

#include <stdint.h>
#include <vector>
#include <optional>
#include <filesystem>

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
		std::string CBytecode;
	};
	class LunaAsset
	{
	public:
		std::string Identifier;
		std::string CData;
	};

	class LunaFile
	{
	public:
		uint8_t Version = -1;
		uint8_t MinorVersion = -1;
		std::vector<LunaAsset> Assets = {};
		std::vector<LunaScript> Scripts = {};
		
		static LunaFile LoadFile(std::filesystem::path Path);
	};

}