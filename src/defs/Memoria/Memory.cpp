#include<Memoria/Memory.hpp>
#include<Memoria/MemoryParts.hpp>

Memory::Memory( Bus* pBus )
: bus(pBus)
{
    bank00 = new BANK00( pBus );
    banknn = new BANKNN( pBus );
    vram = new VRAM();
}

Memory::~Memory()
{
    delete bank00;
    delete banknn;
    delete vram;
}

MemoryPart* Memory::GetMemoryPart( uint16_t address )
{   
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
    MemoryPart* part = GetMemoryPart(address);

    if(part)
    {
        return part->Read(address);
    }

    return 0x0;
}

void Memory::write(const uint16_t& address,const uint8_t& value )
{
    MemoryPart* part = GetMemoryPart(address);

    if(part)
    {
        part->Write(address, value);
    }
}