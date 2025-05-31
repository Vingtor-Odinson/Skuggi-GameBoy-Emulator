#pragma once

#include <string>
#include <stdint.h>
#include <CPU/Instructions/InstructionsParameters.hpp>

class CPU;

namespace Instructions{

    uint8_t* get8BytesReg( std::string regString, CPU* cpu );

    uint16_t* get16BytesReg( std::string regString, CPU* cpu );

    void nop( InstructionParameters param, CPU* cpu );

    void inc( InstructionParameters param, CPU* cpu ); //TODO: testar
    
    void dec( InstructionParameters param, CPU* cpu ); //TODO: testar

    void ld( InstructionParameters param, CPU* cpu ); // TODO: implementar
}

class Operand
{
    private:
        std::string name; //Tlavez trocar pra regs*
        uint8_t bytes;
        bool immediate;
        bool decrement = false;

    public:

        void SetName(std::string nome){name = nome;}
        void SetNeededBytes(uint8_t bts){bytes = bts;}   //trocar as entradas pra string e fazer cast
        void SetIsImmediate(bool imm){ immediate = imm; }
        void SetIsDecrement(bool imm){ decrement = imm; }

        std::string GetName(){return name;}
        uint8_t GetBytes(){ return bytes; }
        bool IsImmediate(){ return immediate; }
        bool IsDecrement(){ return decrement; }
};

struct Flags
{
    std::string Z;
    std::string N;
    std::string H;
    std::string C;
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
            operands = new Operand[2];
        }

        Flags flags;

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
        }

        Operand GetFirstOperand()
        {
            if(operandsNumber < 1)
            {   Operand op = Operand();
                op.SetName("0");
                op.SetNeededBytes(0);
                op.SetIsImmediate(0);
                return op;
            }
            return operands[0];
        }

        Operand GetSecondOperand()
        {
            if(operandsNumber < 2)
            {
                Operand op = Operand();
                op.SetName("0");
                op.SetNeededBytes(0);
                op.SetIsImmediate(0);
                return op;
            }
            return operands[1];
        }
};

class InstructionLoader
{
    private:
        CPU* cpu;
        std::string fileLocation = "Data/Instructions.json";

    public:
        explicit InstructionLoader(CPU* cpuPtr)
        : cpu(cpuPtr){}

        void LoadInstructions();
};