//
// Created by Abdos on 14/04/2023.
//

#ifndef INC_8080SIM_DEBUG_HPP
#define INC_8080SIM_DEBUG_HPP

#include <string>
#include "imgui.h"

struct Debug {

    ImVec2 window_pos;
    ImVec2 window_size;
    std::string title;

    Debug(const std::string &title, ImVec2 window_pos, ImVec2 window_size);

    void DrawWindow(ImGuiWindowFlags window_flags);
    void DrawContents();
};

#endif //INC_8080SIM_DEBUG_HPP
