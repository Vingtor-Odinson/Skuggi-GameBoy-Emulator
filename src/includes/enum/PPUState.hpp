#pragma once
#include <cstdint>

enum class PPUState
{
    OAM_Scan,
    DrawingPixels,
    HBlank,
    VBlank
};
