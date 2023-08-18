#ifndef DEVICES_HPP
#define DEVICES_HPP

#include "configuration.hpp"

#ifdef KITCHEN_AC
const char DEVIDE_IP[] = "192.168.1.64";
const char DEVIDE_DNS_NAME[] = "espKitchenAC";
const char DEVICE_ID[] = "kitchenAC_ESP8266";
const char HA_request_configure_AC_fresh_default[] = "homeassistant/kitchen_ac/HA_request_configure_AC_fresh_default";
const char HA_request_AC_off[] = "homeassistant/kitchen_ac/HA_request_AC_off";
#endif

#ifdef PLAYGROUND
const char DEVIDE_IP[] = "192.168.1.62";
const char DEVIDE_DNS_NAME[] = "espPlayground";
const char DEVICE_ID[] = "playgroundESP8266";
const char HA_request_configure_AC_fresh_default[] = "homeassistant/playground/HA_request_configure_AC_fresh_default";
const char HA_request_AC_off[] = "homeassistant/playground/HA_request_AC_off";
#endif

#endif /* DEVICES_HPP */
