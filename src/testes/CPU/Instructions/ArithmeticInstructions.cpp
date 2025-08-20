#include <catch2/catch_test_macros.hpp>
#include <CPU/CPU.hpp>

TEST_CASE("ADC A, r8 instruction working", "[adc]") {

    uint8_t opcode = 0x88; //opcode for the OR A, B

    CPU cpu = CPU();

    uint8_t valueA = 0x00;
    uint8_t valueB = 0x00;

    *cpu.getRegister<uint8_t *>(RegistersEnum::A) = valueA;
    *cpu.getRegister<uint8_t *>(RegistersEnum::B) = valueB;

    Instruction instADC_Ar8 = cpu.getInstruction(opcode);
    cpu.executeInstruction(instADC_Ar8);

    REQUIRE(*cpu.getRegister<uint8_t *>(RegistersEnum::A) == 0x00);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == false);

    valueA = 0x0F;
    valueB = 0x01;

    *cpu.getRegister<uint8_t *>(RegistersEnum::A) = valueA;
    *cpu.getRegister<uint8_t *>(RegistersEnum::B) = valueB;

    cpu.executeInstruction(instADC_Ar8);

    REQUIRE(*cpu.getRegister<uint8_t *>(RegistersEnum::A) == 0x10);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == true);

    valueA = 0xF0;
    valueB = 0x10;

    *cpu.getRegister<uint8_t *>(RegistersEnum::A) = valueA;
    *cpu.getRegister<uint8_t *>(RegistersEnum::B) = valueB;

    cpu.executeInstruction(instADC_Ar8);

    REQUIRE(*cpu.getRegister<uint8_t *>(RegistersEnum::A) == 0x00);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == false);

    valueA = 0xFF;
    valueB = 0x01;

    *cpu.getRegister<uint8_t *>(RegistersEnum::A) = valueA;
    *cpu.getRegister<uint8_t *>(RegistersEnum::B) = valueB;

    cpu.executeInstruction(instADC_Ar8);

    REQUIRE(*cpu.getRegister<uint8_t *>(RegistersEnum::A) == 1); //Because of the carry above
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == true);
}

TEST_CASE("ADC A, [HL] instruction working", "[adc]") {

    uint8_t opcode = 0x8E; //opcode for the OR A, B
    uint16_t addrHL = 0x8510;

    CPU cpu = CPU();

    uint8_t valueA = 0x00;
    uint8_t valueB = 0x00;

    *cpu.getRegister<uint8_t*>(RegistersEnum::A) = valueA;
    *cpu.getRegister<uint16_t*>(RegistersEnum::HL) = addrHL;
    cpu.write(addrHL, valueB);

    Instruction instADC_AHL = cpu.getInstruction(opcode);
    cpu.executeInstruction(instADC_AHL);

    REQUIRE(*cpu.getRegister<uint8_t *>(RegistersEnum::A) == 0x00);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == false);

    valueA = 0x0F;
    valueB = 0x01;

    *cpu.getRegister<uint8_t *>(RegistersEnum::A) = valueA;
    cpu.write(addrHL, valueB);

    cpu.executeInstruction(instADC_AHL);

    REQUIRE(*cpu.getRegister<uint8_t *>(RegistersEnum::A) == 0x10);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == true);

    valueA = 0xF0;
    valueB = 0x10;

    *cpu.getRegister<uint8_t *>(RegistersEnum::A) = valueA;
    cpu.write(addrHL, valueB);

    cpu.executeInstruction(instADC_AHL);

    REQUIRE(*cpu.getRegister<uint8_t *>(RegistersEnum::A) == 0x00);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == false);

    valueA = 0xFF;
    valueB = 0x01;

    *cpu.getRegister<uint8_t *>(RegistersEnum::A) = valueA;
    cpu.write(addrHL, valueB);

    cpu.executeInstruction(instADC_AHL);

    REQUIRE(*cpu.getRegister<uint8_t *>(RegistersEnum::A) == 1); //Because of the carry above
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == true);
}

TEST_CASE("ADC A, n8 instruction working", "[adc]") {

    uint8_t opcode = 0xCE; //opcode for the OR A, B
    uint16_t addrPC = 0x8500;

    CPU cpu = CPU();

    uint8_t valueA = 0x00;
    uint8_t valueB = 0x00;

    *cpu.getRegister<uint8_t*>(RegistersEnum::A) = valueA;
    *cpu.getRegister<uint16_t*>(RegistersEnum::PC) = addrPC;
    cpu.write(addrPC, valueB);

    Instruction instADC_AHL = cpu.getInstruction(opcode);
    cpu.executeInstruction(instADC_AHL);

    REQUIRE(*cpu.getRegister<uint8_t *>(RegistersEnum::A) == 0x00);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == false);

    valueA = 0x0F;
    valueB = 0x01;

    *cpu.getRegister<uint8_t *>(RegistersEnum::A) = valueA;
    cpu.write(addrPC+0x01, valueB);

    cpu.executeInstruction(instADC_AHL);

    REQUIRE(*cpu.getRegister<uint8_t *>(RegistersEnum::A) == 0x10);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == true);

    valueA = 0xF0;
    valueB = 0x10;

    *cpu.getRegister<uint8_t *>(RegistersEnum::A) = valueA;
    cpu.write(addrPC+2, valueB);

    cpu.executeInstruction(instADC_AHL);

    REQUIRE(*cpu.getRegister<uint8_t *>(RegistersEnum::A) == 0x00);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == false);

    valueA = 0xFF;
    valueB = 0x01;

    *cpu.getRegister<uint8_t *>(RegistersEnum::A) = valueA;
    cpu.write(addrPC+3, valueB);

    cpu.executeInstruction(instADC_AHL);

    REQUIRE(*cpu.getRegister<uint8_t *>(RegistersEnum::A) == 1); //Because of the carry above
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == true);
}

