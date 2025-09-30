#include <catch2/catch_test_macros.hpp>
#include "Mocks/CPUMock.hpp"
#include "CPU/CPU.hpp"

TEST_CASE("PUSH and POP Instructions", "[push], [pop]") {

    uint8_t opcodePUSH = 0xF5; // PUSH AF opcode
    uint8_t opcodePOP = 0xF1; // POP AF opcode
    CPUMock cpuMock = CPUMock();
    CPU cpu = *cpuMock.getMockedCPU();
    Instruction instPush = cpu.getInstruction(opcodePUSH);
    Instruction instPop = cpu.getInstruction(opcodePOP);
    cpu.set16bitRegister(RegistersEnum::SP, 0x8510);

    cpu.set16bitRegister(RegistersEnum::AF, 0xAAAA);
    cpu.executeInstruction(instPush);

    cpu.set16bitRegister(RegistersEnum::AF, 0x0000);
    cpu.executeInstruction(instPop);

    REQUIRE(cpu.get16bitRegisterValue(RegistersEnum::SP) == 0x8510);
    REQUIRE(cpu.get16bitRegisterValue(RegistersEnum::AF) == 0xAAAA);
    REQUIRE(cpu.getFlag(FlagsEnum::Z));
    REQUIRE(!cpu.getFlag(FlagsEnum::N));
    REQUIRE(cpu.getFlag(FlagsEnum::H));
    REQUIRE(!cpu.getFlag(FlagsEnum::C));
}
