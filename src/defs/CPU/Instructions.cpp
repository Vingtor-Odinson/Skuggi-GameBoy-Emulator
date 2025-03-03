#include <CPU/CPU.hpp>
#include <CPU/Instructions.hpp>
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

void InstructionLoader::LoadInstructions()
{
    std::ifstream file(fileLocation);

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

        for(const auto& op : value["operands"])
        {
            Operand operand;

            if( op.contains("name") && value["name"].is_string() )
            {
                operand.SetName( op["name"] );
            }
            
            if( op.contains("bytes") && value["bytes"].is_number_integer() )
            {
                operand.SetNeededBytes( op["bytes"] );
            }
            
            if( op.contains("immediate") && value["immediate"].is_boolean() )
            {
                operand.SetIsImmediate( op["immediate"] );
            }
            
            if( op.contains("decrement") && value["decrement"].is_boolean() )
            {
                operand.SetIsDecrement( op["decrement"] );
            }
            
        }

        instruction.flags.Z = value["flags"].value("Z", std::string("-"));
        instruction.flags.N = value["flags"].value("N", std::string("-"));
        instruction.flags.H = value["flags"].value("H", std::string("-"));
        instruction.flags.C = value["flags"].value("C", std::string("-"));
        

        cpu->Instructions[std::stoi(key, nullptr, 16)] = instruction;
    }

    file.close();
}