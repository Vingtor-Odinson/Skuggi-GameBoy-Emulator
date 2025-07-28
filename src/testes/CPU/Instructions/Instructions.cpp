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

/* Deveria testar INC [HL]
TEST_CASE("INC BC instruction working properly", "[inc]")
{ // Pra testar esse aqui eu preciso olhar a memória
    uint8_t opcode = 0x03; //opcode for the INC BC

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
 */

TEST_CASE("INC BC instruction working properly", "[inc]")
{ // Pra testar esse aqui eu preciso olhar a memória
    uint8_t opcode = 0x03; //opcode for the INC BC

    CPU* cpu = new CPU();

    cpu->regs->BC = 0x8500;

    Instruction incBC = cpu->getInstruction(opcode);

    cpu->executeInstruction( incBC );

    REQUIRE( cpu->regs->BC == 0x8501 );

    delete cpu;
}

TEST_CASE("LD r8, r8 instruction working", "[ld]") {
    uint8_t opcode = 0x4F; //opcode for the LD

    CPU* cpu = new CPU();


    cpu->regs->A = 0x04;
    cpu->regs->C = 0x00;

    Instruction incLD_CA = cpu->getInstruction(opcode);

    cpu->executeInstruction( incLD_CA );

    REQUIRE(cpu->regs->C == 0x04);
    REQUIRE(cpu->regs->A == 0x04);

    delete cpu;
}



TEST_CASE("LD r8, n8 instruction working", "[ld]") {

    uint8_t opcode = 0x3E; //opcode for the LD

    CPU* cpu = new CPU();

    cpu->regs->A = 0x01;
    cpu->regs->PC = 0x8500; //Tem que ser em algum pedaço da memória que possa ser lido

    cpu->memory->WriteMemory(cpu->regs->PC, 0x05);

    Instruction incLD_An8 = cpu->getInstruction(opcode); //Vai colocar o A = 0x05 e aumentar o PC em 1

    cpu->executeInstruction(incLD_An8);

    REQUIRE(cpu->regs->A == 0x05);
    REQUIRE(cpu->regs->PC == 0x8501);

    delete cpu;
}

TEST_CASE("LD r8, HL instruction working", "[ld]") {

    uint8_t opcode = 0x4E; //opcode for the LD

    CPU* cpu = new CPU();

    cpu->regs->C = 0x00;
    cpu->regs->HL = 0x8500; //Tem que ser em algum pedaço da memória que possa ser lido

    cpu->memory->WriteMemory(cpu->regs->HL, 0x05);

    Instruction incLD_AHL = cpu->getInstruction(opcode);

    cpu->executeInstruction(incLD_AHL);

    REQUIRE(cpu->regs->C == 0x05);

    delete cpu;
}

TEST_CASE("LD [HL], r8 instruction working", "[ld]") {

    uint8_t opcode = 0x70;
    CPU* cpu = new CPU();

    cpu->regs->B = 0x10;

    cpu->regs->HL = 0x8500;

    cpu->memory->WriteMemory(cpu->regs->HL, 0x00);

    Instruction incLDhl_r8 = cpu->getInstruction(opcode);

    cpu->executeInstruction(incLDhl_r8);

    REQUIRE(cpu->memory->ReadMemory(cpu->regs->HL) == 0x10);

    delete cpu;
}

TEST_CASE("LD [r16], A instruction working", "[ld]") {

    uint8_t opcode = 0x02;
    CPU* cpu = new CPU();

    cpu->regs->A = 0x10;

    cpu->regs->BC = 0x8500;

    cpu->memory->WriteMemory(cpu->regs->HL, 0x00);

    Instruction incLDr16_A = cpu->getInstruction(opcode);

    cpu->executeInstruction(incLDr16_A);

    REQUIRE(cpu->memory->ReadMemory(cpu->regs->BC) == 0x10);

    delete cpu;
}

TEST_CASE("LD [n16], A instruction working", "[ld]") {

    //todo: Add the case when the address is between $FF00 and $FFFF

    uint8_t opcode = 0xEA; //opcode for the LD [n16], A

    CPU* cpu = new CPU();

    cpu->regs->A = 0x10;
    cpu->regs->PC = 0x8500; //Tem que ser em algum pedaço da memória que possa ser lido

    cpu->memory->WriteMemory(cpu->regs->PC, 0x00);
    cpu->memory->WriteMemory(cpu->regs->PC + 1, 0x85);

    Instruction incLD_n16A = cpu->getInstruction(opcode); //Vai copiar o A em 0x8520

    cpu->executeInstruction(incLD_n16A);

    REQUIRE(cpu->memory->ReadMemory(0x8500) == 0x10);

    delete cpu;
}

TEST_CASE("LD r16, n16 instruction working", "[ld]") {

    uint8_t opcode = 0x01; //opcode for the LD BC, n16

    CPU* cpu = new CPU();

    cpu->regs->BC = 0x0000;
    cpu->regs->PC = 0x8500; //Tem que ser em algum pedaço da memória que possa ser lido

    cpu->memory->WriteMemory(cpu->regs->PC, 0x34);
    cpu->memory->WriteMemory(cpu->regs->PC + 1, 0x12);

    Instruction incLD_r16n16 = cpu->getInstruction(opcode); //Vai colocar o A = 0x05 e aumentar o PC em 1

    cpu->executeInstruction(incLD_r16n16);

    REQUIRE(cpu->regs->BC == 0x1234);
    REQUIRE(cpu->regs->PC == 0x8502);

    delete cpu;
}

TEST_CASE("LD A, [r16] instruction working", "[ld]") {

    uint8_t opcode = 0x1A;
    uint16_t address = 0x8501;


    CPU* cpu = new CPU();

    cpu->regs->A = 0x00;

    cpu->regs->DE = address;

    cpu->memory->WriteMemory(address, 0x10);

    Instruction inst = cpu->getInstruction(opcode);

    cpu->executeInstruction(inst);

    REQUIRE(cpu->regs->A == 0x10);
}

TEST_CASE("LD A, [n16] instruction working", "[ld]") {

    uint8_t opcode = 0xFA;
    uint8_t value = 0x15;

    uint16_t valAddress = 0x8510;
    uint16_t address = 0x8500;

    CPU* cpu = new CPU();

    cpu->regs->A = 0x00;
    cpu->regs->PC = address;

    cpu->memory->WriteMemory(address, 0x10);
    cpu->memory->WriteMemory(address + 1, 0x85);

    cpu->memory->WriteMemory(valAddress, value);

    Instruction inst = cpu->getInstruction(opcode);

    cpu->executeInstruction(inst);

    REQUIRE(cpu->regs->A == value);
}
