#include<Memoria/Memory.hpp>
#include<Memoria/MemoryParts.hpp>

Memory::Memory()
{
    bank00 = new BANK00();
}

Memory::~Memory()
{
    delete bank00;
}