#include <catch2/catch_test_macros.hpp>
#include <CPU/CPU.hpp>

TEST_CASE("ADC A, r8 instruction working", "[adc]") {

    uint8_t opcode = 0x88; //opcode for the OR A, B

    CPU cpu = CPU();

    uint8_t valueA = 0x00;
    uint8_t valueB = 0x00;

    *cpu.get8bitRegister(RegistersEnum::A) = valueA;
    *cpu.get8bitRegister(RegistersEnum::B) = valueB;

    Instruction instADC_Ar8 = cpu.getInstruction(opcode);
    cpu.executeInstruction(instADC_Ar8);

    REQUIRE(*cpu.get8bitRegister(RegistersEnum::A) == 0x00);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == false);

    valueA = 0x0F;
    valueB = 0x01;

    *cpu.get8bitRegister(RegistersEnum::A) = valueA;
    *cpu.get8bitRegister(RegistersEnum::B) = valueB;

    cpu.executeInstruction(instADC_Ar8);

    REQUIRE(*cpu.get8bitRegister(RegistersEnum::A) == 0x10);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == true);

    valueA = 0xF0;
    valueB = 0x10;

    *cpu.get8bitRegister(RegistersEnum::A) = valueA;
    *cpu.get8bitRegister(RegistersEnum::B) = valueB;

    cpu.executeInstruction(instADC_Ar8);

    REQUIRE(*cpu.get8bitRegister(RegistersEnum::A) == 0x00);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == false);

    valueA = 0xFF;
    valueB = 0x01;

    *cpu.get8bitRegister(RegistersEnum::A) = valueA;
    *cpu.get8bitRegister(RegistersEnum::B) = valueB;

    cpu.executeInstruction(instADC_Ar8);

    REQUIRE(*cpu.get8bitRegister(RegistersEnum::A) == 1); //Because of the carry above
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

    *cpu.get8bitRegister(RegistersEnum::A) = valueA;
    *cpu.get16bitRegister(RegistersEnum::HL) = addrHL;
    cpu.write(addrHL, valueB);

    Instruction instADC_AHL = cpu.getInstruction(opcode);
    cpu.executeInstruction(instADC_AHL);

    REQUIRE(*cpu.get8bitRegister(RegistersEnum::A) == 0x00);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == false);

    valueA = 0x0F;
    valueB = 0x01;

    *cpu.get8bitRegister(RegistersEnum::A) = valueA;
    cpu.write(addrHL, valueB);

    cpu.executeInstruction(instADC_AHL);

    REQUIRE(*cpu.get8bitRegister(RegistersEnum::A) == 0x10);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == true);

    valueA = 0xF0;
    valueB = 0x10;

    *cpu.get8bitRegister(RegistersEnum::A) = valueA;
    cpu.write(addrHL, valueB);

    cpu.executeInstruction(instADC_AHL);

    REQUIRE(*cpu.get8bitRegister(RegistersEnum::A) == 0x00);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == false);

    valueA = 0xFF;
    valueB = 0x01;

    *cpu.get8bitRegister(RegistersEnum::A) = valueA;
    cpu.write(addrHL, valueB);

    cpu.executeInstruction(instADC_AHL);

    REQUIRE(*cpu.get8bitRegister(RegistersEnum::A) == 1); //Because of the carry above
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

    *cpu.get8bitRegister(RegistersEnum::A) = valueA;
    *cpu.get16bitRegister(RegistersEnum::PC) = addrPC;
    cpu.write(addrPC, valueB);

    Instruction instADC_AHL = cpu.getInstruction(opcode);
    cpu.executeInstruction(instADC_AHL);

    REQUIRE(*cpu.get8bitRegister(RegistersEnum::A) == 0x00);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == false);

    valueA = 0x0F;
    valueB = 0x01;

    *cpu.get8bitRegister(RegistersEnum::A) = valueA;
    cpu.write(addrPC+0x01, valueB);

    cpu.executeInstruction(instADC_AHL);

    REQUIRE(*cpu.get8bitRegister(RegistersEnum::A) == 0x10);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == true);

    valueA = 0xF0;
    valueB = 0x10;

    *cpu.get8bitRegister(RegistersEnum::A) = valueA;
    cpu.write(addrPC+2, valueB);

    cpu.executeInstruction(instADC_AHL);

    REQUIRE(*cpu.get8bitRegister(RegistersEnum::A) == 0x00);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == false);

    valueA = 0xFF;
    valueB = 0x01;

    *cpu.get8bitRegister(RegistersEnum::A) = valueA;
    cpu.write(addrPC+3, valueB);

    cpu.executeInstruction(instADC_AHL);

    REQUIRE(*cpu.get8bitRegister(RegistersEnum::A) == 1); //Because of the carry above
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

    *cpu.get8bitRegister(RegistersEnum::A) = valueA;
    *cpu.get8bitRegister(RegistersEnum::B) = valueB;

    Instruction instADD_Ar8 = cpu.getInstruction(opcode);
    cpu.executeInstruction(instADD_Ar8);

    REQUIRE(*cpu.get8bitRegister(RegistersEnum::A) == 0x00);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == false);

    valueA = 0x0F;
    valueB = 0x01;

    *cpu.get8bitRegister(RegistersEnum::A) = valueA;
    *cpu.get8bitRegister(RegistersEnum::B) = valueB;

    cpu.executeInstruction(instADD_Ar8);

    REQUIRE(*cpu.get8bitRegister(RegistersEnum::A) == 0x10);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == true);

    valueA = 0xF0;
    valueB = 0x10;

    *cpu.get8bitRegister(RegistersEnum::A) = valueA;
    *cpu.get8bitRegister(RegistersEnum::B) = valueB;

    cpu.executeInstruction(instADD_Ar8);

    REQUIRE(*cpu.get8bitRegister(RegistersEnum::A) == 0x00);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == false);

    valueA = 0xFF;
    valueB = 0x01;

    *cpu.get8bitRegister(RegistersEnum::A) = valueA;
    *cpu.get8bitRegister(RegistersEnum::B) = valueB;

    cpu.executeInstruction(instADD_Ar8);

    REQUIRE(*cpu.get8bitRegister(RegistersEnum::A) == 0x00); //Because it ignores the carry flag above
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

    *cpu.get8bitRegister(RegistersEnum::A) = valueA;
    *cpu.get16bitRegister(RegistersEnum::HL) = addrHL;
    cpu.write(addrHL, valueB);

    Instruction instADD_AHL = cpu.getInstruction(opcode);
    cpu.executeInstruction(instADD_AHL);

    REQUIRE(*cpu.get8bitRegister(RegistersEnum::A) == 0x00);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == false);

    valueA = 0x0F;
    valueB = 0x01;

    *cpu.get8bitRegister(RegistersEnum::A) = valueA;
    cpu.write(addrHL, valueB);

    cpu.executeInstruction(instADD_AHL);

    REQUIRE(*cpu.get8bitRegister(RegistersEnum::A) == 0x10);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == true);

    valueA = 0xF0;
    valueB = 0x10;

    *cpu.get8bitRegister(RegistersEnum::A) = valueA;
    cpu.write(addrHL, valueB);

    cpu.executeInstruction(instADD_AHL);

    REQUIRE(*cpu.get8bitRegister(RegistersEnum::A) == 0x00);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == false);

    valueA = 0xFF;
    valueB = 0x01;

    *cpu.get8bitRegister(RegistersEnum::A) = valueA;
    cpu.write(addrHL, valueB);

    cpu.executeInstruction(instADD_AHL);

    REQUIRE(*cpu.get8bitRegister(RegistersEnum::A) == 0); //Because it ignores the carry flag above
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

    *cpu.get8bitRegister(RegistersEnum::A) = valueA;
    *cpu.get16bitRegister(RegistersEnum::PC) = addrPC;
    cpu.write(addrPC, valueB);

    Instruction instADD_n8 = cpu.getInstruction(opcode);
    cpu.executeInstruction(instADD_n8);

    REQUIRE(*cpu.get8bitRegister(RegistersEnum::A) == 0x00);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == false);

    valueA = 0x0F;
    valueB = 0x01;

    *cpu.get8bitRegister(RegistersEnum::A) = valueA;
    cpu.write(addrPC+0x01, valueB);

    cpu.executeInstruction(instADD_n8);

    REQUIRE(*cpu.get8bitRegister(RegistersEnum::A) == 0x10);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == true);

    valueA = 0xF0;
    valueB = 0x10;

    *cpu.get8bitRegister(RegistersEnum::A) = valueA;
    cpu.write(addrPC+2, valueB);

    cpu.executeInstruction(instADD_n8);

    REQUIRE(*cpu.get8bitRegister(RegistersEnum::A) == 0x00);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == false);

    valueA = 0xFF;
    valueB = 0x01;

    *cpu.get8bitRegister(RegistersEnum::A) = valueA;
    cpu.write(addrPC+3, valueB);

    cpu.executeInstruction(instADD_n8);

    REQUIRE(*cpu.get8bitRegister(RegistersEnum::A) == 0); //Because it ignores the carry flag above
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == true);
}

