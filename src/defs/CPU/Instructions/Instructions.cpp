#include <CPU/CPU.hpp>
#include <Memoria/Memory.hpp>
#include <CPU/Instructions/Instructions.hpp>
#include <CPU/Registers.hpp>
#include <CPU/Instructions/InstructionResolver.hpp>
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

namespace Instructions{

    uint8_t* get8BytesReg( std::string regString, CPU* cpu )
    {
        if(regString == "A")
        {
            return &(cpu->regs->A);
        }
        else if(regString == "B")
        {
            return &(cpu->regs->B);
        }
        else if(regString == "C")
        {
            return &(cpu->regs->C);
        }
        else if(regString == "D")
        {
            return &(cpu->regs->D);
        }
        else if(regString == "E")
        {
            return &(cpu->regs->E);
        }
        else if(regString == "H")
        {
            return &(cpu->regs->H);
        }
        else if(regString == "L")
        {
            return &(cpu->regs->L);
        }

        return nullptr;
    }

    uint16_t* get16BytesReg( std::string regString, CPU* cpu )
    {
        if(regString == "AF")
        {
            return &(cpu->regs->AF);
        }
        else if(regString == "BC")
        {
            return &(cpu->regs->BC);
        }
        else if(regString == "DE")
        {
            return &(cpu->regs->DE);
        }
        else if(regString == "HL")
        {
            return &(cpu->regs->HL);
        }
        else if(regString == "SP")
        {
            return &(cpu->regs->SP);
        }

        return nullptr;
    }

    void nop( InstructionParameters params, CPU* cpu ){}

    void inc( InstructionParameters params, CPU* cpu )
    {  
        if( get8BytesReg( params.AimedReg, cpu ) != nullptr )
        {
            uint8_t* reg = get8BytesReg( params.AimedReg, cpu );
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

        if( get16BytesReg( params.AimedReg, cpu ) != nullptr )
        {
            uint16_t* add = get16BytesReg( params.AimedReg, cpu );

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
        if ( get16BytesReg( params.AimedReg, cpu ) != nullptr )
        {   
            uint16_t* reg = get16BytesReg( params.AimedReg, cpu );
            (*reg) -= 1;
        }
        else if ( get8BytesReg( params.AimedReg, cpu ) != nullptr )
        {   
            uint8_t* reg = get8BytesReg( params.AimedReg, cpu );

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
        
    }
}

void InstructionLoader::LoadInstructions()
{

    ////////////////////////////// Carrega a Lista de instruções do json ////////////////////////////

    std::ifstream file;

    file.open(fileLocation);

    if (!file.is_open()) {
        throw std::runtime_error("Não foi possível abrir o arquivo de instruções");
    }

    json jsonData = json::parse(file);

    for(auto& [key, value] : jsonData["unprefixed"].items() )
    {
        Instruction instruction;

        if( value.contains("mnemonic") && value["mnemonic"].is_string() )
        {
            instruction.SetMnemonic(value["mnemonic"]);
        }

        if( value.contains("bytes") && value["bytes"].is_number_integer() )
        {
            instruction.SetNeededBytesQtd( value["bytes"] );
        }
        
        if( value.contains("cycles") && !value["cycles"].empty() )
        {
            instruction.SetCiclesNumber( value["cycles"][0] );
        }

        if(value.contains("immediate") && value["immediate"].is_boolean())
        {
            instruction.SetImmediate( value["immediate"] );
        }

        if( value.contains("operands") && value["operands"].is_array() && !value["operands"].empty() )
        {
            for (const auto &op: value["operands"]) {
                Operand operand;

                if (op.contains("name")) {
                    operand.SetName(op["name"]);
                }

                if (op.contains("bytes") && value["bytes"].is_number_integer()) {
                    operand.SetNeededBytes(op["bytes"]);
                }

                if (op.contains("immediate") && value["immediate"].is_boolean()) {
                    operand.SetIsImmediate(op["immediate"]);
                }

                if (op.contains("decrement") && value["decrement"].is_boolean()) {
                    operand.SetIsDecrement(op["decrement"]);
                }
                instruction.AddOperand(operand);
            }
        }

        instruction.flags.Z = value["flags"].value("Z", std::string("-"));
        instruction.flags.N = value["flags"].value("N", std::string("-"));
        instruction.flags.H = value["flags"].value("H", std::string("-"));
        instruction.flags.C = value["flags"].value("C", std::string("-"));
        

        cpu->Instructions[std::stoi(key, nullptr, 16)] = instruction;
    }

    file.close();

    //////////////////////// Carrega as funções no mapa de funções /////////////////

    cpu->InstructionMap["NOP"] = Instructions::nop;
    cpu->InstructionMap["INC"] = Instructions::inc;
    cpu->InstructionMap["DEC"] = Instructions::dec;
    cpu->InstructionMap["LD"]  = Instructions::ld;
    
}