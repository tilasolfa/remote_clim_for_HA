#include <Arduino.h>
#include <ArduinoOTA.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ir_Toshiba.h>

//
#include "ac.hpp"
#include "constants.hpp"
// espPlayground

IRToshibaAC ac(IR_LED_PIN);

void setup() {
    Serial.begin(115200);
    delay(200);

    ac.begin();
}

void loop() {
    ac_configure_fresh_default();
    ac_send();
    delay(5000);
}
