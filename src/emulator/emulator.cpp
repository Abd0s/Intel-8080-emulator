//
// Created by Abdos on 14/04/2023.
//

#include "emulator/emulator.hpp"
#include "gui_modules/debug/log.hpp"

#include <fstream>

#include "fmt/core.h"

#define pr(a, b) 256U*state.a+state.b



Emulator::Emulator() {
    ClearMemory();
    SetClockSpeed(2'000'000);
    state.f[1] = 1;
    state.f[5] = 0;
}

int Emulator::StepInstruction() {
    // DECODE AND EXECUTE INSTRUCTION
    int cycle_amount;
    switch (state.memory[state.pc]) {
        case 0x00: cycle_amount = 4; break; // NOP
        case 0x01: cycle_amount = 4; break; // NOP
        case 0x02: cycle_amount = 4; break; // NOP
        case 0x03: cycle_amount = 4; break; // NOP
        case 0x04: cycle_amount = 5; break; // MOV B, B // OPT: ignore as does nothing
        case 0x05: cycle_amount = 5; MOV(state.d, state.b); break; // MOV D, B
        case 0x06: cycle_amount = 5; MOV(state.h, state.b); break; // MOV H, B
        case 0x07: cycle_amount = 7; MOV(state.memory[pr(h, l)], state.b); break; // MOV M, B
        case 0x08: cycle_amount = 4; ADD(state.b); break; // ADD B
    }
    state.pc++;
    return cycle_amount;
}

// FIXME: Fix that files bigger than memory crash
void Emulator::LoadRom(const std::string &file_path_name) {
        Log::Instance()->Gen(fmt::format("Loading file at {}", file_path_name));

        std::streampos size;
        char* buffer;

        std::ifstream file(file_path_name, std::ios::in|std::ios::binary|std::ios::ate);

        if (file.is_open()) {
            size = file.tellg();
            buffer = new char[size];
            file.seekg(0, std::ios::beg);
            file.read(buffer, size);
            file.close();

            memcpy(state.memory.data(), buffer, size);
            Log::Instance()->Succ(fmt::format("Loaded file contents ({} bytes)", int(size)));
            delete[] buffer;
        }
        else Log::Instance()->Err(fmt::format("Unable to open file"));
}

void Emulator::ClearMemory() {
    Log::Instance()->Gen(fmt::format("Clearing memory..."));
    state.memory.fill(0x00);
    Log::Instance()->Succ(fmt::format("Cleared memory"));

}

// TODO: Reload rom after reset
void Emulator::ResetState() {
    Log::Instance()->Gen(fmt::format("Reseting cpu state..."));
    state = State8080();
    // Set const flags
    state.f[1] = 1;
    state.f[5] = 0;

    Log::Instance()->Succ(fmt::format("Reset cpu state"));

    // Reload rom
    //Log::Instance()->Succ(fmt::format("Reloaded ROM"));
}

void Emulator::SetClockSpeed(int clock_speed) {
    this->target_clock_speed = clock_speed;
}

int Emulator::GetActualClockSpeed() {
    return running ? actual_clock_speed : 0;
}

// TODO: IMPLEMENT AUX CARRY, POTENTIALLY OPTIMIZATION: CALC FLAGS ON DEMAND
void Emulator::SetFlags(uint16_t rs) {
    state.f[6] = ((rs & 0xff) == 0); // z
    state.f[7] = ((rs & 0x80) != 0); // s
    state.f[0] = (rs > 0xff); // c
    rs ^= rs >> 4;
    rs &= 0xf;
    state.f[2]  = (0x6996 >> rs) & 1; // p
}

// CPU ISA IMPLEMENTATION

void Emulator::MOV(uint8_t &rd, uint8_t rs) {
    rd = rs;
}

void Emulator::MVI(uint8_t &rd, uint8_t i) {
    rd = i;
}

void Emulator::ADD(uint8_t rs) {
    uint16_t a_im = (uint16_t) state.a + (uint16_t) rs;
    SetFlags(a_im);
    state.a = a_im & 0xff;
}