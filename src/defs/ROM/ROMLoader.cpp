#include <ROM/ROMLoader.hpp>
#include <Memoria/Memory.hpp>
#include "fstream"
#include "MBC/MBC.hpp"
#include "MBC/MBCFactory.hpp"
#include "CPU/Bus.hpp"
#include "Exceptions/ROMReadingGenericError.hpp"

ROMLoader::ROMLoader(Bus* bus) {
    this->bus = bus;
}

void ROMLoader::SetROM( const std::string& Path)
{
    ROMPath = Path;
}

void ROMLoader::LoadROM()
{
    std::ifstream ROM( ROMPath, std::ios::binary | std::ios::ate );

    if(!ROM.is_open())
    {
        throw ROMReadingGenericError("Não foi posśivel carregar a ROM");
    }

    std::streamsize size = ROM.tellg();
    ROM.seekg(0, std::ios::beg);

    ROMData = new std::vector<uint8_t>(size);

    ROM.read(reinterpret_cast<char*>(ROMData->data()), size);

    mbc = MBCFactory::createMBC(*ROMData);
}

uint8_t ROMLoader::readRom(const uint16_t& add)
{
    return (*ROMData)[add];
}

uint8_t ROMLoader::read(const uint16_t &address) {
    if(mbc) {
        uint16_t mbcAddress = mbc->read(address);
        return readRom(mbcAddress);
    }
    else {
        if( 0x0000 <= address && address < 0x4000  ) {
            return readRom(address);
        }
        else {
            throw ROMReadingGenericError("There's no MBC available to manage banking.");
        }
    }
}

void ROMLoader::write(const uint16_t &address, const uint8_t &value) {
    if (mbc) {
        mbc->write(address, value);
    }
    else {
        throw ROMReadingGenericError("There's no available MBC to be written.");
    }
}
