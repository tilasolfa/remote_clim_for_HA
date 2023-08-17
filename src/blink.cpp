#include "blink.hpp"

const void blink(const uint16_t BLINK_ON_CYCLES, const uint16_t ON_DELAY_MS, const uint16_t OFF_DELAY_MS) {
    for (int i = 0; i < BLINK_ON_CYCLES; i++) {
        digitalWrite(LED_BUILTIN, LOW);  // allumé
        delay(ON_DELAY_MS);
        digitalWrite(LED_BUILTIN, HIGH);  // éteint
        delay(OFF_DELAY_MS);
    }
}

void blink(const BlinkParameters blinkerData) {
    blink(blinkerData.m_blink_on_cycles, blinkerData.m_on_delay_ms, blinkerData.m_off_delay_ms);
}
