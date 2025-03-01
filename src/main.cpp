#include <iostream>
#include <CPU.hpp>
#include <ROM/ROMLoader.hpp>
#include <Memoria/Memory.hpp>
#include <Memoria/MemoryParts.hpp>

#include <filesystem>
#include <string.h>

int main()
{
    std::string ROMPath = "ROM/PokemonYellow.gbc";
    CPU cpu = CPU();
    cpu.romLoader->SetROM(ROMPath); //Escolhe a rom
    cpu.romLoader->LoadROM(); //Carrega a ROM
    cpu.romLoader->LoadBANK00(); //Carrega o banco fixo

    cpu.memory->bank00->MostraPrimeiros16();
    cpu.memory->bank00->PrintaLogoNintendo();
    cpu.memory->bank00->PrintaTituloJogo();

    return 0;
} 