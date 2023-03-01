cmake_minimum_required(VERSION 3.23)
project(8080sim)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(8080sim main.cpp)
add_executable(8080dis disassembler.cpp)


add_subdirectory(external/fmt)
target_link_libraries(8080sim fmt::fmt)
