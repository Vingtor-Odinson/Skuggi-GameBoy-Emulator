#include <catch2/catch_test_macros.hpp>
#include "Mocks/CPUMock.hpp"
#include "CPU/CPU.hpp"

TEST_CASE("CCF instruction working", "[ccf]") {
    uint8_t opcode = 0x3F;
    CPUMock cpuMock = CPUMock();
    CPU cpu = *cpuMock.getMockedCPU();

    cpu.setFlag(FlagsEnum::C, false);

    Instruction inst_CCF = cpu.getInstruction(opcode);
    cpu.executeInstruction(inst_CCF);

    REQUIRE(cpu.getFlag(FlagsEnum::C));

    cpu.executeInstruction(inst_CCF);

    REQUIRE(!cpu.getFlag(FlagsEnum::C));
}

TEST_CASE("SCF instruction working", "[scf]") {
    uint8_t opcode = 0x37;
    CPUMock cpuMock = CPUMock();
    CPU cpu = *cpuMock.getMockedCPU();

    cpu.setFlag(FlagsEnum::C, false);

    Instruction inst_CCF = cpu.getInstruction(opcode);
    cpu.executeInstruction(inst_CCF);

    REQUIRE(cpu.getFlag(FlagsEnum::C));

    cpu.executeInstruction(inst_CCF);

    REQUIRE(cpu.getFlag(FlagsEnum::C));
}
