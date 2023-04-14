#include "../include/main.h"
#include "../include/emulator/emulator.h"

#include "fmt/core.h"
#include "fmt/color.h"

#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "../include/gui_modules/memory_editor.h"

#include <iostream>
#include <fstream>
#include <memory>


int main(int argc, char* argv[]) {

    // Application details
    static const std::string title = "Intel 8080 emulator";


    // Initialize emulator
    static Emulator emulator;

    // Initialize graphics
    sf::RenderWindow window(sf::VideoMode(1200, 800), title, sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    if (!ImGui::SFML::Init(window)) {
        fmt::print("Failed to init ImGui\n");
        return 1;
    }


    static MemoryEditor ram_viewer;
    static const ImGuiWindowFlags default_window_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;


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



        ram_viewer.DrawWindow("RAM Viewer", emulator.state.memory.data(), memory_size, ImVec2(0, 0), default_window_flags);

        // Clear frame and redraw
        window.clear();
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

