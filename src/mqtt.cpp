#include "mqtt.hpp"

#include <ir_Toshiba.h>

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

void ac_send() {
#if SEND_TOSHIBA_AC
    ac.send();
#endif
}

void callback(char* topic, uint8_t* payload, unsigned int length) {
    Serial.print("callback : Message arrived [");
    Serial.print(topic);
    Serial.println("] ");
    size_t payload_size = sizeof(payload);                                 // TODO : pourquoi si on met sizeof(payload) au lieu de le calculer en amont, on a un warning ?
    if (memcmp(HA_request_AC_on, topic, sizeof(HA_request_AC_on)) == 0) {  // ON
        Serial.println("HA request AC on");
        ac.on();
        ac_send();
    } else if (memcmp(HA_request_AC_off, topic, sizeof(HA_request_AC_off)) == 0) {  // OFF
        Serial.println("HA request AC off");
        ac.off();
        ac_send();
    } else if (memcmp(HA_request_temperature_value, topic, sizeof(HA_request_temperature_value)) == 0) {  // temperature
        char payloadStr[payload_size];
        for (size_t i = 0; i < payload_size; ++i) {
            payloadStr[i] = static_cast<char>(payload[i]);
        }
        payloadStr[payload_size - 1] = '\0';

        int target_temperature = atoi(payloadStr);

        if (target_temperature <= 30 && target_temperature >= 17) {
            Serial.print("Temperature request : ");
            Serial.println(target_temperature);
            ac.setTemp(target_temperature);
            ac_send();
        }

    } else if (memcmp(HA_request_a_c_mode, topic, sizeof(HA_request_a_c_mode)) == 0) {  // mode
        if (memcmp("Auto", payload, payload_size) == 0) {
            Serial.println("A/C mode request : auto");
            ac.setMode(kToshibaAcAuto);
            ac_send();
        } else if (memcmp("Cool", payload, payload_size) == 0) {
            Serial.println("A/C mode request : cool");
            ac.setMode(kToshibaAcCool);
            ac_send();
        } else if (memcmp("Dry", payload, payload_size) == 0) {  // TODO : ce mode ne fonctionne pas : sizeof("Dry") ?
            Serial.println("A/C mode request : dry");
            ac.setMode(kToshibaAcDry);
            ac_send();
        } else if (memcmp("Heat", payload, payload_size) == 0) {
            Serial.println("A/C mode request : heat");
            ac.setMode(kToshibaAcHeat);
            ac_send();
        } else if (memcmp("Fan", payload, payload_size) == 0) {  // TODO : ce mode ne fonctionne pas : sizeof("Fan") ?
            Serial.println("A/C mode request : fan");
            ac.setMode(kToshibaAcFan);
            ac_send();
        }
    } else if (memcmp(HA_request_a_c_fan_speed, topic, sizeof(HA_request_a_c_fan_speed)) == 0) {  // fan speed
        if (memcmp("Auto", payload, payload_size) == 0) {
            Serial.println("Fan speed request : auto");
            ac.setFan(kToshibaAcFanAuto);
            ac_send();
        } else {
            char payloadStr[payload_size];
            for (size_t i = 0; i < payload_size; ++i) {
                payloadStr[i] = static_cast<char>(payload[i]);
            }
            payloadStr[payload_size - 1] = '\0';

            int fan_speed = atoi(payloadStr);

            if (fan_speed <= 5 && fan_speed >= 0) {
                Serial.print("Fan speed request : ");
                Serial.println(fan_speed);
                ac.setFan(fan_speed);
                ac_send();
            }
        }
    } else if (memcmp(HA_request_a_c_fan_swing, topic, sizeof(HA_request_a_c_fan_swing)) == 0) {  // swing
        if (memcmp("On", payload, 3) == 0) {                                                      // TODO : pourquoi est-on obligés de mettre 3 et pas sizeof(payload) ?
            Serial.println("Fan swing request : on");
            ac.setSwing(kToshibaAcSwingOn);
            ac_send();
        } else if (memcmp("Off", payload, payload_size) == 0) {
            Serial.println("Fan swing request : off");
            ac.setSwing(kToshibaAcSwingOff);
            ac_send();
        }
    }
}