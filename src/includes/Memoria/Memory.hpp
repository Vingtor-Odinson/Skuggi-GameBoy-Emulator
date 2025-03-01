#pragma once

#include <stdint.h>

class BANK00; //A memória será um compêndio de módulos, cada um com sua função específica

class Memory
{   
    public:
        BANK00* bank00;
    
        Memory();
        ~Memory();

        
};

