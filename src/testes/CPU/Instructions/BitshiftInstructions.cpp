#include <catch2/catch_test_macros.hpp>
#include <Mocks/CPUMock.hpp>
#include <CPU/CPU.hpp>

TEST_CASE("RLA instruction working", "[rla]") {
    uint8_t opcode = 0x17;
    CPUMock mock = CPUMock();
    CPU cpu = *mock.getMockedCPU();
    Instruction inst = cpu.getInstruction(opcode);

    cpu.setFlag(FlagsEnum::C, true);
    cpu.set8bitRegister(RegistersEnum::A, 0b00110101);
    cpu.executeInstruction(inst);

    REQUIRE(!cpu.getFlag(FlagsEnum::C));
    REQUIRE(cpu.get8bitRegisterValue(RegistersEnum::A) == 0b01101011);
}

TEST_CASE("RL r8 instruction working", "[rl]") {
    const uint8_t opcode = 0x10; // RL B
    CPUMock mock = CPUMock();
    CPU cpu = *mock.getMockedCPU();
    const Instruction inst = cpu.getCbInstruction(opcode);

    cpu.setFlag(FlagsEnum::C, true);
    cpu.set8bitRegister(RegistersEnum::B, 0b00110101);
    cpu.executeInstruction(inst);

    REQUIRE(!cpu.getFlag(FlagsEnum::C));
    REQUIRE(!cpu.getFlag(FlagsEnum::Z));
    REQUIRE(cpu.get8bitRegisterValue(RegistersEnum::B) == 0b01101011);

    cpu.setFlag(FlagsEnum::C, false);
    cpu.set8bitRegister(RegistersEnum::B, 0b10000000);
    cpu.executeInstruction(inst);

    REQUIRE(cpu.getFlag(FlagsEnum::C));
    REQUIRE(cpu.getFlag(FlagsEnum::Z));
    REQUIRE(cpu.get8bitRegisterValue(RegistersEnum::B) == 0b00000000);
}

TEST_CASE("RL [HL] instruction working", "[rl]") {
    const uint8_t opcode = 0x16; // RL [HL]
    const uint16_t addrHL = 0x8500;
    CPUMock mock = CPUMock();
    CPU cpu = *mock.getMockedCPU();
    const Instruction inst = cpu.getCbInstruction(opcode);
    cpu.set16bitRegister(RegistersEnum::HL, addrHL);

    cpu.setFlag(FlagsEnum::C, true);
    cpu.write(addrHL, 0b00110101);
    cpu.executeInstruction(inst);

    REQUIRE(!cpu.getFlag(FlagsEnum::C));
    REQUIRE(!cpu.getFlag(FlagsEnum::Z));
    REQUIRE(cpu.read(addrHL) == 0b01101011);

    cpu.setFlag(FlagsEnum::C, false);
    cpu.write(addrHL, 0b10000000);
    cpu.executeInstruction(inst);

    REQUIRE(cpu.getFlag(FlagsEnum::C));
    REQUIRE(cpu.getFlag(FlagsEnum::Z));
    REQUIRE(cpu.read(addrHL) == 0b00000000);
}

TEST_CASE("RLCA instruction working", "[rlca]") {
    uint8_t opcode = 0x07;
    CPUMock mock = CPUMock();
    CPU cpu = *mock.getMockedCPU();
    Instruction inst = cpu.getInstruction(opcode);

    cpu.setFlag(FlagsEnum::C, true);
    cpu.set8bitRegister(RegistersEnum::A, 0b00110101);
    cpu.executeInstruction(inst);

    REQUIRE(!cpu.getFlag(FlagsEnum::C));
    REQUIRE(cpu.get8bitRegisterValue(RegistersEnum::A) == 0b01101010);
}

TEST_CASE("RLC r8 instruction working", "[rlc]") {
    uint8_t opcode = 0x00; //RLC B
    CPUMock mock = CPUMock();
    CPU cpu = *mock.getMockedCPU();
    Instruction inst = cpu.getCbInstruction(opcode);

    cpu.setFlag(FlagsEnum::C, true);
    cpu.setFlag(FlagsEnum::Z, true);
    cpu.set8bitRegister(RegistersEnum::B, 0b00110101);
    cpu.executeInstruction(inst);

    REQUIRE(!cpu.getFlag(FlagsEnum::C));
    REQUIRE(!cpu.getFlag(FlagsEnum::Z));
    REQUIRE(cpu.get8bitRegisterValue(RegistersEnum::B) == 0b01101010);
}

