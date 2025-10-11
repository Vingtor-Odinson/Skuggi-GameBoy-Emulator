#include <catch2/catch_test_macros.hpp>
#include "Mocks/CPUMock.hpp"
#include <CPU/CPU.hpp>

TEST_CASE("LDH a8, A instruction working properly", "[ldh]")
{
    const uint8_t opcode = 0xE0;
    const uint16_t addrPC = 0x8500;
    CPUMock mock = CPUMock();
    CPU cpu = *mock.getMockedCPU();
    const Instruction inst = cpu.getInstruction(opcode);
    cpu.set16bitRegister(RegistersEnum::PC, addrPC);

    cpu.write(addrPC, 0x10);
    cpu.set8bitRegister(RegistersEnum::A, opcode);
    cpu.executeInstruction(inst);

    REQUIRE(cpu.read(0xFF10) == opcode);
}

TEST_CASE("LDH C, A instruction working properly", "[ldh]")
{
    const uint8_t opcode = 0xE2;
    CPUMock mock = CPUMock();
    CPU cpu = *mock.getMockedCPU();
    const Instruction inst = cpu.getInstruction(opcode);

    cpu.set8bitRegister(RegistersEnum::C, 0x10);
    cpu.set8bitRegister(RegistersEnum::A, opcode);
    cpu.executeInstruction(inst);

    REQUIRE(cpu.read(0xFF10) == opcode);
}

TEST_CASE("LDH A, a8 instruction working properly", "[ldh]")
{
    const uint8_t opcode = 0xF0;
    const uint16_t addrPC = 0x8500;
    CPUMock mock = CPUMock();
    CPU cpu = *mock.getMockedCPU();
    const Instruction inst = cpu.getInstruction(opcode);
    cpu.set16bitRegister(RegistersEnum::PC, addrPC);

    cpu.write(addrPC, 0x10);
    cpu.write(0xFF10, opcode);
    cpu.executeInstruction(inst);

    REQUIRE(cpu.get8bitRegisterValue(RegistersEnum::A) == opcode);
}

TEST_CASE("LDH A, C instruction working properly", "[ldh]")
{
    const uint8_t opcode = 0xF2;
    CPUMock mock = CPUMock();
    CPU cpu = *mock.getMockedCPU();
    const Instruction inst = cpu.getInstruction(opcode);

    cpu.set8bitRegister(RegistersEnum::C, 0x10);
    cpu.write(0xFF10, opcode);
    cpu.executeInstruction(inst);

    REQUIRE(cpu.get8bitRegisterValue(RegistersEnum::A) == opcode);
}

TEST_CASE("LD HL, SP + e8 instruction working", "[ld]")
{
    const uint8_t opcode = 0xF8;
    const uint16_t addrPC = 0x8500;
    CPUMock mock = CPUMock();
    CPU cpu = *mock.getMockedCPU();
    const Instruction inst = cpu.getInstruction(opcode);

    cpu.write(addrPC, -10);
    cpu.set16bitRegister(RegistersEnum::PC, addrPC);
    cpu.set16bitRegister(RegistersEnum::SP, 0x1234);
    cpu.set16bitRegister(RegistersEnum::HL, 0x00);

    cpu.executeInstruction(inst);

    REQUIRE(cpu.get16bitRegisterValue(RegistersEnum::HL) == 0x122A);
}