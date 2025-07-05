#include <CPU/CPU.hpp>
#include <Memoria/Memory.hpp>
#include <CPU/Instructions/Instructions.hpp>
#include <CPU/Registers.hpp>
#include <CPU/Instructions/InstructionResolver.hpp>
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include "enum/RegistersEnum.hpp"

using json = nlohmann::json;

namespace Instructions{

    uint8_t* get8BytesReg( RegistersEnum reg, CPU* cpu )
    {
        switch (reg) {
            case RegistersEnum::A: return &(cpu->regs->A);
            case RegistersEnum::B: return &(cpu->regs->B);
            case RegistersEnum::C: return &(cpu->regs->C);
            case RegistersEnum::D: return &(cpu->regs->D);
            case RegistersEnum::E: return &(cpu->regs->E);
            case RegistersEnum::F: return &(cpu->regs->F);
            case RegistersEnum::H: return &(cpu->regs->H);
            case RegistersEnum::L: return &(cpu->regs->L);
            default: return nullptr;
        }
    }

    uint16_t* get16BytesReg( RegistersEnum reg, CPU* cpu )
    {
        switch (reg) {
            case RegistersEnum::AF: return &(cpu->regs->AF);
            case RegistersEnum::BC: return &(cpu->regs->BC);
            case RegistersEnum::DE: return &(cpu->regs->DE);
            case RegistersEnum::HL: return &(cpu->regs->HL);
            case RegistersEnum::PC: return &(cpu->regs->PC);
            case RegistersEnum::SP: return &(cpu->regs->SP);
            default: return nullptr;
        }
    }

    void nop( InstructionParameters params, CPU* cpu ){}

    void inc( InstructionParameters params, CPU* cpu )
    {  
        if( uint8_t* reg = get8BytesReg( params.AimedReg, cpu ) )
        {
            uint8_t mask = 0x08;
        
            bool bitBeforeIsOne = ( (*reg) & mask) != 0; // 3o bit era 1 antes?
        
            (*reg) += 1;
            
            bool bitAfterIsOne = ((*reg) & mask) != 0; // 3o bit é 1 depois?
            
            if( bitBeforeIsOne && !bitAfterIsOne )
            {
                cpu->flags->H = "1";
            }

            cpu->flags->N = "0";
        }

        if( uint16_t* add = get16BytesReg( params.AimedReg, cpu ) )
        {
            uint8_t reg = cpu->memory->ReadMemory( (*add) );

            uint8_t mask = 0x08;
        
            bool bitBeforeIsOne = ( reg & mask) != 0; // 3o bit era 1 antes?
        
            reg += 1;
            
            cpu->memory->WriteMemory( (*add), reg );

            bool bitAfterIsOne = (reg & mask) != 0; // 3o bit é 1 depois?
            
            if( bitBeforeIsOne && !bitAfterIsOne )
            {
                cpu->flags->H = "1";
            }
            if( reg == 0 )
            {
                cpu->flags->Z = "1";
            }

            cpu->flags->N = "0";
        
        }
    }

    void dec( InstructionParameters params, CPU* cpu )
    {   
        if ( uint16_t* reg16 = get16BytesReg( params.AimedReg, cpu ) )
        {
            (*reg16) -= 1;
        }
        else if ( uint8_t* reg = get8BytesReg( params.AimedReg, cpu ) )
        {
            cpu->flags->N = "1";

            uint8_t lowerNibbleBefore = ( (*reg) & 0b00001111);

            (*reg) -= 1;

            uint8_t lowerNibbleAfter = ((*reg) & 0b00001111);

            if( lowerNibbleAfter > lowerNibbleBefore )
            {
                cpu->flags->H = "1";
            }

            if( (*reg) == 0 )
            {
                cpu->flags->Z = "0";
            }
        }
    }

    void ld( InstructionParameters params, CPU* cpu )
    {
        if( uint8_t* destReg = get8BytesReg(params.AimedReg, cpu) ) { //Se entrada for de 8 bits

            if( uint8_t* orReg = get8BytesReg(params.OriginReg, cpu) ) { // Se o objetivo for de 8 bits
                *destReg = *orReg;
            }

            else if( params.OriginIsNextByte ) { //Caso o origin sejam os próximos 8 bits
                uint8_t orValue = cpu->fetchMemory(cpu->regs->PC);
                *destReg = orValue;
            }
        }

        else if( get16BytesReg(params.OriginReg, cpu) != nullptr ) { //Se entrada for de 16 bits
            if( get16BytesReg(params.AimedReg, cpu) != nullptr ) { // Se o objetivo for de 16 bits


            }
        }
    }
}