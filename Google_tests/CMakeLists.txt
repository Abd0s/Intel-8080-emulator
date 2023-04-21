# 'Google_test' is the subproject name
project(Google_tests)

# 'googletest-main' is the folder with Google Test sources
add_subdirectory(googletest-main)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'Google_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests
add_executable(Google_Tests_run
        EmulatorInstructionTest.cpp
        )

# Create a sources variable with a link to all cpp files to compile
set(SOURCES src/emulator/emulator.cpp)

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/external
        )

target_link_libraries(Google_Tests_run gtest gtest_main)