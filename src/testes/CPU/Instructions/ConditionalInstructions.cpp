#include <catch2/catch_test_macros.hpp>
#include "Mocks/CPUMock.hpp"
#include "CPU/CPU.hpp"

TEST_CASE("CALL Z, u16 instruction working", "[call]") {

    uint8_t opcode = 0xCC; //opcode for the OR A, B
    CPUMock cpuMock = CPUMock();
    CPU cpu = *cpuMock.getMockedCPU();
    Instruction inst_callZa16 = cpu.getInstruction(opcode);

    uint16_t addPC = 0x8500;
    uint16_t addSP = 0x8600;
    uint8_t lsbNewAdd = 0x34;
    uint8_t msbNewAdd = 0x12;

    *cpu.get16bitRegister(RegistersEnum::SP) = addSP;
    *cpu.get16bitRegister(RegistersEnum::PC) = addPC;
    cpu.write(addPC, lsbNewAdd);
    cpu.write(addPC + 1, msbNewAdd);
    cpu.setFlag(FlagsEnum::Z, true);

    cpu.executeInstruction(inst_callZa16);

    REQUIRE(*cpu.get16bitRegister(RegistersEnum::PC) == ((msbNewAdd << 8) | lsbNewAdd));
    REQUIRE(*cpu.get16bitRegister(RegistersEnum::SP) == addSP - 2);
    REQUIRE(cpu.read(addSP-1) == (addPC & 0xFF00) >> 8);
    REQUIRE(cpu.read(addSP-2) == (addPC & 0xFF) + 2); //Pois fez fetch duas vezes
}

TEST_CASE("CALL u16 instruction working", "[call]") {

    uint8_t opcode = 0xCD; //opcode for the OR A, B
    CPUMock cpuMock = CPUMock();
    CPU cpu = *cpuMock.getMockedCPU();
    Instruction inst_callZa16 = cpu.getInstruction(opcode);

    uint16_t addPC = 0x8500;
    uint16_t addSP = 0x8600;
    uint8_t lsbNewAdd = 0x34;
    uint8_t msbNewAdd = 0x12;

    *cpu.get16bitRegister(RegistersEnum::SP) = addSP;
    *cpu.get16bitRegister(RegistersEnum::PC) = addPC;
    cpu.write(addPC, lsbNewAdd);
    cpu.write(addPC + 1, msbNewAdd);

    cpu.executeInstruction(inst_callZa16);

    REQUIRE(*cpu.get16bitRegister(RegistersEnum::PC) == ((msbNewAdd << 8) | lsbNewAdd));
    REQUIRE(*cpu.get16bitRegister(RegistersEnum::SP) == addSP - 2);
    REQUIRE(cpu.read(addSP-1) == (addPC & 0xFF00) >> 8);
    REQUIRE(cpu.read(addSP-2) == (addPC & 0xFF) + 2); //Pois fez fetch duas vezes
}

TEST_CASE("JP u16 instruction working", "[jp]") {

    uint8_t opcode = 0xC3; //opcode for the OR A, B
    CPUMock cpuMock = CPUMock();
    CPU cpu = *cpuMock.getMockedCPU();
    Instruction inst_jpu16 = cpu.getInstruction(opcode);

    uint16_t addPC = 0x8500;
    uint16_t address = 0x8500;
    uint8_t lsbNewAdd = 0x34;
    uint8_t msbNewAdd = 0x12;

    *cpu.get16bitRegister(RegistersEnum::PC) = addPC;
    cpu.write(address, lsbNewAdd);
    cpu.write(address + 1, msbNewAdd);

    cpu.executeInstruction(inst_jpu16);

    REQUIRE(*cpu.get16bitRegister(RegistersEnum::PC) == 0x1234); //Pois fez fetch duas vezes
}

TEST_CASE("JP HL instruction working", "[jp]") {

    uint8_t opcode = 0xE9; //opcode for the JP, HL
    CPUMock cpuMock = CPUMock();
    CPU cpu = *cpuMock.getMockedCPU();
    Instruction inst_jpuhl = cpu.getInstruction(opcode);

    uint16_t addPC = 0x8000;
    uint16_t addHL = 0x1234;

    *cpu.get16bitRegister(RegistersEnum::PC) = addPC;
    *cpu.get16bitRegister(RegistersEnum::HL) = addHL;

    cpu.executeInstruction(inst_jpuhl);

    REQUIRE(*cpu.get16bitRegister(RegistersEnum::PC) == addHL);
}

