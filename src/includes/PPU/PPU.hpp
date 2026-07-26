#ifndef SKUGGI_PPU_HPP
#define SKUGGI_PPU_HPP
#include <array>
#include <cstdint>

#include "OAM_Object.hpp"
#include "enum/PPUState.hpp"

class Bus;

class PPU
{
private:
    Bus* bus;
    PPUState ppuState;
    std::array<OAMObject, 10> oamObjects = {};
    uint8_t oamIndex = 0;
    uint8_t actualLineObjectsNum = 0;
    uint8_t currentLine = 0;
    uint8_t actualLineTile = 0;
    uint16_t currentLineCycCounter = 0;
    uint8_t* data;
    uint8_t temporaryByteHolder;
    bool readingByte0 = true;

    const uint16_t oamOffset = 0xFE00;

    bool shouldDrawObject(const uint8_t& yPos) const;
    void changeMode(const PPUState& state);

    void oamScanline(const uint8_t& cyc);
    void drawPixels(const uint8_t& cyc);
    uint8_t readLinePixels(const uint8_t& tileID, bool mode);
    void blank(const uint8_t& cyc, const PPUState& state);

    uint8_t getSCY();
    uint8_t getSCX();
    uint8_t getLCDC();
    uint8_t readTileID(const uint8_t& tileIndex);

public:
    PPU(Bus* bus);
    ~PPU();
    void step(const uint8_t& cyc);
    bool isFrameReady() const {return true;}
    uint8_t* getFrameBuffer() const;
};

#endif //SKUGGI_PPU_HPP
