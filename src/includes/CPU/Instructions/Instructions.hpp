#pragma once

#include <string>
#include <stdint.h>
#include <unordered_map>
#include <CPU/Instructions/InstructionsParameters.hpp>
#include "enum/RegistersEnum.hpp"

class CPU;

namespace Instructions{

    void nop( const InstructionParameters& param, CPU* cpu );

    void inc( const InstructionParameters& param, CPU* cpu ); //TODO: arrumar o teste
    
    void adc(const InstructionParameters& param, CPU* cpu);

    void add(const InstructionParameters& param, CPU* cpu);
    
    void dec( const InstructionParameters& param, CPU* cpu ); //TODO: testar

    void ld( const InstructionParameters& param, CPU* cpu ); // TODO: implementar as variantes que dependem da região de registros do sistema

    void orInst( const InstructionParameters&, CPU* );

    void andInst(const InstructionParameters&, CPU*);
}

class Operand
{
    private:
        RegistersEnum name; //Tlavez trocar pra regs*
        uint8_t bytes;
        bool immediate;
        bool increment = false;
        bool decrement = false;

    public:

        void SetName(RegistersEnum nome){name = nome;}
        void SetNeededBytes(uint8_t bts){bytes = bts;}   //trocar as entradas pra string e fazer cast
        void setIsImmediate(bool imm){ immediate = imm; }
        void setIsIncrement(bool imm) { increment = imm; }
        void setIsDecrement(bool imm){ decrement = imm; }

        RegistersEnum GetName(){return name;}
        uint8_t GetBytes(){ return bytes; }
        bool IsImmediate(){ return immediate; }
        bool isIncrement(){ return increment; }
        bool isDecrement(){ return decrement; }
};

class Instruction
{   
    private:
        std::string mnemonic;
        uint8_t bytes;
        uint8_t cicles;
        uint8_t operandsNumber = 0;
        Operand* operands;
        bool immediate;
        

    public:
        Instruction(){
            operands = new Operand[10];
        }

        void SetMnemonic( std::string name ){ mnemonic = name; }
        void SetNeededBytesQtd( uint8_t value ){ bytes = value; }
        void SetCiclesNumber( uint8_t value ){ cicles = value; }
        void SetImmediate(bool imm){ immediate = imm; }

        std::string GetMnemonic() {return mnemonic;}
        uint8_t GetNeededBytesQtd() {return bytes;}
        uint8_t GetCiclesNumber() {return cicles;}
        uint8_t GetOperandsNumber() {return operandsNumber;}
        bool IsImmediate(){return immediate;}

        void AddOperand( Operand operado )
        {
            operands[operandsNumber] = operado;
            operandsNumber++;
        }

        Operand GetFirstOperand()
        {
            if(operandsNumber < 1)
            {   Operand op = Operand();
                op.SetName(RegistersEnum::INVALID);
                op.SetNeededBytes(0);
                op.setIsImmediate(false);
                return op;
            }
            return operands[0];
        }

        Operand GetSecondOperand()
        {
            if(operandsNumber < 2)
            {
                Operand op = Operand();
                op.SetName(RegistersEnum::INVALID);
                op.SetNeededBytes(0);
                op.setIsImmediate(false);
                return op;
            }
            return operands[1];
        }
};