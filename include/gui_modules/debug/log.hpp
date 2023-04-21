//
// Created by Abdos on 17/04/2023.
//

#ifndef INC_8080SIM_LOG_HPP
#define INC_8080SIM_LOG_HPP

#include "imgui.h"
#include <string>


struct Log
{
    ImGuiTextBuffer buffer;
    ImGuiTextFilter filter;
    ImVector<int>   line_offsets; // Index to lines offset. We maintain this with AddLog() calls.
    bool            auto_scroll;  // Keep scrolling if already at the bottom.

    Log();

    static Log* Instance();
    void Clear();

    // TODO: swap to std::string
    void AddLog(const char* fmt, ...) IM_FMTARGS(2);

    void Err(const std::string &msg);

    void Succ(const std::string &msg);

    void Warn(const std::string &msg);

    void Gen(const std::string &msg);

    void DrawWindow(bool* p_open = nullptr);

    void DrawContents();
};

#endif //INC_8080SIM_LOG_HPP
