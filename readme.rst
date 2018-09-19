===================================================
Informations générales sur le projet ESP_NTP_DS3231
===================================================

:Auteur:             Major LEE
:Projet:             ESP_NTP_DS3231
:Version:            20180919
:Licence:            CC0
:Liens:              https://creativecommons.org/licenses/by-nc-sa/4.0/

####

Description
===========

This project aim to set time on DS3231 breakout boards from an NTP server by the way of a WEMOS D1 mini.

To use it you need to creat a config.json file in the data directory of the ARDUINO sketch and up load it in the SPIFFS of the ESP8266.
See https://www.instructables.com/id/Using-ESP8266-SPIFFS/

config.json content:
{
    "wifi_login" : "your_ssid",
    "wifi_pass" : "your_wifi_password",
}

####
