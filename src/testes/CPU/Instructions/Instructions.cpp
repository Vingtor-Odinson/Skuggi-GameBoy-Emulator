#include <catch2/catch_test_macros.hpp>
#include <CPU/CPU.hpp>
#include <CPU/Registers.hpp>
#include <CPU/Instructions/Instructions.hpp>
#include <CPU/Instructions/InstructionResolver.hpp>

#include <Memoria/Memory.hpp>

TEST_CASE("INC B instruction working properly", "[inc]")
{
    uint8_t opcode = 0x04; //opcode for the INC B

    CPU* cpu = new CPU();

    cpu->regs->B = 0x00;

    Instruction incB = cpu->getInstruction(opcode);
    
    cpu->executeInstruction( incB );

    REQUIRE(cpu->regs->B == 0x01); // Simple one, the third bit doesn't change
    REQUIRE( cpu->flags->N == "0" );

    cpu->regs->B = 0b01111;
    cpu->executeInstruction( incB );

    REQUIRE( cpu->regs->B == 0b10000 );
    REQUIRE( cpu->flags->H == "1" );

    delete cpu;
}

TEST_CASE("INC BC instruction working properly", "[inc]")
{ // Pra testar esse aqui eu preciso olhar a memória
    uint8_t opcode = 0x03; //opcode for the INC B

    CPU* cpu = new CPU();

    uint16_t address = 0x8500; //Tem que ser em algum pedaço da memória que possa ser lido em

    cpu->memory->WriteMemory(address, 0x00);

    cpu->regs->BC = address;

    Instruction incBC = cpu->getInstruction(opcode);

    cpu->executeInstruction( incBC );

    REQUIRE(cpu->memory->ReadMemory(address) == 0x01); // Simple one, the third bit doesn't change
    REQUIRE( cpu->flags->N == "0" );

    cpu->flags->H == "1";

    cpu->memory->WriteMemory(address, 0b1111);

    cpu->executeInstruction( incBC );

    REQUIRE(cpu->memory->ReadMemory(address) == 0b10000); // Simple one, the third bit doesn't change
    REQUIRE( cpu->flags->H == "1" );

    delete cpu;
}
