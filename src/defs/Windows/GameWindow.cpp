#include <imgui.h>
#include "Windows/SkuggiWindows.hpp"
#include "CPU/CPU.hpp"
#include "PPU/PPU.hpp"
#include "Utils/Properties.hpp"
#include "Utils/Conversors/MonochromeToRGB.hpp"

namespace SkuggiWindows
{
    void RenderGameWindow(PPU* ppu, GLuint textureId)
    {
        ImGui::Begin("GameBoy");

        if (ppu->isFrameReady())
        {
            const uint8_t* pixels = ppu->getFrameBuffer();
            MonochromeToRGB converter = MonochromeToRGB();
            uint32_t* frameBuffer = converter.convert(pixels);
            glBindTexture(GL_TEXTURE_2D, textureId);
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0,0, GAMEBOY_SCREEN_WIDHT, GAMEBOY_SCREEN_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, frameBuffer);
        }

        ImGui::Image((void*)(intptr_t)textureId, ImVec2(160 * 3, 144 * 3));
        ImGui::End();
    }
}
