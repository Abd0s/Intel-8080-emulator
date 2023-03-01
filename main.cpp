#include "main.h"

#include <iostream>
#include <fstream>

#include "fmt/core.h"
#include "fmt/color.h"


int main(int argc, char* argv[]) {
    // allocate 64kB of memory
    uint8_t memory [65536] = {};
    state.memory = memory;

    // load rom into memory
    LoadRom(argv[1], &state);

    //EmulateInstruction(&state);
    return 0;
}

void UnimplementedInstruction(State8080* state) {
    fmt::print("Error: Unimplemented instruction {:#x} at {:#x}\n", state->memory[state->pc], state->pc);
    exit(1);
}

void EmulateInstruction(State8080* state) {
    unsigned char* opcode = &state->memory[state->pc];

    switch(*opcode) {
        // Unimplemented
        default: UnimplementedInstruction(state);
    }
    state->pc+=1;
}

void LoadRom(char* file_path, State8080* state) {
    fmt::print("Log: Loading file: {}\n", file_path);
    state->pc = 0;

    std::streampos size;
    char* buffer;

    std::ifstream file(file_path, std::ios::in|std::ios::binary|std::ios::ate);

    if (file.is_open()) {
        size = file.tellg();
        buffer = new char[size];
        file.seekg(0, std::ios::beg);
        file.read(buffer, size);
        file.close();

        memcpy(state->memory, buffer, size);
        fmt::print("Log: Loaded file contents ({} bytes)\n", size);
        delete[] buffer;
    }
    else fmt::print("Error: Unable to open file\n");
}