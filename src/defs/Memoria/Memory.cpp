#include<Memoria/Memory.hpp>
#include<Memoria/MemoryParts.hpp>

Memory::Memory( Bus* pBus )
: bus(pBus)
{
    bank00 = new BANK00( pBus );
    banknn = new BANKNN( pBus );
    ioRegs = new IORegisters();
    vram = new VRAM();
}

Memory::~Memory()
{
    delete bank00;
    delete banknn;
    delete ioRegs;
    delete vram;
}

MemoryPart* Memory::GetMemoryPart( uint16_t address )
{
    if(address >= 0xFF00 && address < 0xFF80) {
        return ioRegs;
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
        return part->Read(address);
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
        part->Write(address, value);
    }
}