#pragma once

class Memory;

class ROMLoader;

class Registers;

class CPU
{
    public:
        ROMLoader* romLoader;
        Memory* memory;
        Registers* regs;

        CPU();
        ~CPU();

};