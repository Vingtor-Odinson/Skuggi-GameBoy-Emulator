#include <CPU/CPU.hpp>

void checkSumFlags8bits(const uint8_t& oldValue, const uint8_t& newValue, CPU* cpu) {

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

    cpu->setFlag(FlagsEnum::C, newValue < oldValue);
}

void checkSumFlags8bits(const uint16_t& oldValue, const uint16_t& newValue, CPU* cpu) {

    if(((oldValue & 0x0F) + (newValue & 0x0F)) > 0x0F || ((oldValue & 0x0F) == 0x0F && (newValue & 0x0F) == 0x00))
    {
        cpu->setFlag(FlagsEnum::H, true);
    }
    else {
        cpu->setFlag(FlagsEnum::H, false);
    }

    if(((oldValue & 0x00FF) + (newValue & 0x00FF)) > 0x00FF || (oldValue <= 0x00FF && newValue > 0x00FF && (newValue & 0x00FF) == 0x0000)) {
        cpu->setFlag(FlagsEnum::C, true);
    }
    else {
        cpu->setFlag(FlagsEnum::C, false);
    }
}

void checkSumFlags16bits(const uint16_t& oldValue, const uint16_t& newValue, CPU* cpu) {

    if(((oldValue & 0x800) + (newValue & 0x800)) > 0x800 || ((oldValue & 0x800) == 0x800 && (newValue & 0x800) == 0x800))
    {
        cpu->setFlag(FlagsEnum::H, true);
    }
    else {
        cpu->setFlag(FlagsEnum::H, false);
    }

    cpu->setFlag(FlagsEnum::C, newValue < oldValue);
}

void checkAndFlags(const uint8_t& value, CPU* cpu) {
    if(value == 0x00) {
        cpu->setFlag(FlagsEnum::Z, true);
    }
    else {
        cpu->setFlag(FlagsEnum::Z, false);
    }

    cpu->setFlag(FlagsEnum::N, false);
    cpu->setFlag(FlagsEnum::H, true);
    cpu->setFlag(FlagsEnum::C, false);
}

namespace Instructions{

    void nop( const InstructionParameters& params, CPU* cpu ){}

    void inc( const InstructionParameters& params, CPU* cpu ) //todo: change to use the CheckSumFlags function
    {  
        if( auto* reg = cpu->get8bitRegister(params.AimedReg)) 
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

        if( auto reg16 = cpu->get16bitRegister(params.AimedReg) )
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

        if( auto dest8reg = cpu->get8bitRegister(param.AimedReg)){

            uint8_t orValueA = *dest8reg;
            uint8_t carryValue = cpu->getFlag(FlagsEnum::C) ? 1 : 0;
            uint8_t newValueA = orValueA;

            if(auto or8reg = cpu->get8bitRegister(param.OriginReg)) {
                newValueA += *or8reg + carryValue;
            }
            else if(auto or16reg = cpu->get16bitRegister(param.OriginReg)) {
                uint8_t regValue = cpu->read(*or16reg);
                newValueA += regValue + carryValue;
            }
            else if(param.OriginIsNextByte) {
                uint8_t nextByteValue = cpu->fetchMemory();
                newValueA += nextByteValue + carryValue;
            }

            *dest8reg = newValueA;

            cpu->setFlag(FlagsEnum::N, false);
            checkSumFlags8bits(orValueA, newValueA, cpu);
        }
    }

    void add(const InstructionParameters& param, CPU* cpu) {

        if( auto dest8reg = cpu->get8bitRegister(param.AimedReg)){

            uint8_t orValueA = *dest8reg;
            uint8_t newValueA = orValueA;

            if(auto or8reg = cpu->get8bitRegister(param.OriginReg)) {
                newValueA += *or8reg;
            }
            else if(auto or16reg = cpu->get16bitRegister(param.OriginReg)) {
                uint8_t regValue = cpu->read(*or16reg);
                newValueA += regValue;
            }
            else if(param.OriginIsNextByte) {
                uint8_t nextByteValue = cpu->fetchMemory();
                newValueA += nextByteValue;
            }

            *dest8reg = newValueA;

            cpu->setFlag(FlagsEnum::N, false);
            checkSumFlags8bits(orValueA, newValueA, cpu);
        }
        else if( auto dest16bits = cpu->get16bitRegister(param.AimedReg) ) {
            uint16_t orValueDest = *dest16bits;
            uint16_t newValueDest = orValueDest;

            if(auto or16bits = cpu->get16bitRegister(param.OriginReg)) {
                newValueDest += *or16bits;
                checkSumFlags16bits(orValueDest, newValueDest, cpu);
            }
            else if(param.OriginIsNextByteSigned) {
                auto value = (int8_t) cpu->fetchMemory();
                newValueDest += value;
                checkSumFlags8bits(orValueDest, newValueDest, cpu);
            }

            *dest16bits = newValueDest;
            cpu->setFlag(FlagsEnum::N, false);
        }
    }