TEST_CASE("ADD A, r8 instruction working", "[add]") {

    uint8_t opcode = 0x80; //opcode for the OR A, B

    CPU cpu = CPU();

    uint8_t valueA = 0x00;
    uint8_t valueB = 0x00;

    *cpu.getRegister<uint8_t *>(RegistersEnum::A) = valueA;
    *cpu.getRegister<uint8_t *>(RegistersEnum::B) = valueB;

    Instruction instADD_Ar8 = cpu.getInstruction(opcode);
    cpu.executeInstruction(instADD_Ar8);

    REQUIRE(*cpu.getRegister<uint8_t *>(RegistersEnum::A) == 0x00);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == false);

    valueA = 0x0F;
    valueB = 0x01;

    *cpu.getRegister<uint8_t *>(RegistersEnum::A) = valueA;
    *cpu.getRegister<uint8_t *>(RegistersEnum::B) = valueB;

    cpu.executeInstruction(instADD_Ar8);

    REQUIRE(*cpu.getRegister<uint8_t *>(RegistersEnum::A) == 0x10);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == true);

    valueA = 0xF0;
    valueB = 0x10;

    *cpu.getRegister<uint8_t *>(RegistersEnum::A) = valueA;
    *cpu.getRegister<uint8_t *>(RegistersEnum::B) = valueB;

    cpu.executeInstruction(instADD_Ar8);

    REQUIRE(*cpu.getRegister<uint8_t *>(RegistersEnum::A) == 0x00);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == false);

    valueA = 0xFF;
    valueB = 0x01;

    *cpu.getRegister<uint8_t *>(RegistersEnum::A) = valueA;
    *cpu.getRegister<uint8_t *>(RegistersEnum::B) = valueB;

    cpu.executeInstruction(instADD_Ar8);

    REQUIRE(*cpu.getRegister<uint8_t *>(RegistersEnum::A) == 0x00); //Because it ignores the carry flag above
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == true);
}

TEST_CASE("ADD A, [HL] instruction working", "[add]") {

    uint8_t opcode = 0x86; //opcode for the OR A, B
    uint16_t addrHL = 0x8510;

    CPU cpu = CPU();

    uint8_t valueA = 0x00;
    uint8_t valueB = 0x00;

    *cpu.getRegister<uint8_t*>(RegistersEnum::A) = valueA;
    *cpu.getRegister<uint16_t*>(RegistersEnum::HL) = addrHL;
    cpu.write(addrHL, valueB);

    Instruction instADD_AHL = cpu.getInstruction(opcode);
    cpu.executeInstruction(instADD_AHL);

    REQUIRE(*cpu.getRegister<uint8_t *>(RegistersEnum::A) == 0x00);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == false);

    valueA = 0x0F;
    valueB = 0x01;

    *cpu.getRegister<uint8_t *>(RegistersEnum::A) = valueA;
    cpu.write(addrHL, valueB);

    cpu.executeInstruction(instADD_AHL);

    REQUIRE(*cpu.getRegister<uint8_t *>(RegistersEnum::A) == 0x10);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == true);

    valueA = 0xF0;
    valueB = 0x10;

    *cpu.getRegister<uint8_t *>(RegistersEnum::A) = valueA;
    cpu.write(addrHL, valueB);

    cpu.executeInstruction(instADD_AHL);

    REQUIRE(*cpu.getRegister<uint8_t *>(RegistersEnum::A) == 0x00);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == false);

    valueA = 0xFF;
    valueB = 0x01;

    *cpu.getRegister<uint8_t *>(RegistersEnum::A) = valueA;
    cpu.write(addrHL, valueB);

    cpu.executeInstruction(instADD_AHL);

    REQUIRE(*cpu.getRegister<uint8_t *>(RegistersEnum::A) == 0); //Because it ignores the carry flag above
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == true);
}

TEST_CASE("ADD A, n8 instruction working", "[add]") {

    uint8_t opcode = 0xC6; //opcode for the OR A, B
    uint16_t addrPC = 0x8500;

    CPU cpu = CPU();

    uint8_t valueA = 0x00;
    uint8_t valueB = 0x00;

    *cpu.getRegister<uint8_t*>(RegistersEnum::A) = valueA;
    *cpu.getRegister<uint16_t*>(RegistersEnum::PC) = addrPC;
    cpu.write(addrPC, valueB);

    Instruction instADD_n8 = cpu.getInstruction(opcode);
    cpu.executeInstruction(instADD_n8);

    REQUIRE(*cpu.getRegister<uint8_t *>(RegistersEnum::A) == 0x00);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == false);

    valueA = 0x0F;
    valueB = 0x01;

    *cpu.getRegister<uint8_t *>(RegistersEnum::A) = valueA;
    cpu.write(addrPC+0x01, valueB);

    cpu.executeInstruction(instADD_n8);

    REQUIRE(*cpu.getRegister<uint8_t *>(RegistersEnum::A) == 0x10);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == true);

    valueA = 0xF0;
    valueB = 0x10;

    *cpu.getRegister<uint8_t *>(RegistersEnum::A) = valueA;
    cpu.write(addrPC+2, valueB);

    cpu.executeInstruction(instADD_n8);

    REQUIRE(*cpu.getRegister<uint8_t *>(RegistersEnum::A) == 0x00);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == false);

    valueA = 0xFF;
    valueB = 0x01;

    *cpu.getRegister<uint8_t *>(RegistersEnum::A) = valueA;
    cpu.write(addrPC+3, valueB);

    cpu.executeInstruction(instADD_n8);

    REQUIRE(*cpu.getRegister<uint8_t *>(RegistersEnum::A) == 0); //Because it ignores the carry flag above
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == true);
}