#include <catch2/catch_test_macros.hpp>
#include <Mocks/CPUMock.hpp>
#include <CPU/CPU.hpp>

TEST_CASE("CPL instruction working", "[cpl]") {
    uint8_t opcode = 0x2F;
    CPUMock cpuMock = CPUMock();
    CPU cpu = *cpuMock.getMockedCPU();
    Instruction inst = cpu.getInstruction(opcode);

    uint8_t valueA = 0b01010101;
    uint8_t valueComplementA = 0b10101010;
    cpu.set8bitRegister(RegistersEnum::A, valueA);

    cpu.executeInstruction(inst);

    REQUIRE(cpu.get8bitRegisterValue(RegistersEnum::A) == valueComplementA);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == true);

    cpu.executeInstruction(inst);

    REQUIRE(cpu.get8bitRegisterValue(RegistersEnum::A) == valueA);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == true);
}