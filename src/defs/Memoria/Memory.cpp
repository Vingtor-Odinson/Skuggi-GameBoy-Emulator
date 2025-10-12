#include<Memoria/Memory.hpp>
#include<Memoria/MemoryParts.hpp>
#include<CPU/Bus.hpp>

Memory::Memory( Bus* pBus )
: bus(pBus)
{
    bank00 = new BANK00( pBus );
    banknn = new BANKNN( pBus );
    wram1 = new WRAM(0xC000);
    wram2 = new WRAM(0xD000);
    hram = new HRAM();
    oam = new OAM();
    ioRegs = new IORegisters();
    vram = new VRAM();
}

Memory::~Memory()
{
    delete bank00;
    delete banknn;
    delete wram1;
    delete wram2;
    delete hram;
    delete oam;
    delete ioRegs;
    delete vram;
}

MemoryPart* Memory::GetMemoryPart( uint16_t address )
{
    if(address >= 0xFF00 && address < 0xFF80)
    {
        return ioRegs;
    }

    if ( address >= 0xFE00 && address < 0xFEA0)
    {
        return oam;
    }

    uint8_t region = address >> 12;

    switch (region)
    {
    case 0x0:
    case 0x1:
    case 0x2:
    case 0x3:
        return this->bank00;
    
    case 0x4:
    case 0x5:
    case 0x6:
    case 0x7:
        return this->banknn;

    case 0x8:
    case 0x9:
        return this->vram;
    case 0xC:
        return this->wram1;
    case 0xD:
        return this->wram2;
    default:
        break;
    }
}

uint8_t Memory::read(const uint16_t& address)
{
    if(address == 0xFFFF) {
        return interruptEnableReg;
    }

    MemoryPart* part = GetMemoryPart(address);

    if(part)
    {
        return part->read(address);
    }

    return 0x0;
}

void Memory::write(const uint16_t& address,const uint8_t& value )
{
    if(address == 0xFFFF) {
        interruptEnableReg = value;
        return;
    }

    MemoryPart* part = GetMemoryPart(address);

    if(part)
    {
        part->write(address, value);
    }
}