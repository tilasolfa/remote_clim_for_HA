#ifndef D513452E_BD8D_485E_B531_FE9EB9CFB2F7
#define D513452E_BD8D_485E_B531_FE9EB9CFB2F7
#ifndef BLINKER_PARAMETERS_HPP
#define BLINKER_PARAMETERS_HPP

#include <Arduino.h>

class BlinkParameters {
   private:
    uint16_t m_blink_on_cycles;
    uint16_t m_on_delay_ms;
    uint16_t m_off_delay_ms;

   public:
    BlinkParameters(uint16_t blink_on_cycles, uint16_t on_delay_ms, uint16_t off_delay_ms);
    friend void blink(BlinkParameters blinkerData);
};

static BlinkParameters error(20, 30, 250);
static BlinkParameters wifi_connection_in_progress(2, 50, 50);
static BlinkParameters wifi_connection_done(10, 20, 20);
static BlinkParameters force_update_request_done(5, 500, 200);
static BlinkParameters sensor_is_online(1, 30, 50);
static BlinkParameters sensor_is_offline(20, 30, 250);
static BlinkParameters data_publication_done(5, 30, 50);

#endif /* BLINKER_PARAMETERS_HPP */


#endif /* D513452E_BD8D_485E_B531_FE9EB9CFB2F7 */
