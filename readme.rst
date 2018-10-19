===================================================
Informations générales sur le projet ESP_NTP_DS3231
===================================================

:Auteur:             Major LEE
:Projet:             ESP_NTP_DS3231
:Version:            20181005
:Projet:             A venir sur le `wiki du VoLAB <http://www.vorobotics.com/wiki/index.php?title=Nos_Projets>`_
:Licence:            CC0
:Liens:              https://creativecommons.org/licenses/by-nc-sa/4.0/

####

Description
===========

This project aim to set time on DS3231 breakout boards from an NTP server by the way of a WEMOS D1 mini.

To use it you need to creat a config.json file in the data directory of the ARDUINO sketch and up load it in the SPIFFS of the ESP8266.
See https://www.instructables.com/id/Using-ESP8266-SPIFFS/

config.json content:
::

    {
        "wifi_login" : "your_ssid",
        "wifi_pass" : "your_wifi_password",
    }


In this release this is serial commands:

<N> to display NTP time

<D> to display DS3231 time

<2> to diaplay both times

<S> to set DS3231 time with NTP time

<V> to display compile time

<e> to introduice a 15s delta time between 2 clocks

<d> to display epoc delta time between 2 clocks

<T> for LED test

<O> to turn RGB LEDs off

<o> to turn RGB LEDs on

We also add LED and button features to operate without a PC only need a 5V usb power supply.

Shortly : printable case 3D design...

