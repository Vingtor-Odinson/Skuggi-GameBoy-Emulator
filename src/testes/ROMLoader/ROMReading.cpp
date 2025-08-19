#include <catch2/catch_test_macros.hpp>
#include "CPU/CPU.hpp"
#include "CPU/Bus.hpp"
#include "Utils/NintendoLogo.hpp"

TEST_CASE("Reading ROM with MBC", "[ROM]")
{
    std::string path = "src/testes/Resources/Carga/Zelda.gb";
    CPU cpu = CPU();

    cpu.setROM(path);
    cpu.loadROM();

    for(int i = 0; i < 0x30; i++) {
        uint16_t addr = 0x104 + i;
        REQUIRE(NINTENDO_LOGO.at(i) == cpu.read(addr));
    }

    REQUIRE(cpu.read(0x147) == 0x03);
}
