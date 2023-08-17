#include "ac.hpp"

void ac_configure_fresh_default() {
    ac.on();
    ac.setFan(kToshibaAcFanMax);
    ac.setSwing(kToshibaAcSwingOn);
    ac.setMode(kToshibaAcCool);
    ac.setTemp(23);
}

void ac_send() {
#if SEND_TOSHIBA_AC
    ac.send();
#endif
}