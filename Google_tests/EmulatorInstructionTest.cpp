//
// Created by Abdos on 21/04/2023.
//

#include "gtest/gtest.h"

#include "emulator/emulator.hpp"

class EmulatorTest : public ::testing::Test {
    protected:
        void SetUp() override {
        }

    Emulator emulator;
};

TEST_F(EmulatorTest, NOP) {
    State8080 p_state = emulator.state;
    emulator.state.memory[0] = 0x00; // INSTRUCTION TO TEST

    emulator.StepInstruction();

    //EXPECT_EQ(emulator.state, p_state);
    FAIL();
}

TEST_F(EmulatorTest, MOV) {
    emulator.state.memory[0] = 0x05; // INSTRUCTION TO TEST

    emulator.state.b = 0x02;
    emulator.state.d = 0x00;

    emulator.StepInstruction();

    EXPECT_EQ(emulator.state.d, emulator.state.b);
    // TEST THAT NOTHING ELSE CHANGED
}