TEST_CASE("RLC [HL] instruction working", "[rlc]") {
    uint8_t opcode = 0x06; //RLC [HL]
    uint16_t addrHL = 0x8500;
    CPUMock mock = CPUMock();
    CPU cpu = *mock.getMockedCPU();
    Instruction inst = cpu.getCbInstruction(opcode);
    cpu.set16bitRegister(RegistersEnum::HL, addrHL);

    cpu.setFlag(FlagsEnum::C, true);
    cpu.setFlag(FlagsEnum::Z, true);
    cpu.write(addrHL, 0b00110101);
    cpu.executeInstruction(inst);

    REQUIRE(!cpu.getFlag(FlagsEnum::C));
    REQUIRE(!cpu.getFlag(FlagsEnum::Z));
    REQUIRE(cpu.read(addrHL) == 0b01101010);
}

TEST_CASE("SLA r8 instruction working", "[sla]") {
    uint8_t opcode = 0x22; //SLA D
    CPUMock mock = CPUMock();
    CPU cpu = *mock.getMockedCPU();
    Instruction inst = cpu.getCbInstruction(opcode);

    cpu.setFlag(FlagsEnum::C, true);
    cpu.setFlag(FlagsEnum::Z, true);
    cpu.set8bitRegister(RegistersEnum::D, 0b00110101);
    cpu.executeInstruction(inst);

    REQUIRE(!cpu.getFlag(FlagsEnum::C));
    REQUIRE(!cpu.getFlag(FlagsEnum::Z));
    REQUIRE(cpu.get8bitRegisterValue(RegistersEnum::D) == 0b01101010);
}

TEST_CASE("RRA instruction working", "[rra]") {
    uint8_t opcode = 0x1F;
    CPUMock mock = CPUMock();
    CPU cpu = *mock.getMockedCPU();
    Instruction inst = cpu.getInstruction(opcode);

    cpu.setFlag(FlagsEnum::C, true);
    cpu.set8bitRegister(RegistersEnum::A, 0b00110100);
    cpu.executeInstruction(inst);

    REQUIRE(!cpu.getFlag(FlagsEnum::C));
    REQUIRE(cpu.get8bitRegisterValue(RegistersEnum::A) == 0b10011010);
}

TEST_CASE("RR r8 instruction working", "[rr]") {
    const uint8_t opcode = 0x18;
    CPUMock mock = CPUMock();
    CPU cpu = *mock.getMockedCPU();
    const Instruction inst = cpu.getCbInstruction(opcode);

    cpu.setFlag(FlagsEnum::C, true);
    cpu.set8bitRegister(RegistersEnum::B, 0b00110100);
    cpu.executeInstruction(inst);

    REQUIRE(!cpu.getFlag(FlagsEnum::C));
    REQUIRE(!cpu.getFlag(FlagsEnum::Z));
    REQUIRE(cpu.get8bitRegisterValue(RegistersEnum::B) == 0b10011010);

    cpu.setFlag(FlagsEnum::C, false);
    cpu.set8bitRegister(RegistersEnum::B, 0b00000001);
    cpu.executeInstruction(inst);

    REQUIRE(cpu.getFlag(FlagsEnum::C));
    REQUIRE(cpu.getFlag(FlagsEnum::Z));
    REQUIRE(cpu.get8bitRegisterValue(RegistersEnum::B) == 0b00000000);
}

TEST_CASE("RR [HL] instruction working", "[rr]") {
    const uint8_t opcode = 0x1E;
    const uint16_t addrHL = 0x8500;
    CPUMock mock = CPUMock();
    CPU cpu = *mock.getMockedCPU();
    const Instruction inst = cpu.getCbInstruction(opcode);
    cpu.set16bitRegister(RegistersEnum::HL, addrHL);

    cpu.setFlag(FlagsEnum::C, true);
    cpu.write(addrHL, 0b00110100);
    cpu.executeInstruction(inst);

    REQUIRE(!cpu.getFlag(FlagsEnum::C));
    REQUIRE(!cpu.getFlag(FlagsEnum::Z));
    REQUIRE(cpu.read(addrHL) == 0b10011010);

    cpu.setFlag(FlagsEnum::C, false);
    cpu.write(addrHL, 0b00000001);
    cpu.executeInstruction(inst);

    REQUIRE(cpu.getFlag(FlagsEnum::C));
    REQUIRE(cpu.getFlag(FlagsEnum::Z));
    REQUIRE(cpu.read(addrHL) == 0b00000000);
}

