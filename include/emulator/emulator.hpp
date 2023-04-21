//
// Created by Abdos on 14/04/2023.
//

#ifndef INC_8080SIM_EMULATOR_HPP
#define INC_8080SIM_EMULATOR_HPP

#include <cstdint>
#include <array>
#include <string>
#include <bitset>

struct ConditionCodes {
    uint8_t s;
    uint8_t z;
    uint8_t ac;
    uint8_t p;
    uint8_t c;
};

struct State8080 {
    uint8_t a;
    std::bitset<8> f;
    uint8_t b;
    uint8_t c;
    uint8_t d;
    uint8_t e;
    uint8_t h;
    uint8_t l;
    uint16_t sp;
    uint16_t pc;
    std::array<uint8_t, 65536> memory;
    uint8_t int_enable;
};

class Emulator {

public:
    State8080 state;

    bool running;
    unsigned int target_clock_speed;
    unsigned int actual_clock_speed;

    Emulator();

    void LoadRom(const std::string &file_path_name);

    void SetClockSpeed(int clock_speed);

    int GetActualClockSpeed();

    void ClearMemory();

    void ResetState();

    int StepInstruction();

private:
    void SetFlags(uint16_t rs);
    // CPU ISA IMPLEMENTATION
    void MOV(uint8_t &rd, uint8_t rs);
    void MVI(uint8_t &rd, uint8_t rs);
    void ADD(uint8_t rs);

};

#endif //INC_8080SIM_EMULATOR_HPP