TEST_CASE("JP cc, u16 instruction working", "[jp]") {

    uint8_t opcode = 0xCA; //opcode for the JP Z, u16
    CPUMock cpuMock = CPUMock();
    CPU cpu = *cpuMock.getMockedCPU();
    Instruction inst_jpu16 = cpu.getInstruction(opcode);

    uint16_t addPC = 0x8500;
    uint16_t address = 0x8500;
    uint8_t lsbNewAdd = 0x34;
    uint8_t msbNewAdd = 0x12;

    *cpu.get16bitRegister(RegistersEnum::PC) = addPC;
    cpu.write(address, lsbNewAdd);
    cpu.write(address + 1, msbNewAdd);

    cpu.executeInstruction(inst_jpu16);

    REQUIRE(*cpu.get16bitRegister(RegistersEnum::PC) == 0x8500);

    cpu.setFlag(FlagsEnum::Z, true);
    cpu.executeInstruction(inst_jpu16);

    REQUIRE(*cpu.get16bitRegister(RegistersEnum::PC) == 0x1234);
}

TEST_CASE("JR u16 instruction working", "[jr]") {

    uint8_t opcode = 0x18; //opcode for the JR u16
    CPUMock cpuMock = CPUMock();
    CPU cpu = *cpuMock.getMockedCPU();
    Instruction inst_jru16 = cpu.getInstruction(opcode);

    uint16_t iAddr = 0x8500;
    uint8_t  offset = 0x00;

    *cpu.get16bitRegister(RegistersEnum::PC) = iAddr;
    cpu.write(iAddr, offset);

    cpu.executeInstruction(inst_jru16);
    iAddr++;
    REQUIRE(*cpu.get16bitRegister(RegistersEnum::PC) == iAddr); //Se offset = 0 não muda o ponteiro

    offset = 0x01;
    cpu.write(iAddr, offset);
    cpu.executeInstruction(inst_jru16);
    iAddr++;
    REQUIRE(*cpu.get16bitRegister(RegistersEnum::PC) == iAddr + 1); //Se offset = 1 aumenta o PC em 1
    iAddr++; //Pra deixar igual o PC

    offset = 0xFF;
    cpu.write(iAddr, offset);
    cpu.executeInstruction(inst_jru16);
    iAddr++;
    REQUIRE(*cpu.get16bitRegister(RegistersEnum::PC) == iAddr - 1); //Se offset = 1 diminui o PC em 1
}

TEST_CASE("JR cc, u16 instruction working", "[jr]") {

    uint8_t opcode = 0x38; //opcode for the JP C, u16
    CPUMock cpuMock = CPUMock();
    CPU cpu = *cpuMock.getMockedCPU();
    Instruction inst_jru16 = cpu.getInstruction(opcode);
    cpu.setFlag(FlagsEnum::C, true);

    uint16_t iAddr = 0x8500;
    uint8_t  offset = 0x00;

    *cpu.get16bitRegister(RegistersEnum::PC) = iAddr;
    cpu.write(iAddr, offset);

    cpu.executeInstruction(inst_jru16);
    iAddr++;
    REQUIRE(*cpu.get16bitRegister(RegistersEnum::PC) == iAddr); //Se offset = 0 não muda o ponteiro

    offset = 0x01;
    cpu.write(iAddr, offset);
    cpu.executeInstruction(inst_jru16);
    iAddr++;
    REQUIRE(*cpu.get16bitRegister(RegistersEnum::PC) == iAddr + 1); //Se offset = 1 aumenta o PC em 1
    iAddr++; //Pra deixar igual ao PC

    offset = 0xFF;
    cpu.write(iAddr, offset);
    cpu.executeInstruction(inst_jru16);
    iAddr++;
    REQUIRE(*cpu.get16bitRegister(RegistersEnum::PC) == iAddr - 1); //Se offset = 1 diminui o PC em 1
}
