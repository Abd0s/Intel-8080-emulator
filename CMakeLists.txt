cmake_minimum_required(VERSION 3.16.3)
project(8080sim)

set(CMAKE_CXX_STANDARD 17)

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
        src/main.cpp
        src/emulator/emulator.cpp
        src/emulator/instruction_implementations.cpp
        src/gui_modules/cpu_controls.cpp
        src/gui_modules/instruction_execution_trace.cpp
        src/gui_modules/emulator_controls.cpp
        src/gui_modules/debug/debug.cpp

    # External
        external/ImGuiFileDialog/ImGuiFileDialog.cpp
        )


add_executable(${PROJECT_NAME} ${SOURCES})
add_executable(${PROJECT_NAME}-diss disassembler.cpp)

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/external
        )

# External libraries
find_package(fmt)
target_link_libraries(8080sim fmt::fmt)

find_package(ImGui-SFML REQUIRED)
target_link_libraries(8080sim ImGui-SFML::ImGui-SFML)

find_package(SFML
        COMPONENTS
        system window graphics audio REQUIRED)
target_link_libraries(8080sim sfml-system sfml-graphics sfml-window)


