#include "arduino.h"

const uint8_t maxAcceleration PROGMEM = 10;

uint8_t map_accel(uint8_t x, uint8_t rng)
{
    return map(x, 0, maxAcceleration, 0, rng);
}
