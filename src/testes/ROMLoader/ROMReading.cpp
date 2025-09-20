#include <catch2/catch_test_macros.hpp>
#include "GameBoy.hpp"
#include "CPU/Bus.hpp"
#include "Utils/NintendoLogo.hpp"

TEST_CASE("Reading ROM with MBC", "[ROM]")
{
    std::string path = "src/testes/Resources/Carga/Zelda.gb";
    GameBoy gb = GameBoy();

    gb.setRom(path);
    gb.loadRom();

    for(int i = 0; i < 0x30; i++) {
        uint16_t addr = 0x104 + i;
        REQUIRE(NINTENDO_LOGO.at(i) == gb.read(addr));
    }

    REQUIRE(gb.read(0x147) == 0x03);
}
