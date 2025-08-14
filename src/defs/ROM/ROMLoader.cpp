#include <ROM/ROMLoader.hpp>
#include <CPU/CPU.hpp>
#include <Memoria/Memory.hpp>
#include <Memoria/MemoryParts.hpp>
#include "fstream"
#include "MBC/MBC.hpp"
#include "MBC/MBCFactory.hpp"

void ROMLoader::SetROM( const std::string& Path)
{
    ROMPath = Path;
}

void ROMLoader::LoadROM()
{
    std::ifstream ROM( ROMPath, std::ios::binary | std::ios::ate );

    if(!ROM.is_open())
    {
        throw std::runtime_error("Não foi posśivel carregar a ROM");
    }

    std::streamsize size = ROM.tellg();
    ROM.seekg(0, std::ios::beg);

    ROMData = new std::vector<uint8_t>(size);

    ROM.read(reinterpret_cast<char*>(ROMData->data()), size);

    MBCFactory mbcFactory;
    mbc = mbcFactory.createMBC(*ROMData);
}

uint8_t ROMLoader::readRom(const uint16_t& add)
{
    return (*ROMData)[add];
}

uint8_t ROMLoader::readFixedBank(const uint16_t &address) {
    if(mbc) {
        uint16_t mbcAddress = mbc->readFixedBank(address);
        return readRom(mbcAddress);
    }
    else {
        return readRom(address);
    }
}

uint8_t ROMLoader::readSwapBank(const uint16_t &address) {
    if (mbc) {
        uint16_t mbcAddress = mbc->readSwapBank(address);
        return readRom(mbcAddress);
    }
    else {
        throw std::runtime_error("There's no MBC available to manage banking.");
    }
}

void ROMLoader::write(const uint16_t &address, const uint8_t &value) {
    if (mbc) {
        mbc->write(address, value);
    }
    else {
        throw std::runtime_error("There's no available MBC to be written.");
    }
}
