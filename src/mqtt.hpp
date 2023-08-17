#ifndef MQTT_HPP
#define MQTT_HPP

#include <PubSubClient.h>

extern PubSubClient mqttClient;

bool reconnect();
void callback(char* topic, uint8_t* payload, unsigned int length);

#endif /* MQTT_HPP */
