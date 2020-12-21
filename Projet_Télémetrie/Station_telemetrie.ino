/*
 Station météo à base d'un ESP8266, et des composants suivant : 

 - SSD1306 Ecran OLED
 - BM180 Barometer Plage de pression: 300 ~ 1100hPa.
 - DHT11 Temperature and Humidity sensor
 - BH1750FVI : Digital Light Sensor - Capteur d'intensité lumineuse numérique Sortie numérique directe, calcul complexe omis, sans étalonnage
 
 Bibliothéques nécessaires, et version utilisées :
  - ESP8266Wifi v1.0.0
  - ArduinoOTA v1.0.0
  - Adafruit unified sensor v 1.1.2
  - Adafruit BME280 v2.0.2
  - DHT sensor library by Adafruit v1.4.0
  - NTPClient by Fabrice Weinberg v3.2.0
 
 Installer le gestionnaire de carte ESP8266 version 2.7.1 
 Si besoin : URL à ajouter pour le Bord manager : http://arduino.esp8266.com/stable/package_esp8266com_index.json

Code inspiré de Dominique PAUL. Dépot Github : https://github.com/DomoticDIY/

*/

// Appel des librairies locales

#include "config.h"
#include "network.h"
#include "capteurs.h"
#include "ecrans.h"

//Necessaires à l'I2C.
#include <Wire.h>

void setup() {
  // put your setup code here, to run once:
  delay(2000);
  Serial.begin(115200);                           // On initialise la vitesse de transmission de la console.
  Serial.println("Initialisation du programme...");
  setup_wifi();                                   // Connexion au Wifi
  setup_ota();                                    // Initialisation de l'OTA
  setup_ntp();                                    // Connexion au NTP
  init_ssd1306();                                 // Initialisation de l'ecran SSD1306
  print_ssd1306();                                // Ecriture sur l'ecran
  init_dht();                                     // Initialisation du capteur DHT (humidité, température)
  getData_dht();                                  // Lecture des valeurs du capteur DHT (humidité, température) 
  init_bh1750();                                  // Initialisation du capteur BH1750 (lumiere)
  getData_bh1750();                               // Lecture des valeurs du capteur BH1750 (lumiere 
  init_bmp180();                                  // initiaisation capteur de pression BMP180
  getData_bmp180();                               // Lecture des valeurs BMP180

  //init_connect_mqtt();                          // On défini la connexion MQTT
  //init_capteurs();                              // Initialisation des Capteurs de relevés


}

void loop() {
  // put your main code here, to run repeatedly:


}
