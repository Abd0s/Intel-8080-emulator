//
// Created by Abdos on 14/04/2023.
//

#ifndef INC_8080SIM_EMULATOR_CONTROLS_HPP
#define INC_8080SIM_EMULATOR_CONTROLS_HPP

#include <string>
#include "imgui.h"

struct EmulatorControls {

    ImVec2 window_pos;
    ImVec2 window_size;
    std::string title;

    EmulatorControls(const std::string &title, ImVec2 window_pos, ImVec2 window_size);

    void DrawWindow(ImGuiWindowFlags window_flags);

    void DrawContents();

    void EmulationTab();

    void ProgramTab();

    void AboutTab();
};

#endif //INC_8080SIM_EMULATOR_CONTROLS_HPP
