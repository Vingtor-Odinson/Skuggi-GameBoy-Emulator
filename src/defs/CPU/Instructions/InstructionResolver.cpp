#include "CPU/Instructions/InstructionResolver.hpp"
#include "CPU/Registers.hpp"
#include "CPU/CPU.hpp"

void InstructionResolver::ConfigParams( Instruction* inst, InstructionParameters& param)
{
    param.ArgumentNumber = 0;

    if ( (*inst).GetOperandsNumber() > 0 )
    {  
        param.ArgumentNumber += 1;

        //////////////////////////////////// Primeiro Operando /////////////////////////////////

        Operand firstOperand = (*inst).GetFirstOperand();
        
        if(firstOperand.GetName() == RegistersEnum::n8) //alvo são os próximos 8 bytes
        {
            param.AimIsNextByte = true;
        }
        else if(firstOperand.GetName() == RegistersEnum::n16) //alvo são os próximos 16 bytes
        {
            param.AimIsNextByte = true;
        }
        else if(firstOperand.GetName() == RegistersEnum::a16) //alvo são os próximos 16 bytes
        {
            param.AimIsNextBytes = true;
            param.AimedIsAddress = true;
        }


        param.AimedReg = firstOperand.GetName();

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
        
            if(sndOperand.GetName() == RegistersEnum::n8) //alvo são os próximos 8 bytes
            {
                param.OriginIsNextByte = true;
            }
            else if(sndOperand.GetName() == RegistersEnum::n16) //alvo são os próximos 16 bytes
            {
                param.OriginIsNextBytes = true;
            }
            else if(sndOperand.GetName() == RegistersEnum::a16) //alvo são os próximos 16 bytes
            {
                param.OriginIsNextBytes = true;
                param.OriginIsAddress = true;
            }

            param.OriginReg = sndOperand.GetName();

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