TEST_CASE("RRCA instruction working", "[rrca]") {
    const uint8_t opcode = 0x0F;
    CPUMock mock = CPUMock();
    CPU cpu = *mock.getMockedCPU();
    const Instruction inst = cpu.getInstruction(opcode);

    cpu.setFlag(FlagsEnum::C, true);
    cpu.set8bitRegister(RegistersEnum::A, 0b00110100);
    cpu.executeInstruction(inst);

    REQUIRE(!cpu.getFlag(FlagsEnum::C));
    REQUIRE(cpu.get8bitRegisterValue(RegistersEnum::A) == 0b00011010);
}

TEST_CASE("RRC r8 instruction working", "[rrc]") {
    const uint8_t opcode = 0x08; //RRC B
    CPUMock mock = CPUMock();
    CPU cpu = *mock.getMockedCPU();
    const Instruction inst = cpu.getCbInstruction(opcode);

    cpu.setFlag(FlagsEnum::C, true);
    cpu.setFlag(FlagsEnum::Z, true);
    cpu.set8bitRegister(RegistersEnum::B, 0b00110100);
    cpu.executeInstruction(inst);

    REQUIRE(!cpu.getFlag(FlagsEnum::C));
    REQUIRE(!cpu.getFlag(FlagsEnum::Z));
    REQUIRE(cpu.get8bitRegisterValue(RegistersEnum::B) == 0b00011010);
}

TEST_CASE("RRC [HL] instruction working", "[rrc]") {
    const uint8_t opcode = 0x0E; //RRC E
    const uint16_t addrHL = 0x8500;
    CPUMock mock = CPUMock();
    CPU cpu = *mock.getMockedCPU();
    const Instruction inst = cpu.getCbInstruction(opcode);
    cpu.set16bitRegister(RegistersEnum::HL, addrHL);

    cpu.setFlag(FlagsEnum::C, true);
    cpu.setFlag(FlagsEnum::Z, true);
    cpu.write(addrHL, 0b00110100);
    cpu.executeInstruction(inst);

    REQUIRE(!cpu.getFlag(FlagsEnum::C));
    REQUIRE(!cpu.getFlag(FlagsEnum::Z));
    REQUIRE(cpu.read(addrHL) == 0b00011010);
}

TEST_CASE("SRA r8 instruction working", "[sra]") {
    uint8_t opcode = 0x2B; //SLA E
    CPUMock mock = CPUMock();
    CPU cpu = *mock.getMockedCPU();
    Instruction inst = cpu.getCbInstruction(opcode);

    cpu.setFlag(FlagsEnum::C, true);
    cpu.setFlag(FlagsEnum::Z, true);
    cpu.set8bitRegister(RegistersEnum::E, 0b00110101);
    cpu.executeInstruction(inst);

    REQUIRE(cpu.getFlag(FlagsEnum::C));
    REQUIRE(!cpu.getFlag(FlagsEnum::Z));
    REQUIRE(cpu.get8bitRegisterValue(RegistersEnum::E) == 0b00011010);
}

TEST_CASE("SRL r8 instruction working", "[srl]") {
    uint8_t opcode = 0x2B; //SLA E
    CPUMock mock = CPUMock();
    CPU cpu = *mock.getMockedCPU();
    Instruction inst = cpu.getCbInstruction(opcode);

    cpu.setFlag(FlagsEnum::C, true);
    cpu.setFlag(FlagsEnum::Z, true);
    cpu.set8bitRegister(RegistersEnum::E, 0b10110101);
    cpu.executeInstruction(inst);

    REQUIRE(cpu.getFlag(FlagsEnum::C));
    REQUIRE(!cpu.getFlag(FlagsEnum::Z));
    REQUIRE(cpu.get8bitRegisterValue(RegistersEnum::E) == 0b11011010);
}