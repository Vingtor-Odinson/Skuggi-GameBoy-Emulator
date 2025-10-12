#pragma once
#include <SDL3/SDL_opengl.h>

class CPU;
class PPU;

namespace SkuggiWindows
{
    void RenderRegistersWindow(CPU* cpu);
    void RenderGameWindow(PPU* ppu, GLuint textureId);
}