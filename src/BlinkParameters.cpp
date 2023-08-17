#include "BlinkParameters.hpp"

BlinkParameters::BlinkParameters(uint16_t blink_on_cycles, uint16_t on_delay_ms, uint16_t off_delay_ms) {
    m_blink_on_cycles = blink_on_cycles;
    m_on_delay_ms = on_delay_ms;
    m_off_delay_ms = off_delay_ms;
}
