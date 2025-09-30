#include <imgui.h>
#include "Windows/SkuggiWindows.hpp"
#include "CPU/CPU.hpp"

namespace SkuggiWindows
{
    void RenderRegistersWindow(CPU* cpu)
    {
        ImGui::Begin("Registers");
        ImGui::Text("Registers:");
        ImGui::Separator();
        ImGui::Text("AF: 0x%04X", cpu->get16bitRegisterValue(RegistersEnum::AF));
        ImGui::SameLine();
        ImGui::Text("BC: 0x%04X", cpu->get16bitRegisterValue(RegistersEnum::BC));
        ImGui::Text("DE: 0x%04X", cpu->get16bitRegisterValue(RegistersEnum::DE));
        ImGui::SameLine();
        ImGui::Text("HL: 0x%04X", cpu->get16bitRegisterValue(RegistersEnum::HL));
        ImGui::Separator();
        ImGui::Text("PC: 0x%04X", cpu->get16bitRegisterValue(RegistersEnum::PC));
        ImGui::SameLine();
        ImGui::Text("SP: 0x%04X", cpu->get16bitRegisterValue(RegistersEnum::SP));

        ImGui::End();
    }
}