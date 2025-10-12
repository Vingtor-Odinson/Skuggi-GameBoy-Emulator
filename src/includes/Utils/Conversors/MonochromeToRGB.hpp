#pragma once
#include <cstdint>

class MonochromeToRGB
{
private:
    uint32_t* convertedFrameBuffer;

public:

    MonochromeToRGB()
    {
        convertedFrameBuffer = new uint32_t[160*144];
    }

    ~MonochromeToRGB()
    {
        delete[] convertedFrameBuffer;
    }

    uint32_t* convert(const uint8_t* frameBuffer)
    {
        for (int i = 0; i < 160*144; i++)
        {
            uint8_t shade = frameBuffer[i];
            uint8_t gray = 255 - shade*85;
            convertedFrameBuffer[i] = 0xFF000000 | (gray << 16) | (gray << 8) | gray;
        }

        return convertedFrameBuffer;
    }
};
