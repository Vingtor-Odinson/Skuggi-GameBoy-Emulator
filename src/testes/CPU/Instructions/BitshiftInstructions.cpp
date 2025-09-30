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

TEST_CASE("RRCA instruction working", "[rrca]") {
    uint8_t opcode = 0x0F;
    CPUMock mock = CPUMock();
    CPU cpu = *mock.getMockedCPU();
    Instruction inst = cpu.getInstruction(opcode);

    cpu.setFlag(FlagsEnum::C, true);
    cpu.set8bitRegister(RegistersEnum::A, 0b00110100);
    cpu.executeInstruction(inst);

    REQUIRE(!cpu.getFlag(FlagsEnum::C));
    REQUIRE(cpu.get8bitRegisterValue(RegistersEnum::A) == 0b00011010);
}