TEST_CASE("ADD HL, r16 instruction working", "[add]") {

    uint8_t opcode = 0x09; //opcode for the ADD HL, BC
    CPU cpu = CPU();

    //Tests 15th bit overflow and value

    uint16_t valueHL = 0xFFFF;
    uint16_t valueBC = 0x0010;

    *cpu.get16bitRegister(RegistersEnum::HL) = valueHL;
    *cpu.get16bitRegister(RegistersEnum::BC) = valueBC;

    Instruction instADD_HLBC = cpu.getInstruction(opcode);
    cpu.executeInstruction(instADD_HLBC);

    REQUIRE(*cpu.get16bitRegister(RegistersEnum::HL) == 0x000F);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == false);

    // Tests 11th bit overflow value and flags

    valueHL = 0x0800;
    valueBC = 0x0002;

    *cpu.get16bitRegister(RegistersEnum::HL) = valueHL;
    *cpu.get16bitRegister(RegistersEnum::BC) = valueBC;

    cpu.executeInstruction(instADD_HLBC);

    REQUIRE(*cpu.get16bitRegister(RegistersEnum::HL) == 0x0802);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == true);

    //Testes 11th and 15th bit overflow and value

    valueHL = 0xF800;
    valueBC = 0x1002;

    *cpu.get16bitRegister(RegistersEnum::HL) = valueHL;
    *cpu.get16bitRegister(RegistersEnum::BC) = valueBC;

    cpu.executeInstruction(instADD_HLBC);

    REQUIRE(*cpu.get16bitRegister(RegistersEnum::HL) == 0x0802);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == true);
}

