#ifndef BLINK_HPP
#define BLINK_HPP

#include "BlinkParameters.hpp"

const void blink(const uint16_t BLINK_ON_CYCLES, const uint16_t ON_DELAY_MS, const uint16_t OFF_DELAY_MS);
void blink(BlinkParameters blinkerData);

#endif /* BLINK_HPP */
