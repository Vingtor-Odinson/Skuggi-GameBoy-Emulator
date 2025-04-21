#include<Memoria/Memory.hpp>
#include<Memoria/MemoryParts.hpp>

Memory::Memory( CPU* pCPU )
: cpu(pCPU)
{
    bank00 = new BANK00( pCPU );
}

Memory::~Memory()
{
    delete bank00;
}

uint8_t Memory::GetMemoryCategory(uint16_t address)
{
    if(address >= 0x0000 and address < 0x4000)
    {
        return 1;
    }
    else{
        return 0;
    }
}

uint8_t Memory::ReadMemory(uint16_t address)
{
    switch (Memory::GetMemoryCategory(address))
    {
    case 1:
        return this->bank00->Read(address);
        break;
    }

    return 0x0;
}

void Memory::WriteMemory( uint16_t address, uint8_t value )
{
    switch (Memory::GetMemoryCategory(address))
    {
    case 1:
        return this->bank00->Write(address, value);
        break;
    }
}