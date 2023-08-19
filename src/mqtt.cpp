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

void msg_from_payload(char* zone, uint8_t* payload, unsigned int payload_size) {
    memcpy(zone, payload, payload_size);
    zone[payload_size] = '\0';
}

void callback(char* topic, uint8_t* payload, unsigned int payload_size) {
    Serial.print("callback : Message arrived [");
    Serial.print(topic);
    Serial.println("] ");

    char msg[120];
    msg_from_payload(msg, payload, payload_size);

    if (strcmp(HA_request_AC_on, topic) == 0) {  // ON
        Serial.println("HA request AC on");
        ac.on();
        ac_send();
    } else if (strcmp(HA_request_AC_off, topic) == 0) {  // OFF
        Serial.println("HA request AC off");
        ac.off();
        ac_send();
    } else if (strcmp(HA_request_temperature_value, topic) == 0) {  // temperature
        int target_temperature = atoi(msg);
        if (target_temperature <= 30 && target_temperature >= 17) {
            Serial.print("Temperature request : ");
            Serial.println(target_temperature);
            ac.setTemp(target_temperature);
            ac_send();
        }

    } else if (strcmp(HA_request_a_c_mode, topic) == 0) {  // mode
        if (strcmp("Auto", msg) == 0) {
            Serial.println("A/C mode request : auto");
            ac.setMode(kToshibaAcAuto);
            ac_send();
        } else if (strcmp("Cool", msg) == 0) {
            Serial.println("A/C mode request : cool");
            ac.setMode(kToshibaAcCool);
            ac_send();
        } else if (strcmp("Dry", msg) == 0) {
            Serial.println("A/C mode request : dry");
            ac.setMode(kToshibaAcDry);
            ac_send();
        } else if (strcmp("Heat", msg) == 0) {
            Serial.println("A/C mode request : heat");
            ac.setMode(kToshibaAcHeat);
            ac_send();
        } else if (strcmp("Fan", msg) == 0) {
            Serial.println("A/C mode request : fan");
            ac.setMode(kToshibaAcFan);
            ac_send();
        }
    } else if (strcmp(HA_request_a_c_fan_speed, topic) == 0) {  // fan speed
        if (strcmp("Auto", msg) == 0) {
            Serial.println("Fan speed request : auto");
            ac.setFan(kToshibaAcFanAuto);
            ac_send();
        } else {
            int fan_speed = atoi(msg);

            if (fan_speed <= 5 && fan_speed >= 0) {
                Serial.print("Fan speed request : ");
                Serial.println(fan_speed);
                ac.setFan(fan_speed);
                ac_send();
            }
        }
    } else if (strcmp(HA_request_a_c_fan_swing, topic) == 0) {  // swing
        if (strcmp("On", msg) == 0) {
            Serial.println("Fan swing request : on");
            ac.setSwing(kToshibaAcSwingOn);
            ac_send();
        } else if (strcmp("Off", msg) == 0) {
            Serial.println("Fan swing request : off");
            ac.setSwing(kToshibaAcSwingOff);
            ac_send();
        }
    }
}
