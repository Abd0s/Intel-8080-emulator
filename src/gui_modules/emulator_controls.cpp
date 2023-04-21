//
// Created by Abdos on 14/04/2023.
//

#include "gui_modules/emulator_controls.hpp"

#include "ImGuiFileDialog/ImGuiFileDialog.h"

#include "fmt/core.h"
#include <iostream>

EmulatorControls::EmulatorControls(const std::string &title,
                                   ImVec2 window_pos,
                                   ImVec2 window_size,
                                   Emulator* emulator) :
                                   title(title),
                                   window_pos(window_pos),
                                   window_size(window_size),
                                   emulator(emulator) {
}

void EmulatorControls::DrawWindow(ImGuiWindowFlags window_flags = 0) {
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

void EmulatorControls::DrawContents() {

    ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
    if (ImGui::BeginTabBar("settings_tab", tab_bar_flags))
    {
        if (ImGui::BeginTabItem("Emulation"))
        {
            EmulationTab();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Program"))
        {
            ProgramTab();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("About"))
        {
            AboutTab();
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
}

void EmulatorControls::EmulationTab() {
    ImGui::SeparatorText("Loadds");
    ImGui::Text("LALALALALALALAL");
}

void EmulatorControls::ProgramTab() {
    // open file dialog
    if (ImGui::Button("Open File Dialog"))
        ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".*",
                                                ".", 1, nullptr, ImGuiFileDialogFlags_Modal);

    // display
    if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey"))
    {
        // action if OK
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
            std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
            // action

            emulator->LoadRom(filePathName);

        }

        // close
        ImGuiFileDialog::Instance()->Close();
    }
    // open file dialog
    if (ImGui::Button("Clear mem")) {
        emulator->ClearMemory();
    }

}

void EmulatorControls::AboutTab() {

}