#include <Arduino.h>
#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>

//
#include <PubSubClient.h>

//
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ir_Toshiba.h>

//
#include "ac.hpp"
#include "blink.hpp"
#include "constants.hpp"
#include "devices.hpp"
#include "mqtt.hpp"
// espPlayground

WiFiClient espClient;
PubSubClient mqttClient(espClient);
IRToshibaAC ac(IR_LED_PIN);

void setup_wifi() {
    delay(10);

    Serial.println();
    Serial.print("Connecting Wi-Fi...");
    Serial.println(WIFI_SSID);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        blink(2, 50, 50);
    }

    Serial.println("");
    Serial.println("Connected:");
    Serial.println(WiFi.localIP());
    blink(10, 20, 20);
}

void setup() {
    Serial.begin(115200);
    delay(200);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    setup_wifi();
    ArduinoOTA.begin();

    mqttClient.setServer(MQTT_SERVER, MQTT_SERVER_PORT);
    mqttClient.setCallback(callback);

    ac.begin();
}

void loop() {
    if (!mqttClient.connected()) {
        if (reconnect()) {
            mqttClient.subscribe(HA_request_configure_AC_fresh_default);
            mqttClient.subscribe(HA_request_AC_off);
        }
    }
    mqttClient.loop();

    ArduinoOTA.handle();
}
