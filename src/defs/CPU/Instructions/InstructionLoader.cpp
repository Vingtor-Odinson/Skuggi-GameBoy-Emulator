//
// Created by glauco on 05/07/25.
//

#include "CPU/Instructions/InstructionLoader.hpp"
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

const std::string InstructionLoader::fileLocation = "Data/Instructions.json";

std::unordered_map <std::string, RegistersEnum> InstructionLoader::registerNameEnumMap = {
        {"A", RegistersEnum::A},
        {"B", RegistersEnum::B},
        {"C", RegistersEnum::C},
        {"D", RegistersEnum::D},
        {"E", RegistersEnum::E},
        {"F", RegistersEnum::F},
        {"H", RegistersEnum::H},
        {"L", RegistersEnum::L},
        {"n8", RegistersEnum::n8},
        {"n16", RegistersEnum::n16},
        {"a16", RegistersEnum::a16},
        {"AF", RegistersEnum::AF},
        {"BC", RegistersEnum::BC},
        {"DE", RegistersEnum::DE},
        {"HL", RegistersEnum::HL},
        {"SP", RegistersEnum::SP},
        {"PC", RegistersEnum::PC}
};

RegistersEnum InstructionLoader::getRegisterEnum(const std::string& name) {
    auto iterator = registerNameEnumMap.find(name);
    return (iterator != registerNameEnumMap.end()) ? iterator->second : RegistersEnum::INVALID; //checa se o iterator achou algo, se sim devolve o reg, se não devolve invalid
};

std::unordered_map<uint8_t, Instruction> InstructionLoader::LoadInstructions()
{

    ////////////////////////////// Carrega a Lista de instruções do json ////////////////////////////

    std::unordered_map<uint8_t, Instruction> Instructions = std::unordered_map<uint8_t, Instruction>();

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
                    operand.SetName(getRegisterEnum(op["name"]));
                }

                if (op.contains("bytes") && value["bytes"].is_number_integer()) {
                    operand.SetNeededBytes(op["bytes"]);
                }

                if (op.contains("immediate") && value["immediate"].is_boolean()) {
                    operand.setIsImmediate(op["immediate"]);
                }

                if (op.contains("increment") && op["increment"].is_boolean()) {
                    operand.setIsIncrement(op["increment"]);
                }

                if (op.contains("decrement") && op["decrement"].is_boolean()) {
                    operand.setIsDecrement(op["decrement"]);
                }

                instruction.AddOperand(operand);
            }
        }

        instruction.flags.Z = value["flags"].value("Z", std::string("-"));
        instruction.flags.N = value["flags"].value("N", std::string("-"));
        instruction.flags.H = value["flags"].value("H", std::string("-"));
        instruction.flags.C = value["flags"].value("C", std::string("-"));


        Instructions[std::stoi(key, nullptr, 16)] = instruction;
    }

    file.close();

    return Instructions;
}
