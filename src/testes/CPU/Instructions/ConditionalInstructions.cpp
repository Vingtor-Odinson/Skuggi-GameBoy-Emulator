#include <catch2/catch_test_macros.hpp>
#include "CPU/CPU.hpp"

TEST_CASE("CALL Z, u16 instruction working", "[call]") {

    uint8_t opcode = 0xCC; //opcode for the OR A, B
    CPU cpu = CPU();
    Instruction inst_callZa16 = cpu.getInstruction(opcode);

    uint16_t addPC = 0x8500;
    uint16_t addSP = 0x8600;
    uint8_t lsbNewAdd = 0x34;
    uint8_t msbNewAdd = 0x12;

    *cpu.get16bitRegister(RegistersEnum::SP) = addSP;
    *cpu.get16bitRegister(RegistersEnum::PC) = addPC;
    cpu.write(addPC, lsbNewAdd);
    cpu.write(addPC + 1, msbNewAdd);
    cpu.setFlag(FlagsEnum::Z, true);

    cpu.executeInstruction(inst_callZa16);

    REQUIRE(*cpu.get16bitRegister(RegistersEnum::PC) == ((msbNewAdd << 8) | lsbNewAdd));
    REQUIRE(*cpu.get16bitRegister(RegistersEnum::SP) == addSP - 2);
    REQUIRE(cpu.read(addSP-1) == (addPC & 0xFF00) >> 8);
    REQUIRE(cpu.read(addSP-2) == (addPC & 0xFF) + 2); //Pois fez fetch duas vezes
}

TEST_CASE("CALL u16 instruction working", "[call]") {

    uint8_t opcode = 0xCD; //opcode for the OR A, B
    CPU cpu = CPU();
    Instruction inst_callZa16 = cpu.getInstruction(opcode);

    uint16_t addPC = 0x8500;
    uint16_t addSP = 0x8600;
    uint8_t lsbNewAdd = 0x34;
    uint8_t msbNewAdd = 0x12;

    *cpu.get16bitRegister(RegistersEnum::SP) = addSP;
    *cpu.get16bitRegister(RegistersEnum::PC) = addPC;
    cpu.write(addPC, lsbNewAdd);
    cpu.write(addPC + 1, msbNewAdd);

    cpu.executeInstruction(inst_callZa16);

    REQUIRE(*cpu.get16bitRegister(RegistersEnum::PC) == ((msbNewAdd << 8) | lsbNewAdd));
    REQUIRE(*cpu.get16bitRegister(RegistersEnum::SP) == addSP - 2);
    REQUIRE(cpu.read(addSP-1) == (addPC & 0xFF00) >> 8);
    REQUIRE(cpu.read(addSP-2) == (addPC & 0xFF) + 2); //Pois fez fetch duas vezes
}