TEST_CASE("ADD HL, SP instruction working", "[add]") {

    uint8_t opcode = 0x39; //opcode for the ADD HL, BC
    CPU cpu = CPU();

    //Tests 15th bit overflow and value

    uint16_t valueHL = 0xFFFF;
    uint16_t valueSP = 0x0010;

    *cpu.get16bitRegister(RegistersEnum::HL) = valueHL;
    *cpu.get16bitRegister(RegistersEnum::SP) = valueSP;

    Instruction instADD_HLSP = cpu.getInstruction(opcode);
    cpu.executeInstruction(instADD_HLSP);

    REQUIRE(*cpu.get16bitRegister(RegistersEnum::HL) == 0x000F);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == false);

    // Tests 11th bit overflow value and flags

    valueHL = 0x0800;
    valueSP = 0x0002;

    *cpu.get16bitRegister(RegistersEnum::HL) = valueHL;
    *cpu.get16bitRegister(RegistersEnum::SP) = valueSP;

    cpu.executeInstruction(instADD_HLSP);

    REQUIRE(*cpu.get16bitRegister(RegistersEnum::HL) == 0x0802);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == true);

    //Testes 11th and 15th bit overflow and value

    valueHL = 0xF800;
    valueSP = 0x1002;

    *cpu.get16bitRegister(RegistersEnum::HL) = valueHL;
    *cpu.get16bitRegister(RegistersEnum::SP) = valueSP;

    cpu.executeInstruction(instADD_HLSP);

    REQUIRE(*cpu.get16bitRegister(RegistersEnum::HL) == 0x0802);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == true);
}

