#include <iostream>
#include <CPU.hpp>
#include <Memoria/Memory.hpp>
#include <Memoria/MemoryParts.hpp>

int main()
{
    CPU cpu = CPU();
    cpu.memory->bank00->Write(0x0010, 0x05);
    std::cout << "Valor na memória: " << static_cast<int> (cpu.memory->bank00->Read(0x0010))<< std::endl;
    return 0;
}