//
// Created by Abdos on 14/04/2023.
//

#include "gui_modules/emulator_controls.hpp"

#include "ImGuiFileDialog/ImGuiFileDialog.h"

EmulatorControls::EmulatorControls(const std::string &title, ImVec2 window_pos, ImVec2 window_size) : title(title), window_pos(window_pos), window_size(window_size) {

}

void EmulatorControls::DrawWindow(ImGuiWindowFlags window_flags = 0) {
    ImGui::SetNextWindowPos(window_pos);
    ImGui::SetNextWindowSize(window_size);
    ImGui::SetNextWindowSizeConstraints(ImVec2(0.0f, 0.0f), ImVec2(window_size.x, FLT_MAX));

    if (ImGui::Begin(title.c_str(), NULL, window_flags))
    {
        DrawContents();
    }
    ImGui::End();
}

void EmulatorControls::DrawContents() {

    static int active_tab = 0;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    if (ImGui::Button("Emulation", ImVec2(window_size.x/3, 25)))
    {
        active_tab = 0;
    }
    ImGui::SameLine(0.0f, 0.0f);
    if (ImGui::Button("Program", ImVec2(window_size.x/3, 25)))
    {
        active_tab = 1;
    }
    ImGui::SameLine(0.0f, 0.0f);
    if (ImGui::Button("About", ImVec2(window_size.x/3, 25)))
    {
        active_tab = 2;
    }
    ImGui::PopStyleVar();
    switch(active_tab) {
        case 0: EmulationTab(); break;
        case 1: ProgramTab(); break;
        case 2: AboutTab(); break;
    }
}

void EmulatorControls::EmulationTab() {
    ImGui::SeparatorText("Loadds");
    ImGui::Text("LALALALALALALAL");
}

void EmulatorControls::ProgramTab() {
    if (ImGui::Button("Load program", ImVec2(150, 25))) {
        ImGuiFileDialog::Instance()->OpenDialog("Choose ROM file", "Choose File", ".cpp,.h,.hpp", ".");
        std::cout
    }

        // display
        if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) {
            // action if OK
            if (ImGuiFileDialog::Instance()->IsOk()) {
                std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
                // action
            }

            // close
            ImGuiFileDialog::Instance()->Close();
        }
}

void EmulatorControls::AboutTab() {

}