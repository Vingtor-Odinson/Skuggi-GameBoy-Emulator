#pragma once

#include <stdint.h>

class MemoryPart
{   
    public:
        uint32_t memoryOffset; //O offset para que possamos lidar com acesso externo a memória (Normalmente o último bit anterior + 1)
        uint8_t* memory; //A memória para esse pedaço

        void Write(uint16_t address, uint8_t value); //Funções básicas pra escrever e ler
        uint8_t Read(uint16_t address);
};

class BANK00 : public MemoryPart //Implementação da primeira parte da memória: O BANK00 que conterá o HEADER do jogo
{
    public:
        BANK00();
        ~BANK00();

        void MostraPrimeiros16();
        void PrintaLogoNintendo();
        void PrintaTituloJogo();

};