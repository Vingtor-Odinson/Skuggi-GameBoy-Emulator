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

void checkSumFlags(const uint8_t& oldValue, const uint8_t& newValue, CPU* cpu) {

    if(newValue == 0x00) {
        cpu->setFlag(FlagsEnum::Z, true);
    }
    else {
        cpu->setFlag(FlagsEnum::Z, false);
    }

    if(((oldValue & 0x0F) + (newValue & 0x0F)) > 0x0F || ((oldValue & 0x0F) == 0x0F && (newValue & 0x0F) == 0x00))
    {
        cpu->setFlag(FlagsEnum::H, true);
    }
    else {
        cpu->setFlag(FlagsEnum::H, false);
    }

    if(newValue < oldValue) {
        cpu->setFlag(FlagsEnum::C, true);
    }
    else {
        cpu->setFlag(FlagsEnum::C, false);
    }
}

namespace Instructions{

    void nop( const InstructionParameters& params, CPU* cpu ){}

    void inc( const InstructionParameters& params, CPU* cpu ) //todo: change to use the CheckSumFlags function
    {  
        if( auto* reg = cpu->getRegister<uint8_t*>(params.AimedReg)) 
        {
            uint8_t mask = 0x08;
        
            bool bitBeforeIsOne = ( (*reg) & mask) != 0; // 3o bit era 1 antes?
        
            (*reg) += 1;
            
            bool bitAfterIsOne = ((*reg) & mask) != 0; // 3o bit é 1 depois?
            
            if( bitBeforeIsOne && !bitAfterIsOne )
            {
                cpu->setFlag(FlagsEnum::H, true);
            }

            cpu->setFlag(FlagsEnum::N, false);
            cpu->setFlag(FlagsEnum::Z, ((*reg) == 0x0));
        }

        if( auto reg16 = cpu->getRegister<uint16_t*>(params.AimedReg) )
        {
            if(!params.AimedIsAddress) { (*reg16) += 1; }
            else {
                uint8_t reg = cpu->read((*reg16));

                uint8_t mask = 0x08;

                bool bitBeforeIsOne = ( reg & mask) != 0; // 3o bit era 1 antes?

                reg += 1;

                cpu->write((*reg16), reg);

                bool bitAfterIsOne = (reg & mask) != 0; // 3o bit é 1 depois?

                if( bitBeforeIsOne && !bitAfterIsOne )
                {
                    cpu->setFlag(FlagsEnum::H, true);
                }

                cpu->setFlag(FlagsEnum::N, false);
                cpu->setFlag(FlagsEnum::Z, (reg == 0));
            }
        }
    }
    
    void adc(const InstructionParameters& param, CPU* cpu) {

        if( auto dest8reg = cpu->getRegister<uint8_t*>(param.AimedReg)){

            uint8_t orValueA = *dest8reg;
            uint8_t carryValue = cpu->getFlag(FlagsEnum::C) ? 1 : 0;
            uint8_t newValueA = orValueA;

            if(auto or8reg = cpu->getRegister<uint8_t*>(param.OriginReg)) {
                newValueA += *or8reg + carryValue;
            }
            else if(auto or16reg = cpu->getRegister<uint16_t*>(param.OriginReg)) {
                uint8_t regValue = cpu->read(*or16reg);
                newValueA += regValue + carryValue;
            }
            else if(param.OriginIsNextByte) {
                uint8_t nextByteValue = cpu->fetchMemory();
                newValueA += nextByteValue + carryValue;
            }

            *dest8reg = newValueA;

            cpu->setFlag(FlagsEnum::N, false);
            checkSumFlags(orValueA, newValueA, cpu);
        }
    }

    void add(const InstructionParameters& param, CPU* cpu) {

        if( auto dest8reg = cpu->getRegister<uint8_t*>(param.AimedReg)){

            uint8_t orValueA = *dest8reg;
            uint8_t newValueA = orValueA;

            if(auto or8reg = cpu->getRegister<uint8_t*>(param.OriginReg)) {
                newValueA += *or8reg;
            }
            else if(auto or16reg = cpu->getRegister<uint16_t*>(param.OriginReg)) {
                uint8_t regValue = cpu->read(*or16reg);
                newValueA += regValue;
            }
            else if(param.OriginIsNextByte) {
                uint8_t nextByteValue = cpu->fetchMemory();
                newValueA += nextByteValue;
            }

            *dest8reg = newValueA;

            cpu->setFlag(FlagsEnum::N, false);
            checkSumFlags(orValueA, newValueA, cpu);
        }
    }

