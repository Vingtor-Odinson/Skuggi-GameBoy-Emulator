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
        
        if(firstOperand.GetName() == "e8") //alvo são os próximos 8 bytes
        {
            param.AimIsNextByte = true;
        }
        else if(firstOperand.GetName() == "a8") //alvo são os próximos 16 bytes
        {
            param.AimIsNextByte = true;
        }
        else{
            param.AimedReg = firstOperand.GetName();
        }

        if( firstOperand.IsImmediate() ) // Deve tratar o alvo como endereço
        {
            param.AimedIsAddress = true;
        }

        //////////////////////////////////// Segundo Operando /////////////////////////////////

        if( (*inst).GetOperandsNumber() > 1 )
        {   
            param.ArgumentNumber += 1;
            
            Operand sndOperand = (*inst).GetSecondOperand();
        
            if(sndOperand.GetName() == "e8") //alvo são os próximos 8 bytes
            {
                param.OriginIsNextByte = true;
            }
            else if(sndOperand.GetName() == "a8") //alvo são os próximos 16 bytes
            {
                param.OriginIsNextBytes = true;
            }
            else{
                param.OriginReg = sndOperand.GetName();
            }

            if( sndOperand.IsImmediate() ) // Deve tratar o alvo como endereço
            {
                param.OriginIsAddress = true;
            }
        }
    }

}