
#ifndef ESP_NTP_DS3231_H
#define ESP_NTP_DS3231_H
#include <FS.h> //this needs to be first, or it all crashes and burns...

#include <ESP8266WiFi.h> //https://github.com/esp8266/Arduino
//needed for library
#include <DNSServer.h>
// #include <ESP8266WebServer.h>
// #include <WiFiManager.h> //https://github.com/tzapu/WiFiManager
#include <ArduinoJson.h> //https://github.com/bblanchon/ArduinoJson
#include <NTPClient.h>
#include <WiFiUdp.h> 
#include <TimeLib.h>
#include "SerialCommand.h"
#include <Wire.h>
#include <RTClib.h>
#include "bouton.h"

#define DEBUGPORT Serial
#define INTERFACE DEBUGPORT //for compatibility with SerialCommand

#define WIFISELMODEPIN D7

#define SECPERHOURS (int)3600

#include "errLed.h"

#endif