#pragma once

#include <Memoria/MemoryParts.hpp>

class ROMLoader;

class BANKNN : public MemoryPart //Implementação da primeira parte da memória: O BANK00 que conterá o HEADER do jogo
{   
    private:
        ROMLoader* romLoader;

    public:
        BANKNN( CPU* pCpu );

        uint8_t Read(uint16_t address) override;
        void Write(uint16_t address, uint8_t value) override;

        void MostraPrimeiros16();
        void PrintaLogoNintendo();
        void PrintaTituloJogo();

};