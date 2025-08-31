#include <catch2/catch_test_macros.hpp>
#include "CPU/CPU.hpp"

TEST_CASE("CALL Z, u16 instruction working", "[call]") {

    uint8_t opcode = 0xCC; //opcode for the OR A, B

    CPU cpu = CPU();

    Instruction inst_callZa16 = cpu.getInstruction(opcode);
    cpu.executeInstruction(inst_callZa16);
}