#pragma once

#include <cstdint>

struct Bus{
    uint8_t data;
};

static const uint8_t NEGATIVE = 0b1000; //0 = Positive
static const uint8_t OVERFLOW = 0b0100; //0 = No Overflow
static const uint8_t ZERO     = 0b0010; //0 = Non-zero
static const uint8_t UNUSED   = 0b0001; // Unused for now

    

