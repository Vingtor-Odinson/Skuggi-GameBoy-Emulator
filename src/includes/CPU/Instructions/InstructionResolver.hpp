#pragma once    

#include <CPU/Instructions/Instructions.hpp>

class InstructionResolver
{
    public:
        void ConfigParams(Instruction* st, InstructionParameters& param);
};