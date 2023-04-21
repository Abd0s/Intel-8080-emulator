//
// Created by Abdos on 14/04/2023.
//

#include "gui_modules/debug/debug.hpp"

#include "gui_modules/debug/log.hpp"

Debug::Debug(const std::string &title,
             ImVec2 window_pos,
             ImVec2 window_size,
             Emulator* emulator) : title(title), window_pos(window_pos), window_size(window_size), emulator(emulator) {

    em_log_open = false;
    im_metrics_open = false;
    im_log_open = false;
    im_stack_tool = false;
}

void Debug::DrawWindow() {
    ImGui::SetNextWindowPos(window_pos);
    ImGui::SetNextWindowSize(window_size);
    ImGui::SetNextWindowSizeConstraints(ImVec2(0.0f, 0.0f), ImVec2(window_size.x, FLT_MAX));

    if (!ImGui::Begin(title.c_str(), nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoBackground)) {
        ImGui::End();
        return;
    }
    DrawContents();
    ImGui::End();
}

void Debug::DrawContents() {

    // Debug menu
    if (ImGui::BeginMenu("D")) {
        // GUI Debug menu
        if (ImGui::BeginMenu("GUI debug")) {
            if (ImGui::MenuItem("Metrics")) {
                im_metrics_open = true;
            }
            if (ImGui::MenuItem("Log")) {
                im_log_open = true;
            }
            if (ImGui::MenuItem("Stack tool")) {
                im_stack_tool = true;
            }
            ImGui::EndMenu();
        }
        // Emulator Debug menu
        if (ImGui::BeginMenu("Emulator debug")) {
            if (ImGui::MenuItem("Log")) {
                em_log_open = true;
            }
            if (ImGui::MenuItem("ClearState")) {
                emulator->ResetState();
            }
            ImGui::EndMenu();
        }

        ImGui::EndMenu();
    }

    // Open popups depending on state
     if (em_log_open) {
         Log::Instance()->DrawWindow(&em_log_open);
     }
     if (im_metrics_open) {
         ImGui::ShowMetricsWindow(&im_metrics_open);
     }
     if (im_log_open) {
         ImGui::ShowDebugLogWindow(&im_log_open);
     }
     if (im_stack_tool) {
         ImGui::ShowStackToolWindow(&im_stack_tool);
     }

}

