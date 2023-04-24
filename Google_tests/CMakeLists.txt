# 'Google_test' is the subproject name
project(Google_tests)

# 'googletest-main' is the folder with Google Test sources
add_subdirectory(googletest-main)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Create a sources variable with a link to all cpp files to compile
get_filename_component(PARENT_DIR ../ ABSOLUTE)
set(SOURCES
        ${PARENT_DIR}/src/emulator/emulator.cpp
        ${PARENT_DIR}/src/gui_modules/debug/log.cpp)

add_executable(Google_Tests_run
        EmulatorInstructionTest.cpp
        ${SOURCES})

target_include_directories(Google_Tests_run
        PRIVATE
        ${PARENT_DIR}/include
        )

# External libraries
find_package(fmt)
target_link_libraries(Google_Tests_run fmt::fmt)

find_package(ImGui-SFML REQUIRED)
target_link_libraries(Google_Tests_run ImGui-SFML::ImGui-SFML)

find_package(SFML
        COMPONENTS
        system window graphics audio REQUIRED)
target_link_libraries(Google_Tests_run sfml-system sfml-graphics sfml-window)

target_link_libraries(Google_Tests_run gtest gtest_main)