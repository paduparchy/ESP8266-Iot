#ifndef NETWORK_H
#define NETWORK_H

// Appel des bibliothéques globales

//WIFI
#include <ESP8266WiFi.h>
//OTA.
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>
//NTP
#include <NTPClient.h>
#include <WiFiUdp.h>

void setup_wifi();
void setup_ota();
void maj_ota();
void setup_ntp();
int ntp_heures();
int ntp_minutes();

#endif
