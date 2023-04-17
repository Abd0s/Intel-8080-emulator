//
// Created by Abdos on 14/04/2023.
//

#ifndef INC_8080SIM_EMULATOR_HPP
#define INC_8080SIM_EMULATOR_HPP

#include <cstdint>
#include <array>

static const int memory_size = 65536;

struct ConditionCodes {
    uint8_t s:1;
    uint8_t z:1;
    uint8_t ac:1;
    uint8_t p:1;
    uint8_t c:1;
};

struct State8080 {
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t d;
    uint8_t e;
    uint8_t h;
    uint8_t l;
    uint16_t sp;
    uint16_t pc;
    std::array<uint8_t, memory_size> memory;
    ConditionCodes condition_codes;
    uint8_t int_enable;
};

class Emulator {

public:
    State8080 state;


    Emulator();

    void LoadRom();
private:

};

#endif //INC_8080SIM_EMULATOR_HPP