    void ld( const InstructionParameters& params, CPU* cpu )
    {
        if( auto destReg = cpu->get8bitRegister(params.AimedReg) ) { //Se entrada for de 8 bits

            if( auto or8Reg = cpu->get8bitRegister(params.OriginReg) ) { // Se o objetivo for de 8 bits
                *destReg = *or8Reg;
            }

            else if( auto orReg = cpu->get16bitRegister(params.OriginReg) ) {
                if( params.OriginIsAddress ) {
                    *destReg = cpu->read(*orReg);

                    *orReg += params.OriginShouldIncrement ? 1 : 0;
                    *orReg -= params.OriginShouldDecrement ? 1 : 0;
                }
            }

            else if( params.OriginIsNextByte ) { //Caso o origin sejam os próximos 8 bits
                uint8_t orValue = cpu->fetchMemory(*(cpu->get16bitRegister(RegistersEnum::PC)));//cpu->regs->PC);
                *destReg = orValue;
            }

            else if( params.OriginIsNextBytes ) {
                uint8_t lsb = cpu->fetchMemory(*(cpu->get16bitRegister(RegistersEnum::PC))); //least significant byte
                uint8_t msb = cpu->fetchMemory(*(cpu->get16bitRegister(RegistersEnum::PC))); //most significant byte

                uint16_t orAddress = (msb << 8) | lsb;

                *destReg = cpu->read(orAddress);
            }

        }

        else if(auto dest16Reg = cpu->get16bitRegister(params.AimedReg)) { //Se entrada for de 16 bits

            if( params.OriginIsNextBytes ) {

                uint8_t lsb = cpu->fetchMemory(*(cpu->get16bitRegister(RegistersEnum::PC))); //least significant byte
                uint8_t msb = cpu->fetchMemory(*(cpu->get16bitRegister(RegistersEnum::PC))); //most significant byte

                uint16_t orValue = (msb << 8) | lsb;

                *dest16Reg = orValue;
            }

            else if(auto or8Reg = cpu->get8bitRegister(params.OriginReg)) { // Se o registro de origem for de 8 bits
                if(params.AimedIsAddress) { // Se deve tratar o "aimed" como endereço
                    cpu->write(*dest16Reg, *or8Reg); //copia valor do registro de 8 bits no endereço

                    *dest16Reg += params.AimShouldIncrement ? 1 : 0;
                    *dest16Reg -= params.AimShouldDecrement ? 1 : 0;
                }
            }

            else if (params.AimedReg == RegistersEnum::HL && params.OriginReg == RegistersEnum::SP)
            {
                int8_t e8 = static_cast<int8_t>(cpu->fetchMemory());
                uint16_t spOldValue = cpu->get16bitRegisterValue(RegistersEnum::SP);
                uint16_t spNewValue = cpu->get16bitRegisterValue(RegistersEnum::SP) + e8;
                checkSumFlags8bits(spOldValue, spNewValue, cpu);
                cpu->set16bitRegister(RegistersEnum::HL, spNewValue);
            }

            else if( auto or16Reg = cpu->get16bitRegister(params.OriginReg) ) {
                *dest16Reg = *or16Reg;
            }
        }

        else if( params.AimIsNextBytes && params.AimedIsAddress ) {

            uint8_t lsb = cpu->fetchMemory(); //least significant byte
            uint8_t msb = cpu->fetchMemory(); //most significant byte

            uint16_t destAdd = (msb << 8) | lsb;

            if(params.OriginReg == RegistersEnum::SP) {
                uint16_t valueSP = *(cpu->get16bitRegister(params.OriginReg));
                cpu->write(destAdd, valueSP & 0xFF);
                cpu->write(destAdd + 1, valueSP >> 8);
            }
            else if(auto orReg = cpu->get8bitRegister(params.OriginReg)) {
                cpu->write(destAdd, *orReg);
            }

        }
    }

    void orInst( const InstructionParameters& params, CPU* cpu ) {

        uint8_t value = 0;

        auto dest8reg = cpu->get8bitRegister(params.AimedReg);

        if( auto org8reg = cpu->get8bitRegister(params.OriginReg) ) {
            value = (*dest8reg | *org8reg);
        }
        else if(auto org16reg = cpu->get16bitRegister(params.OriginReg)) {
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

    void andInst(const InstructionParameters& params, CPU* cpu) {
        if(auto dest8reg = cpu->get8bitRegister(params.AimedReg)){

            uint8_t value = *dest8reg;

            if(auto or8reg = cpu->get8bitRegister(params.OriginReg)) {
                value = (*dest8reg & *or8reg);
            }
            else if(params.OriginIsNextByte) {
                uint8_t nextBit = cpu->fetchMemory();
                value = (*dest8reg & nextBit);
            }
            else if(auto or16reg = cpu->get16bitRegister(params.OriginReg)) {
                value = (*dest8reg & cpu->read(*or16reg));
            }

            *dest8reg = value;
            checkAndFlags(value, cpu);
        }
    }
}