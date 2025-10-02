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

TEST_CASE("RL instruction working", "[rl]") {
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

TEST_CASE("RLC instruction working", "[rlc]") {
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

TEST_CASE("RR instruction working", "[rr]") {
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

TEST_CASE("RRC instruction working", "[rrc]") {
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