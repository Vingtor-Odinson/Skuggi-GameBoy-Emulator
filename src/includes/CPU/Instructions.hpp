#pragma once

#include <string>
#include <stdint.h>

class CPU;

class Operand
{
    private:
        std::string name; //Tlavez trocar pra regs*
        uint8_t bytes;
        bool immediate;

    public:

        void SetName(std::string nome){name = nome;}
        void SetNeededBytes(uint8_t bts){bytes = bts;}
        void SetIsImmediate( bool imm ){ immediate = imm; }

        std::string GetName(){return name;}
        uint8_t GetBytes(){ return bytes; }
        bool IsImmediate(){ return immediate; }
};

class Instruction
{   
    private:
        std::string mnemonic;
        uint8_t bytes;
        uint8_t cicles;
        uint8_t operandsNumber = 0;
        Operand* operands;

    public:
        Instruction(){
            operands = new Operand[2];
        }

        std::string GetMnemonic() {return mnemonic;}

        uint8_t GetNeededBytesQtd() {return bytes;}
        uint8_t GetCiclesNumber() {return cicles;}
        uint8_t GetOperandsNumber() {return operandsNumber;}

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
        std::string fileLocation;

    public:
        InstructionLoader(CPU* cpuPtr)
        : cpu(cpuPtr){}

        void LoadInstructions();
};