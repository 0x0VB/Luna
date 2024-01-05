#include "LunaPack.h"
#include "LunaUtil/Common.h"

#include <iostream>
#include <string>
#include <fstream>

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


private:
    std::ostream& stream_;
};

std::string LunaUtil::LunaPack(std::string ScriptBytecode, std::filesystem::path AssetsPath, std::filesystem::path OutputPath)
{
    std::ofstream OutputFile(OutputPath, std::ios::binary);

    if (!OutputFile.is_open()) {
        return "";
	}

    LunaOutStream OutputStream(OutputFile);
    OutputStream.Write<uint8_t>(LUNA_VERSION);          // [LUNA_VERSION]
    OutputStream.Write<uint8_t>(LUNA_MINOR_VERSION);    // [LUNA_MINOR_VERSION]


    //OutputStream.WriteVarInt(ScriptBytecode.size());    // [LUNA_COMPRESSED_BYTECODE_SIZE]

    return "";
}
