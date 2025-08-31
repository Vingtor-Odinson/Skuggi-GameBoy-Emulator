#include "CPU/Instructions/InstructionResolver.hpp"
#include "CPU/Registers.hpp"
#include "CPU/CPU.hpp"
#include "Utils/Conversors/OpMnemonicToRegEnum.hpp"

void InstructionResolver::ConfigParams( Instruction* inst, InstructionParameters& param)
{
    OpMnemonicToReg converter = OpMnemonicToReg();
    param.ArgumentNumber = 0;

    if ( (*inst).GetOperandsNumber() > 0 )
    {  
        param.ArgumentNumber += 1;

        //////////////////////////////////// Primeiro Operando /////////////////////////////////

        Operand firstOperand = (*inst).GetFirstOperand();
        
        if(firstOperand.GetName() == OperatorMnemonicEnum::n8) //alvo são os próximos 8 bytes
        {
            param.AimIsNextByte = true;
        }
        else if(firstOperand.GetName() == OperatorMnemonicEnum::e8) //alvo são os próximos 8 bytes tratado com sinal
        {
            param.AimIsNextByteSigned = true;
        }
        else if(firstOperand.GetName() == OperatorMnemonicEnum::n16) //alvo são os próximos 16 bytes
        {
            param.AimIsNextByte = true;
        }
        else if(firstOperand.GetName() == OperatorMnemonicEnum::a16) //alvo são os próximos 16 bytes
        {
            param.AimIsNextBytes = true;
            param.AimedIsAddress = true;
        }

        param.firstOpMnemonic = firstOperand.GetName();
        param.AimedReg = converter.convert(firstOperand.GetName());

        if( !firstOperand.IsImmediate() ) // Deve tratar o alvo como endereço
        {
            param.AimedIsAddress = true;
        }
        if( firstOperand.isIncrement() ){
            param.AimShouldIncrement = true;
        }
        else if( firstOperand.isDecrement() ) {
            param.AimShouldDecrement = true;
        }

        //////////////////////////////////// Segundo Operando /////////////////////////////////

        if( (*inst).GetOperandsNumber() > 1 )
        {   
            param.ArgumentNumber += 1;
            
            Operand sndOperand = (*inst).GetSecondOperand();
        
            if(sndOperand.GetName() == OperatorMnemonicEnum::n8) //alvo são os próximos 8 bytes
            {
                param.OriginIsNextByte = true;
            }
            else if(sndOperand.GetName() == OperatorMnemonicEnum::e8) //alvo são os próximos 8 bytes
            {
                param.OriginIsNextByteSigned = true;
            }
            else if(sndOperand.GetName() == OperatorMnemonicEnum::n16) //alvo são os próximos 16 bytes
            {
                param.OriginIsNextBytes = true;
            }
            else if(sndOperand.GetName() == OperatorMnemonicEnum::a16) //alvo são os próximos 16 bytes
            {
                param.OriginIsNextBytes = true;
                param.OriginIsAddress = true;
            }

            param.sndOpMnemonic = sndOperand.GetName();
            param.OriginReg = converter.convert(sndOperand.GetName());

            if( !sndOperand.IsImmediate() ) // Deve tratar o alvo como endereço
            {
                param.OriginIsAddress = true;
            }
            if( sndOperand.isIncrement() ){
                param.OriginShouldIncrement = true;
            }
            else if( sndOperand.isDecrement() ){
                param.OriginShouldDecrement = true;
            }
        }
    }

}