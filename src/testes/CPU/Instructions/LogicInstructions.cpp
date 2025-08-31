#include <catch2/catch_test_macros.hpp>
#include "CPU/CPU.hpp"

TEST_CASE("AND A, r8 instruction working", "[and]") {

    uint8_t opcode = 0xA0; // AND A, B opcode
    CPU cpu = CPU();

    // Tests the Z flag

    *cpu.get8bitRegister(RegistersEnum::A) = 0x10;
    *cpu.get8bitRegister(RegistersEnum::B) = 0x00;

    Instruction inst_AndAr8 = cpu.getInstruction(opcode);
    cpu.executeInstruction(inst_AndAr8);

    REQUIRE(*cpu.get8bitRegister(RegistersEnum::A) == 0x00);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == false);

    // Tests a normal case

    *cpu.get8bitRegister(RegistersEnum::A) = 0b10;
    *cpu.get8bitRegister(RegistersEnum::B) = 0b11;

    cpu.executeInstruction(inst_AndAr8);

    REQUIRE(*cpu.get8bitRegister(RegistersEnum::A) == 0b10);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == false);
}

TEST_CASE("AND A, [HL] instruction working", "[and]") {

    uint8_t opcode = 0xA6; // AND A, [HL] opcode
    CPU cpu = CPU();

    // Tests the Z flag

    uint8_t valueA = 0x10;
    uint8_t value = 0x00;
    uint16_t addrHL = 0x8510;

    *cpu.get8bitRegister(RegistersEnum::A) = valueA;
    *cpu.get16bitRegister(RegistersEnum::HL) = addrHL;
    cpu.write(addrHL, value);

    Instruction inst_AndAr8 = cpu.getInstruction(opcode);
    cpu.executeInstruction(inst_AndAr8);

    REQUIRE(*cpu.get8bitRegister(RegistersEnum::A) == 0x00);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == false);

    // Tests a normal case

    valueA = 0b10;
    value = 0b11;

    *cpu.get8bitRegister(RegistersEnum::A) = valueA;
    *cpu.get16bitRegister(RegistersEnum::HL) = addrHL;
    cpu.write(addrHL, value);

    cpu.executeInstruction(inst_AndAr8);

    REQUIRE(*cpu.get8bitRegister(RegistersEnum::A) == 0b10);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == false);
}

TEST_CASE("AND A, n8 instruction working", "[and]") {

    uint8_t opcode = 0xE6; // AND A, n8 opcode
    CPU cpu = CPU();

    // Tests the Z flag

    uint8_t valueA = 0x10;
    uint8_t value = 0x00;
    uint16_t addrPC = 0x8510;

    *cpu.get8bitRegister(RegistersEnum::A) = valueA;
    *cpu.get16bitRegister(RegistersEnum::PC) = addrPC;
    cpu.write(addrPC, value);

    Instruction inst_AndAr8 = cpu.getInstruction(opcode);
    cpu.executeInstruction(inst_AndAr8);

    REQUIRE(*cpu.get8bitRegister(RegistersEnum::A) == 0x00);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == false);

    // Tests a normal case

    valueA = 0b10;
    value = 0b11;

    *cpu.get8bitRegister(RegistersEnum::A) = valueA;
    cpu.write(addrPC + 1, value);

    cpu.executeInstruction(inst_AndAr8);

    REQUIRE(*cpu.get8bitRegister(RegistersEnum::A) == 0b10);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == false);
}

TEST_CASE("OR A, r8 instruction working", "[or]") {

    uint8_t opcode = 0xB0; //opcode for the OR A, B
    uint8_t valueA = 0x10;
    uint8_t valueB = 0x11;

    CPU* cpu = new CPU();

    *cpu->get8bitRegister(RegistersEnum::A) = valueA;
    *cpu->get8bitRegister(RegistersEnum::B) = valueB;

    Instruction incOR_AB = cpu->getInstruction(opcode);
    cpu->executeInstruction(incOR_AB);

    REQUIRE(*cpu->get8bitRegister(RegistersEnum::A) == (valueA | valueB) );
    REQUIRE(!cpu->getFlag(FlagsEnum::N));
    REQUIRE(!cpu->getFlag(FlagsEnum::H));
    REQUIRE(!cpu->getFlag(FlagsEnum::C));

    *cpu->get8bitRegister(RegistersEnum::A) = 0x00;
    *cpu->get8bitRegister(RegistersEnum::B) = 0x00;

    cpu->executeInstruction(incOR_AB);

    REQUIRE(*cpu->get8bitRegister(RegistersEnum::A) == 0x00 );
    REQUIRE(cpu->getFlag(FlagsEnum::Z));

    delete cpu;
}

TEST_CASE("OR A, [HL] instruction working", "[or]") {

    uint8_t opcode = 0xB6; //opcode for the OR A, [HL]
    uint16_t addrHL = 0x8510;
    uint8_t valueA = 0x10;
    uint8_t valueB = 0x11;

    CPU* cpu = new CPU();

    *cpu->get8bitRegister(RegistersEnum::A) = valueA;
    *cpu->get16bitRegister(RegistersEnum::HL) = addrHL;
    cpu->write(addrHL, valueB);

    Instruction incOR_AHL = cpu->getInstruction(opcode);
    cpu->executeInstruction(incOR_AHL);

    REQUIRE(*cpu->get8bitRegister(RegistersEnum::A) == (valueA | valueB) );
    REQUIRE(!cpu->getFlag(FlagsEnum::N));
    REQUIRE(!cpu->getFlag(FlagsEnum::H));
    REQUIRE(!cpu->getFlag(FlagsEnum::C));

    *cpu->get8bitRegister(RegistersEnum::A) = 0x00;
    cpu->write(addrHL, 0x00);

    cpu->executeInstruction(incOR_AHL);

    REQUIRE(*cpu->get8bitRegister(RegistersEnum::A) == 0x00 );
    REQUIRE(cpu->getFlag(FlagsEnum::Z));

    delete cpu;
}

TEST_CASE("OR A, n8 instruction working", "[or]") {

    uint8_t opcode = 0xF6; //opcode for the OR A, B
    uint16_t addrPC = 0x8510;
    uint8_t valueA = 0x10;
    uint8_t valueB = 0x11;

    CPU* cpu = new CPU();

    *cpu->get8bitRegister(RegistersEnum::A) = valueA;
    *cpu->get16bitRegister(RegistersEnum::PC) = addrPC;
    cpu->write(addrPC, valueB);

    Instruction incOR_Ar8 = cpu->getInstruction(opcode);
    cpu->executeInstruction(incOR_Ar8);

    REQUIRE(*cpu->get8bitRegister(RegistersEnum::A) == (valueA | valueB) );
    REQUIRE(!cpu->getFlag(FlagsEnum::N));
    REQUIRE(!cpu->getFlag(FlagsEnum::H));
    REQUIRE(!cpu->getFlag(FlagsEnum::C));

    *cpu->get8bitRegister(RegistersEnum::A) = 0x00;
    cpu->write(addrPC + 1, 0x00);

    cpu->executeInstruction(incOR_Ar8);

    REQUIRE(*cpu->get8bitRegister(RegistersEnum::A) == 0x00 );
    REQUIRE(cpu->getFlag(FlagsEnum::Z));

    delete cpu;
}