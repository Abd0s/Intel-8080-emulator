//
// Created by Abdos on 14/04/2023.
//

#ifndef INC_8080SIM_DEBUG_HPP
#define INC_8080SIM_DEBUG_HPP

#include "emulator/emulator.hpp"

#include <string>
#include "imgui.h"


struct Debug {

    ImVec2 window_pos;
    ImVec2 window_size;
    std::string title;

    // Window states
    bool em_log_open;
    bool im_metrics_open;
    bool im_log_open;
    bool im_stack_tool;

    Emulator* emulator;

    Debug(const std::string &title, ImVec2 window_pos, ImVec2 window_size, Emulator* emulator);

    void DrawWindow();
    void DrawContents();
};

#endif //INC_8080SIM_DEBUG_HPP
