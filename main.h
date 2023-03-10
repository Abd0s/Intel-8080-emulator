//
// Created by Abdos on 12/09/2022.
//

#ifndef INC_8080SIM_MAIN_H
#define INC_8080SIM_MAIN_H

#include <cstdint>

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
    uint8_t* memory;
    ConditionCodes condition_codes;
    uint8_t int_enable;
};

void UnimplementedInstruction(State8080* state);
void LoadRom(char* file_path, State8080* state);
void EmulateInstruction(State8080* state);

State8080 state;
#endif //INC_8080SIM_MAIN_H
