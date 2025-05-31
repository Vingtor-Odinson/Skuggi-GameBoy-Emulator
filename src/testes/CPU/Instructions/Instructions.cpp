#include <catch2/catch_test_macros.hpp>
#include <CPU/CPU.hpp>
#include <CPU/Registers.hpp>
#include <CPU/Instructions/Instructions.hpp>
#include <CPU/Instructions/InstructionResolver.hpp>

TEST_CASE("INC B instruction working properly", "[inc]")
{
    uint8_t opcode = 0x04; //opcode for the INC B

    CPU* cpu = new CPU();

    cpu->regs->B = 0x00;

    Instruction incB = cpu->getInstruction(opcode);
    
    cpu->executeInstruction( incB );


    REQUIRE(cpu->regs->B == 0x01); // Simple one, the third bit doesn't change
    REQUIRE( cpu->flags->N == "0" );

    delete cpu;
}