//
// Created by Abdos on 14/04/2023.
//

#include "gui_modules/cpu_controls.hpp"

CpuControls::CpuControls(const std::string &title, ImVec2 window_pos, ImVec2 window_size) : title(title), window_pos(window_pos), window_size(window_size) {

}

void CpuControls::DrawWindow(ImGuiWindowFlags window_flags = 0) {
    ImGui::SetNextWindowPos(window_pos);
    ImGui::SetNextWindowSize(window_size);
    ImGui::SetNextWindowSizeConstraints(ImVec2(0.0f, 0.0f), ImVec2(window_size.x, FLT_MAX));

    if (ImGui::Begin(title.c_str(), NULL, window_flags))
    {
        DrawContents();
    }
    ImGui::End();
}

void CpuControls::DrawContents() {

}