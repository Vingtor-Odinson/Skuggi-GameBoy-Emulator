#pragma once

#include <string>
#include <stdint.h>
#include <unordered_map>
#include <CPU/Instructions/InstructionsParameters.hpp>
#include "enum/OperatorMnemonicEnum.hpp"

class CPU;

namespace Instructions{

    void nop( const InstructionParameters& param, CPU* cpu );

    void inc( const InstructionParameters& param, CPU* cpu ); //TODO: arrumar o teste
    
    void adc(const InstructionParameters& param, CPU* cpu);

    void add(const InstructionParameters& param, CPU* cpu);

    void daa(const InstructionParameters& param, CPU* cpu);
    
    void dec( const InstructionParameters& param, CPU* cpu ); //TODO: testar

    void sub(const InstructionParameters& param, CPU* cpu);

    void sbc(const InstructionParameters& param, CPU* cpu);

    void cp(const InstructionParameters& param, CPU* cpu);

    void cpl(const InstructionParameters& param, CPU* cpu);

    void ld( const InstructionParameters& param, CPU* cpu ); // TODO: implementar as variantes que dependem da região de registros do sistema

    void orInst( const InstructionParameters&, CPU* );

    void andInst(const InstructionParameters&, CPU*);

    void xorInst(const InstructionParameters&, CPU*);

    void call(const InstructionParameters&, CPU*);

    void jp(const InstructionParameters&, CPU*);

    void jr(const InstructionParameters&, CPU*);

    void ccf(const InstructionParameters&, CPU*);

    void scf(const InstructionParameters&, CPU*);

    void rla (const InstructionParameters&, CPU*);

    void rl (const InstructionParameters&, CPU*);

    void rlca (const InstructionParameters&, CPU*);

    void rlc (const InstructionParameters&, CPU*);

    void sla (const InstructionParameters&, CPU*);

    void rra (const InstructionParameters&, CPU*);

    void rr (const InstructionParameters&, CPU*);

    void rrca (const InstructionParameters&, CPU*);

    void rrc (const InstructionParameters&, CPU*);

    void swap (const InstructionParameters&, CPU*);

    void set (const InstructionParameters&, CPU*);

    void res (const InstructionParameters&, CPU*);

    void bit (const InstructionParameters&, CPU*);

    void sra (const InstructionParameters&, CPU*);

    void srl (const InstructionParameters&, CPU*);

    void ei(const InstructionParameters& param, CPU* cpu);

    void di(const InstructionParameters& param, CPU* cpu);

    void push(const InstructionParameters& param, CPU* cpu);

    void pop(const InstructionParameters& param, CPU* cpu);

    void ret(const InstructionParameters& param, CPU* cpu);

    void reti(const InstructionParameters& param, CPU* cpu);

    void rst(const InstructionParameters& param, CPU* cpu);

    void halt(const InstructionParameters& param, CPU* cpu);
}

class Operand
{
    private:
        OperatorMnemonicEnum name; //Tlavez trocar pra regs*
        uint8_t bytes;
        bool immediate;
        bool increment = false;
        bool decrement = false;

    public:

        void SetName(OperatorMnemonicEnum nome){ name = nome;}
        void SetNeededBytes(uint8_t bts){bytes = bts;}   //trocar as entradas pra string e fazer cast
        void setIsImmediate(bool imm){ immediate = imm; }
        void setIsIncrement(bool imm) { increment = imm; }
        void setIsDecrement(bool imm){ decrement = imm; }

        OperatorMnemonicEnum GetName(){return name;}
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
        uint8_t getCiclesNumber() {return cicles;}
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
                op.SetName(OperatorMnemonicEnum::INVALID);
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
                op.SetName(OperatorMnemonicEnum::INVALID);
                op.SetNeededBytes(0);
                op.setIsImmediate(false);
                return op;
            }
            return operands[1];
        }
};