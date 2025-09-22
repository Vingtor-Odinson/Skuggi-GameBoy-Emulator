#include <catch2/catch_test_macros.hpp>
#include "Mocks/CPUMock.hpp"
#include "CPU/CPU.hpp"

TEST_CASE("EI and DI instructions working", "[ei], [di]") {

    uint8_t opcode;
    CPUMock cpuMock = CPUMock();
    CPU cpu = *cpuMock.getMockedCPU();
    Instruction inst;

    cpu.setIME();
    opcode = 0xF3; // DI opcode
    inst = cpu.getInstruction(opcode);
    cpu.executeInstruction(inst);

    REQUIRE(!cpu.getIME());

    opcode = 0xFB; // EI opcode
    inst = cpu.getInstruction(opcode);
    cpu.executeInstruction(inst);

    REQUIRE(!cpu.getIME());

    opcode = 0xF3; // DI opcode
    inst = cpu.getInstruction(opcode);
    cpu.executeInstruction(inst);

    REQUIRE(cpu.getIME());
}