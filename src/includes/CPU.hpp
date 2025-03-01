#pragma once

class Memory;

class ROMLoader;

class CPU
{
    public:
        ROMLoader* romLoader;
        Memory* memory;

        CPU();
        ~CPU();
};