    void dec( const InstructionParameters& params, CPU* cpu )
    {   
        if ( auto reg16 = cpu->getRegister<uint16_t*>(params.AimedReg) )
        {
            (*reg16) -= 1;
        }
        else if ( auto reg = cpu->getRegister<uint8_t*>(params.AimedReg) )
        {
            cpu->setFlag(FlagsEnum::N, true);

            uint8_t lowerNibbleBefore = ( (*reg) & 0b00001111);

            (*reg) -= 1;

            uint8_t lowerNibbleAfter = ((*reg) & 0b00001111);

            if( lowerNibbleAfter > lowerNibbleBefore )
            {
                cpu->setFlag(FlagsEnum::H, true);
            }

            if( (*reg) == 0 )
            {
                cpu->setFlag(FlagsEnum::Z, false);
            }
        }
    }

    void ld( const InstructionParameters& params, CPU* cpu )
    {
        if( auto destReg = cpu->getRegister<uint8_t*>(params.AimedReg) ) { //Se entrada for de 8 bits

            if( auto or8Reg = cpu->getRegister<uint8_t*>(params.OriginReg) ) { // Se o objetivo for de 8 bits
                *destReg = *or8Reg;
            }

            else if( auto orReg = cpu->getRegister<uint16_t*>(params.OriginReg) ) {
                if( params.OriginIsAddress ) {
                    *destReg = cpu->read(*orReg);

                    *orReg += params.OriginShouldIncrement ? 1 : 0;
                    *orReg -= params.OriginShouldDecrement ? 1 : 0;
                }
            }

            else if( params.OriginIsNextByte ) { //Caso o origin sejam os próximos 8 bits
                uint8_t orValue = cpu->fetchMemory(*(cpu->getRegister<uint16_t *>(RegistersEnum::PC)));//cpu->regs->PC);
                *destReg = orValue;
            }

            else if( params.OriginIsNextBytes ) {
                uint8_t lsb = cpu->fetchMemory(*(cpu->getRegister<uint16_t *>(RegistersEnum::PC))); //least significant byte
                uint8_t msb = cpu->fetchMemory(*(cpu->getRegister<uint16_t *>(RegistersEnum::PC))); //most significant byte

                uint16_t orAddress = (msb << 8) | lsb;

                *destReg = cpu->read(orAddress);
            }

        }

        else if(auto dest16Reg = cpu->getRegister<uint16_t*>(params.AimedReg)) { //Se entrada for de 16 bits

            if( params.OriginIsNextBytes ) {

                uint8_t lsb = cpu->fetchMemory(*(cpu->getRegister<uint16_t *>(RegistersEnum::PC))); //least significant byte
                uint8_t msb = cpu->fetchMemory(*(cpu->getRegister<uint16_t *>(RegistersEnum::PC))); //most significant byte

                uint16_t orValue = (msb << 8) | lsb;

                *dest16Reg = orValue;
            }

            else if(auto or8Reg = cpu->getRegister<uint8_t*>(params.OriginReg)) { // Se o registro de origem for de 8 bits
                if(params.AimedIsAddress) { // Se deve tratar o "aimed" como endereço
                    cpu->write(*dest16Reg, *or8Reg); //copia valor do registro de 8 bits no endereço

                    *dest16Reg += params.AimShouldIncrement ? 1 : 0;
                    *dest16Reg -= params.AimShouldDecrement ? 1 : 0;
                }
            }

            else if( auto or16Reg = cpu->getRegister<uint16_t*>(params.OriginReg) ) {
                *dest16Reg = *or16Reg;
            }
        }

        else if( params.AimIsNextBytes && params.AimedIsAddress ) {

            uint8_t lsb = cpu->fetchMemory(); //least significant byte
            uint8_t msb = cpu->fetchMemory(); //most significant byte

            uint16_t destAdd = (msb << 8) | lsb;

            if( params.OriginReg == RegistersEnum::SP) {
                uint16_t valueSP = *(cpu->getRegister<uint16_t*>(params.OriginReg));
                cpu->write(destAdd, valueSP & 0xFF);
                cpu->write(destAdd + 1, valueSP >> 8);
            }
            else if(auto orReg = cpu->getRegister<uint8_t*>(params.OriginReg)) {
                cpu->write(destAdd, *orReg);
            }

        }
    }

    void orInst( const InstructionParameters& params, CPU* cpu ) {

        uint8_t value = 0;

        auto dest8reg = cpu->getRegister<u_int8_t*>(params.AimedReg);

        if( auto org8reg = cpu->getRegister<uint8_t *>(params.OriginReg) ) {
            value = (*dest8reg | *org8reg);
        }
        else if(auto org16reg = cpu->getRegister<uint16_t*>(params.OriginReg)) {
            value = (*dest8reg | cpu->read(*org16reg));
        }
        else if(params.OriginIsNextByte) {
            uint8_t nextByte = cpu->fetchMemory();
            value = (*dest8reg | nextByte);
        }

        *dest8reg = value;

        if( value == 0 ) {
            cpu->setFlag(FlagsEnum::Z, true);
        }
        cpu->setFlag(FlagsEnum::N, false);
        cpu->setFlag(FlagsEnum::H, false);
        cpu->setFlag(FlagsEnum::C, false);
    }
}