#ifndef SKUGGI_CPUMOCK_HPP
#define SKUGGI_CPUMOCK_HPP

class Bus;

class CPU;

class Memory;

class ROMLoader;

class CPUMock {

private:
    Bus* bus;
    CPU* cpu;
    Memory* memory;
    ROMLoader* romLoader;

public:
    CPUMock();
    ~CPUMock();
    CPU* getMockedCPU();
};

#endif //SKUGGI_CPUMOCK_HPP
