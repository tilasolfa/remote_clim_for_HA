#include "mqtt.hpp"

#include <ir_Toshiba.h>

#include "ac.hpp"
#include "blink.hpp"
#include "constants.hpp"
#include "devices.hpp"

extern IRToshibaAC ac;

bool reconnect() {
    Serial.print("Connecting MQTT...");

    if (mqttClient.connect(DEVICE_ID, MQTT_USER, MQTT_PASSWORD)) {
        Serial.println("connected");
        return true;
    } else {
        Serial.print("failed, rc=");
        Serial.println(mqttClient.state());
        delay(1000);
        return false;
    }
}

void callback(char* topic, uint8_t* payload, unsigned int length) {
    Serial.print("callback : Message arrived [");
    Serial.print(topic);
    Serial.println("] ");
    if (memcmp(HA_request_configure_AC_fresh_default, topic, sizeof(HA_request_configure_AC_fresh_default)) == 0) {
        ac_configure_fresh_default();
        ac_send();
        blink(10, 10, 30);

    } else if (memcmp(HA_request_AC_off, topic, sizeof(HA_request_AC_off)) == 0) {
        ac.off();
        blink(10, 10, 30);
    }
    Serial.println();
}