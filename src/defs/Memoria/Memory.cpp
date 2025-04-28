#include<Memoria/Memory.hpp>
#include<Memoria/MemoryParts.hpp>

Memory::Memory( CPU* pCPU )
: cpu(pCPU)
{
    bank00 = new BANK00( pCPU );
    banknn = new BANKNN( pCPU );
    vram = new VRAM();
}

Memory::~Memory()
{
    delete bank00;
    delete banknn;
    delete vram;
}

uint8_t Memory::GetMemoryCategory(uint16_t address)
{
    
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
        break;
    
    case 0x4:
    case 0x5:
    case 0x6:
    case 0x7:
        return this->banknn;
        break;

    case 0x8:
    case 0x9:
        return this->vram;
        
    default:
        break;
    }
}

uint8_t Memory::ReadMemory(uint16_t address)
{
    MemoryPart* part = GetMemoryPart(address);

    if(part)
    {
        return part->Read(address);
    }

    return 0x0;
}

void Memory::WriteMemory( uint16_t address, uint8_t value )
{
    MemoryPart* part = GetMemoryPart(address);

    if(part)
    {
        part->Write(address, value);
    }
}