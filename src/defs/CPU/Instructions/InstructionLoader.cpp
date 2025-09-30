#include "CPU/Instructions/InstructionLoader.hpp"
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <fstream>

//Todo: I really need to improve this altogether with the metadata pipeline

using json = nlohmann::json;

const std::string InstructionLoader::fileLocation = "Data/Instructions.json";

std::unordered_map<std::string, OperatorMnemonicEnum> InstructionLoader::registerNameEnumMap = {
    {"A", OperatorMnemonicEnum::A},
    {"B", OperatorMnemonicEnum::B},
    {"C", OperatorMnemonicEnum::C},
    {"D", OperatorMnemonicEnum::D},
    {"E", OperatorMnemonicEnum::E},
    {"F", OperatorMnemonicEnum::F},
    {"H", OperatorMnemonicEnum::H},
    {"L", OperatorMnemonicEnum::L},
    {"n8", OperatorMnemonicEnum::n8},
    {"e8", OperatorMnemonicEnum::e8},
    {"n16", OperatorMnemonicEnum::n16},
    {"a16", OperatorMnemonicEnum::a16},
    {"AF", OperatorMnemonicEnum::AF},
    {"BC", OperatorMnemonicEnum::BC},
    {"DE", OperatorMnemonicEnum::DE},
    {"HL", OperatorMnemonicEnum::HL},
    {"SP", OperatorMnemonicEnum::SP},
    {"PC", OperatorMnemonicEnum::PC},
    {"Z", OperatorMnemonicEnum::Z},
    {"NZ", OperatorMnemonicEnum::NZ},
    {"NC", OperatorMnemonicEnum::NC},
    {"$00", OperatorMnemonicEnum::x00},
    {"$08", OperatorMnemonicEnum::x08},
    {"$10", OperatorMnemonicEnum::x10},
    {"$18", OperatorMnemonicEnum::x18},
    {"$20", OperatorMnemonicEnum::x20},
    {"$28", OperatorMnemonicEnum::x28},
    {"$30", OperatorMnemonicEnum::x30},
    {"$38", OperatorMnemonicEnum::x38},
    {"0", OperatorMnemonicEnum::b0},
    {"1", OperatorMnemonicEnum::b1},
    {"2", OperatorMnemonicEnum::b2},
    {"3", OperatorMnemonicEnum::b3},
    {"4", OperatorMnemonicEnum::b4},
    {"5", OperatorMnemonicEnum::b5},
    {"6", OperatorMnemonicEnum::b6},
    {"7", OperatorMnemonicEnum::b7},
};

OperatorMnemonicEnum InstructionLoader::getRegisterEnum(const std::string& name)
{
    auto iterator = registerNameEnumMap.find(name);
    return (iterator != registerNameEnumMap.end()) ? iterator->second : OperatorMnemonicEnum::INVALID;
};

std::unordered_map<uint8_t, Instruction> InstructionLoader::LoadInstructions()
{
    ////////////////////////////// Carrega a Lista de instruções do json ////////////////////////////

    std::unordered_map<uint8_t, Instruction> Instructions = std::unordered_map<uint8_t, Instruction>();

    std::ifstream file;

    file.open(fileLocation);

    if (!file.is_open())
    {
        throw std::runtime_error("Não foi possível abrir o arquivo de instruções");
    }

    json jsonData = json::parse(file);

    for (auto& [key, value] : jsonData["unprefixed"].items())
    {
        Instruction instruction;

        if (value.contains("mnemonic") && value["mnemonic"].is_string())
        {
            instruction.SetMnemonic(value["mnemonic"]);
        }

        if (value.contains("bytes") && value["bytes"].is_number_integer())
        {
            instruction.SetNeededBytesQtd(value["bytes"]);
        }

        if (value.contains("cycles") && !value["cycles"].empty())
        {
            instruction.SetCiclesNumber(value["cycles"][0]);
        }

        if (value.contains("immediate") && value["immediate"].is_boolean())
        {
            instruction.SetImmediate(value["immediate"]);
        }

        if (value.contains("operands") && value["operands"].is_array() && !value["operands"].empty())
        {
            for (const auto& op : value["operands"])
            {
                Operand operand;

                if (op.contains("name"))
                {
                    operand.SetName(getRegisterEnum(op["name"]));
                }

                if (op.contains("bytes") && value["bytes"].is_number_integer())
                {
                    operand.SetNeededBytes(op["bytes"]);
                }

                if (op.contains("immediate") && value["immediate"].is_boolean())
                {
                    operand.setIsImmediate(op["immediate"]);
                }

                if (op.contains("increment") && op["increment"].is_boolean())
                {
                    operand.setIsIncrement(op["increment"]);
                }

                if (op.contains("decrement") && op["decrement"].is_boolean())
                {
                    operand.setIsDecrement(op["decrement"]);
                }

                instruction.AddOperand(operand);
            }
        }

        Instructions[std::stoi(key, nullptr, 16)] = instruction;
    }

    file.close();

    return Instructions;
}
