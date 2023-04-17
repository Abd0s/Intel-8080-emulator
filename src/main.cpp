#include "main.hpp"
#include "config.hpp"
#include "emulator/emulator.hpp"
#include "gui_modules/instruction_execution_trace.hpp"
#include "gui_modules/emulator_controls.hpp"
#include "gui_modules/cpu_controls.hpp"
#include "gui_modules/debug/debug.hpp"

#include "fmt/core.h"
#include "fmt/color.h"

#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "../include/gui_modules/memory_editor.h"

#include <iostream>
#include <fstream>
#include <memory>


int main(int argc, char* argv[]) {

    // Application settings
    static const std::string title = "Intel 8080 emulator";
    static const std::array<int, 2> window_size = {1200, 800};


    // Initialize emulator
    static Emulator emulator;

    // Initialize graphics
    sf::RenderWindow window(sf::VideoMode(window_size[0], window_size[1]), title, sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    if (!ImGui::SFML::Init(window)) {
        fmt::print("Failed to init ImGui\n");
        return 1;
    }


    // Create GUI window modules
    static MemoryEditor ram_viewer("RAM Viewer", ImVec2(0, window_size[1]), ImVec2(0, 0)); // Auto sets width based on #cols
    static InstructionExecutionTrace instruction_execution_trace("ROM Viewer", ImVec2(323, 0), ImVec2(177, window_size[1]));
    static CpuControls cpu_controls("CPU Controls", ImVec2(500, 500),ImVec2(400, 300));
    static EmulatorControls emulator_controls("Settings", ImVec2(900, 500), ImVec2(300, 300));

    static const ImGuiWindowFlags default_window_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;

    // video buffer output reserved space: 650x450 (25px padding) center @ 850, 250
    // Draw placeholder video buffer output
    sf::RectangleShape video_buffer_placeholder(sf::Vector2f(650, 450));
    video_buffer_placeholder.setFillColor(sf::Color(20, 20, 20));
    // set a 10-pixel wide orange outline
    video_buffer_placeholder.setOutlineThickness(1.f);
    video_buffer_placeholder.setOutlineColor(sf::Color(105, 105, 105));
    video_buffer_placeholder.setOrigin(sf::Vector2f(video_buffer_placeholder.getSize().x/2, video_buffer_placeholder.getSize().y/2));
    video_buffer_placeholder.setPosition(sf::Vector2f(850, 250));

    // Main update loop
    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        // Event handling
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Imgui update call
        ImGui::SFML::Update(window, deltaClock.restart());

        // ImGui Tools/Apps (accessible from the "DEV" menu)
        static bool show_app_metrics = true;
        static bool show_app_debug_log = true;
        static bool show_app_stack_tool = true;

        if (show_app_metrics)
            ImGui::ShowMetricsWindow(&show_app_metrics);
        if (show_app_debug_log)
            ImGui::ShowDebugLogWindow(&show_app_debug_log);
        if (show_app_stack_tool)
            ImGui::ShowStackToolWindow(&show_app_stack_tool);

        // Call GUI modules draw functions
        ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImGui::GetStyleColorVec4(ImGuiCol_TitleBg));

        ram_viewer.DrawWindow(emulator.state.memory.data(), memory_size, default_window_flags);
        instruction_execution_trace.DrawWindow(default_window_flags);
        cpu_controls.DrawWindow(default_window_flags);
        emulator_controls.DrawWindow(default_window_flags);

        ImGui::PopStyleColor();


        // Clear frame and redraw
        window.clear();
        // SFML draw calls
        window.draw(video_buffer_placeholder);

        // Imgui draw call
        ImGui::SFML::Render(window);

        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}



void EmulateInstruction(State8080* state) {
    unsigned char* opcode = &state->memory[state->pc];

    switch(*opcode) {
        // Unimplemented
    }
    state->pc+=1;
}

