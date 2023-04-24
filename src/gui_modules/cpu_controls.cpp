//
// Created by Abdos on 14/04/2023.
//

#include "gui_modules/cpu_controls.hpp"

#include "gui_modules/debug/log.hpp"


CpuControls::CpuControls(const std::string &title,
                         ImVec2 window_pos,
                         ImVec2 window_size,
                         Emulator* emulator) : title(title), window_pos(window_pos), window_size(window_size), emulator(emulator) {

}

void CpuControls::DrawWindow(ImGuiWindowFlags window_flags = 0) {
    ImGui::SetNextWindowPos(window_pos);
    ImGui::SetNextWindowSize(window_size);
    ImGui::SetNextWindowSizeConstraints(ImVec2(0.0f, 0.0f), ImVec2(window_size.x, FLT_MAX));

    if (!ImGui::Begin(title.c_str(), NULL, window_flags))
    {
        ImGui::End();
        return;
    }
    DrawContents();
    ImGui::End();
}

void CpuControls::DrawContents() {
    // Controls
    ImGui::BeginGroup();
    if (!emulator->running) {
        if (ImGui::Button("Run")) {
            emulator->running = true;
        }
    }
    else {
        if (ImGui::Button("Stop")) {
            emulator->running = false;
        }
    }

    // Make sure we cant step while the emulator is running
    ImGui::BeginDisabled(emulator->running);
    ImGui::SameLine();
    if (ImGui::Button("Step")) {
        emulator->StepInstruction();
    }

    ImGui::SameLine();
    if (ImGui::Button("Reset")) {
        emulator->ResetState();
    }

    ImGui::EndDisabled();
    ImGui::Text("State: %d", emulator->running);
    ImGui::EndGroup();

    ImGui::SameLine();
    ImGui::BeginGroup();
    ImGui::Indent();
    ImGui::Text("Target Clock Speed: %d Hz", emulator->target_clock_speed);
    ImGui::Text("Actual Clock Speed: %d Hz", emulator->GetActualClockSpeed());
    ImGui::Unindent();
    ImGui::EndGroup();

    // Registers
    ImGui::SeparatorText("Registers");
    int reg_input_flags;
    std::string reg_format;

    ImGui::BeginDisabled(emulator->running);
    // 8 bit registers
    if (ImGui::BeginTable("register_table", 3)) {
        // 1st row HEADER
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        // 1st col
        ImGui::Indent(35.0f);
        ImGui::Text("15 ... 8");
        ImGui::Unindent(35.0f);
        ImGui::TableNextColumn();
        // 2nd col
        ImGui::Indent(40.0f);
        ImGui::Text("7 ... 0");
        ImGui::Unindent(40.0f);
        // 3rd col
        ImGui::TableNextColumn();
        static int radix_select = 0;
        ImGui::Combo("##radix", &radix_select, "HEX\0DEC\0\0");

        switch (radix_select) {
            case 0: {
                reg_input_flags = reg_input_flags | ImGuiInputTextFlags_CharsHexadecimal; reg_format = "%02X"; break;
            }
            case 1: {
                reg_input_flags = reg_input_flags | ImGuiInputTextFlags_CharsDecimal; reg_format = "%u"; break;
            }
            // TODO: Implement binary mode
            case 2: {
                reg_input_flags = reg_input_flags | ImGuiInputTextFlags_CharsDecimal; reg_format = "%u"; break;
            }

        }

        // 2nd row AF
        ImGui::TableNextRow();
        // 1st col
        ImGui::TableNextColumn();
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "A |");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(65.0f);
        ImGui::InputScalar("##A", ImGuiDataType_U8, &emulator->state.a, nullptr, nullptr, reg_format.c_str(), reg_input_flags);
        // 2nd col
        ImGui::TableNextColumn();
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "F |");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(65.0f);
        ImGui::InputScalar("##F", ImGuiDataType_U8, &emulator->state.f, nullptr, nullptr, reg_format.c_str(), reg_input_flags);
        // 3nd col
        ImGui::TableNextColumn();
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "<- PSW");

        // 3rd row BC
        ImGui::TableNextRow();
        // 1st col
        ImGui::TableNextColumn();
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "B |");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(65.0f);
        ImGui::InputScalar("##B", ImGuiDataType_U8, &emulator->state.b, nullptr, nullptr, reg_format.c_str(), reg_input_flags);
        // 2nd col
        ImGui::TableNextColumn();
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "C |");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(65.0f);
        ImGui::InputScalar("##C", ImGuiDataType_U8, &emulator->state.c, nullptr, nullptr, reg_format.c_str(), reg_input_flags);
        // 3nd col
        ImGui::TableNextColumn();
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "<- B");

        // 4th row DE
        ImGui::TableNextRow();
        // 1st col
        ImGui::TableNextColumn();
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "D |");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(65.0f);
        ImGui::InputScalar("##D", ImGuiDataType_U8, &emulator->state.d, nullptr, nullptr, reg_format.c_str(), reg_input_flags);
        // 2nd col
        ImGui::TableNextColumn();
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "E |");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(65.0f);
        ImGui::InputScalar("##E", ImGuiDataType_U8, &emulator->state.e, nullptr, nullptr, reg_format.c_str(), reg_input_flags);
        // 3nd col
        ImGui::TableNextColumn();
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "<- D");

        // 4th row DE
        ImGui::TableNextRow();
        // 1st col
        ImGui::TableNextColumn();
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "H |");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(65.0f);
        ImGui::InputScalar("##H", ImGuiDataType_U8, &emulator->state.h, nullptr, nullptr, reg_format.c_str(), reg_input_flags);
        // 2nd col
        ImGui::TableNextColumn();
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "L |");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(65.0f);
        ImGui::InputScalar("##L", ImGuiDataType_U8, &emulator->state.l, nullptr, nullptr, reg_format.c_str(), reg_input_flags);
        // 3nd col
        ImGui::TableNextColumn();
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "<- H");


        ImGui::EndTable();
    }

    // 16 bit registers
    ImGui::Indent(75.0f);
    ImGui::Text("15 ... 0");
    ImGui::Unindent(75.0f);
    // 2nd row SP
    ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "SP |");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(130.0f);
    ImGui::InputScalar("##SP", ImGuiDataType_U16, &emulator->state.sp, nullptr, nullptr, reg_format.c_str(), reg_input_flags);
    // 3rd row PC
    ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "PC |");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(130.0f);
    ImGui::InputScalar("##PC", ImGuiDataType_U16, &emulator->state.pc, nullptr, nullptr, reg_format.c_str(), reg_input_flags);

    ImGui::EndDisabled();
}