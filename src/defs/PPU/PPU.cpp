#include "CPU/Bus.hpp"
#include "PPU/PPU.hpp"

bool PPU::shouldDrawObject(const uint8_t& yPos) const
{
    return true;
}

PPU::PPU(Bus* bus)
{
    this->bus = bus;
    data = new uint8_t[160*144];
}

PPU::~PPU()
{
    delete[] data;
}

void PPU::step(const uint8_t& cyc)
{
    currentLineCycCounter += cyc;

    switch (ppuState)
    {
    case PPUState::OAM_Scan:
        {
            oamScanline(cyc);
        }
    case PPUState::DrawingPixels:
        {
            drawPixels(cyc);
        }
    case PPUState::VBlank:
    case PPUState::HBlank:
        {
            blank(cyc, ppuState);
        }
    }
}

void PPU::changeMode(const PPUState& state)
{
    ppuState = state;
    //to-do
    //Depois precisa adicionar as devidas travas aos pedaços de memória
}

void PPU::oamScanline(const uint8_t& cyc)
{
    uint8_t objects = cyc / 4; //This supposing the T-cycles per instruction is always a multiple of 4

    uint8_t objIndex = oamIndex;
    oamIndex = oamIndex + objects;

    bool shallChangeMode = false;
    uint8_t restingCycles = 0;

    if (oamIndex >= 40)
    {
        restingCycles = oamIndex - 40;
        shallChangeMode = true;
        oamIndex = 40;
    }

    for (; objIndex < oamIndex; objIndex++)
    {
        if (shouldDrawObject(bus->read(DeviceEnum::Memory, oamOffset + objIndex)))
        {
            oamObjects[actualLineObjectsNum].yPosition = bus->read(DeviceEnum::Memory, oamOffset + objIndex);
            oamObjects[actualLineObjectsNum].xPosition = bus->read(DeviceEnum::Memory, oamOffset + objIndex + 1);
            oamObjects[actualLineObjectsNum].tileIndex = bus->read(DeviceEnum::Memory, oamOffset + objIndex + 2);
            oamObjects[actualLineObjectsNum].attributes = bus->read(DeviceEnum::Memory, oamOffset + objIndex + 3);
            actualLineObjectsNum++;
        }
    }

    if (shallChangeMode)
    {
        changeMode(PPUState::DrawingPixels);
        drawPixels(restingCycles);
    }
}

void PPU::drawPixels(const uint8_t& cyc)
{ //I'll suppose each 4 cycles corresponds to 1 pixel =>

    uint8_t iterations = cyc/4;
    for (int i = 0; i < iterations; i++)
    {
        const uint8_t tileIndex = currentLine * 20  + actualLineTile;
        const uint8_t tileID = readTileID(tileIndex);

        if (readingByte0)
        {
            temporaryByteHolder = readLinePixels(tileID, readingByte0);
        }
        else
        {
            uint8_t byte1 = readLinePixels(tileID, readingByte0);
            for (int i = 0; i < 8; i++)
            {
                uint8_t byte0 = (temporaryByteHolder & (0x01 << (7-i))) >> (7-i);
                byte1 = (byte1 & (0x01 << (7-i))) >> (7-i);
                data[i] = (byte1 < 1) + byte0;
            }
            actualLineTile++;
        }

        readingByte0 = !readingByte0;
    }
}

void PPU::blank(const uint8_t& yPos, const PPUState& state)
{
    if (state == PPUState::VBlank)
    {
        currentLine = 0;
    }
    actualLineTile = 0;
    oamIndex = 0;
    actualLineObjectsNum = 0;
    currentLineCycCounter = 0;
}

uint8_t PPU::getSCY()
{
    return bus->read(DeviceEnum::Memory, 0xFF42);
}

uint8_t PPU::getSCX()
{
    return bus->read(DeviceEnum::Memory, 0xFF43);
}

uint8_t PPU::getLCDC()
{
    return bus->read(DeviceEnum::Memory, 0xFF40);
}

uint8_t PPU::readTileID(const uint8_t& tileIndex)
{ //This is not taking scrolling into account

    bool isLCDC3on = (getLCDC() & 0x08) >> 3;
    uint16_t tileMapBaseAddr = isLCDC3on ? 0x9800 : 0x9C00;
    return bus->read(DeviceEnum::Memory, tileMapBaseAddr + tileIndex);
}

uint8_t PPU::readLinePixels(const uint8_t& tileID, bool mode)
{
    bool isLCDC4on = (getLCDC() & 0x10) >> 4;
    uint16_t tileDataBaseAddr;
    const uint8_t offset = tileID * 0x10 + currentLine * 2 + !mode;
    if (isLCDC4on)
    {
        tileDataBaseAddr = 0x8000;
        return bus->read(DeviceEnum::Memory, tileDataBaseAddr + offset);
    }
    tileDataBaseAddr = 0x9000;
    return bus->read(DeviceEnum::Memory, tileDataBaseAddr + static_cast<int8_t>(offset));
}

uint8_t* PPU::getFrameBuffer() const
{
    for (int i = 0; i < 160*144; i++)
    {
        if (i % 2 == 0)
        {
            data[i] = 0x01;
        }
        else
        {
            data[i] = 0x02;
        }
    }

    return data;
}