TEST_CASE("ADD SP, e8 instruction working", "[add]") {

    uint8_t opcode = 0xE8; //opcode for the ADD HL, BC
    CPU cpu = CPU();

    //Tests the sum

    uint16_t valueSP = 0x0010;
    uint16_t addrPC = 0x8500;
    uint8_t valueRegister = 0x01;

    *cpu.get16bitRegister(RegistersEnum::PC) = addrPC;
    *cpu.get16bitRegister(RegistersEnum::SP) = valueSP;
    cpu.write(addrPC, valueRegister);

    Instruction instADD_SPe8 = cpu.getInstruction(opcode);
    cpu.executeInstruction(instADD_SPe8);

    REQUIRE(*cpu.get16bitRegister(RegistersEnum::SP) == 0x0011);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == false);

    //Tests the overflow from 3rd bit

    valueSP = 0x000F;
    addrPC = 0x8500;
    valueRegister = 0x01;

    *cpu.get16bitRegister(RegistersEnum::PC) = addrPC;
    *cpu.get16bitRegister(RegistersEnum::SP) = valueSP;
    cpu.write(addrPC, valueRegister);

    cpu.executeInstruction(instADD_SPe8);

    REQUIRE(*cpu.get16bitRegister(RegistersEnum::SP) == 0x0010);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == true);

    //Tests the overflow from 7nd bit

    valueSP = 0x00F0;
    addrPC = 0x8500;
    valueRegister = 0x10;

    *cpu.get16bitRegister(RegistersEnum::PC) = addrPC;
    *cpu.get16bitRegister(RegistersEnum::SP) = valueSP;
    cpu.write(addrPC, valueRegister);

    cpu.executeInstruction(instADD_SPe8);

    REQUIRE(*cpu.get16bitRegister(RegistersEnum::SP) == 0x0100);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == false);

    //Tests the overflow of 3rd and 7th bit

    valueSP = 0x00FF;
    addrPC = 0x8500;
    valueRegister = 0x01;

    *cpu.get16bitRegister(RegistersEnum::PC) = addrPC;
    *cpu.get16bitRegister(RegistersEnum::SP) = valueSP;
    cpu.write(addrPC, valueRegister);

    cpu.executeInstruction(instADD_SPe8);

    REQUIRE(*cpu.get16bitRegister(RegistersEnum::SP) == 0x0100);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == true);

    //Tests subtraction

    valueSP = 0x0010;
    addrPC = 0x8500;
    valueRegister = 0b11111111; //The computer reads the first byte as a negative symbol... This value is equivalent to -1

    *cpu.get16bitRegister(RegistersEnum::PC) = addrPC;
    *cpu.get16bitRegister(RegistersEnum::SP) = valueSP;
    cpu.write(addrPC, valueRegister);

    cpu.executeInstruction(instADD_SPe8);

    REQUIRE(*cpu.get16bitRegister(RegistersEnum::SP) == 0x000F);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == false);
}

TEST_CASE("DEC r8, instruction working", "[dec]") {
    uint8_t opcode = 0x05;
    CPU cpu = CPU();
    Instruction dec = cpu.getInstruction(opcode);

    *cpu.get8bitRegister(RegistersEnum::B) = 0x10; //Tests the carry flag

    cpu.executeInstruction(dec);

    REQUIRE(*cpu.get8bitRegister(RegistersEnum::B) == 0x0F);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == true);

    *cpu.get8bitRegister(RegistersEnum::B) = 0x01; //Tests the Zero flag

    cpu.executeInstruction(dec);

    REQUIRE(*cpu.get8bitRegister(RegistersEnum::B) == 0x00);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == false);

    *cpu.get8bitRegister(RegistersEnum::B) = 0x0A; //Tests a non flag operation

    cpu.executeInstruction(dec);

    REQUIRE(*cpu.get8bitRegister(RegistersEnum::B) == 0x09);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == false);
}

TEST_CASE("DEC r16 instruction working", "[dec]") {
    uint8_t opcode = 0x3B; //DEC SP
    CPU cpu = CPU();
    Instruction inst = cpu.getInstruction(opcode);

    *cpu.get16bitRegister(RegistersEnum::SP) = 0x000A;
    cpu.executeInstruction(inst);

    REQUIRE(*cpu.get16bitRegister(RegistersEnum::SP) == 0x0009);
}

TEST_CASE("DEC HL instruction working", "[dec]") {
    uint8_t opcode = 0x2B; //DEC HL
    CPU cpu = CPU();
    Instruction inst = cpu.getInstruction(opcode);

    *cpu.get16bitRegister(RegistersEnum::HL) = 0x000A;
    cpu.executeInstruction(inst);

    REQUIRE(*cpu.get16bitRegister(RegistersEnum::HL) == 0x0009);
}

TEST_CASE("DEC (HL) instruction working", "[dec]") {
    uint8_t opcode = 0x35;
    CPU cpu = CPU();
    Instruction dec = cpu.getInstruction(opcode);
    uint16_t addr = 0x8500;
    *cpu.get16bitRegister(RegistersEnum::HL) = addr;


    cpu.write(addr, 0x10); //Tests the carry flag

    cpu.executeInstruction(dec);

    REQUIRE(cpu.read(addr) == 0x0F);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == true);

    cpu.write(addr, 0x01); //Tests the Zero flag

    cpu.executeInstruction(dec);

    REQUIRE(cpu.read(addr) == 0x00);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == false);

    cpu.write(addr, 0x0A); //Tests a non flag operation

    cpu.executeInstruction(dec);

    REQUIRE(cpu.read(addr) == 0x09);
    REQUIRE(cpu.getFlag(FlagsEnum::Z) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::N) == true);
    REQUIRE(cpu.getFlag(FlagsEnum::C) == false);
    REQUIRE(cpu.getFlag(FlagsEnum::H) == false);
}
