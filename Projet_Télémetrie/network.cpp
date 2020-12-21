#include <Arduino.h>
#include "network.h"
#include "config.h"

//Config NTP
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);

// CONFIGURATION WIFI

void setup_wifi() {
  // Connexion au réseau Wifi
  delay(10);
  Serial.println();
  Serial.print("Connection au réseau : ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);            // Passage de la puce en mode client
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    // Tant que l'on est pas connecté, on boucle.
    delay(500);
    Serial.print(".");
  }
  // Initialise la séquence Random
  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connecté");
  Serial.print("Addresse IP : ");
  Serial.println(WiFi.localIP());
}


// INITIALISATION Arduino OTA

void setup_ota() {
  /* Port par defaut = 8266 */
  // ArduinoOTA.setPort(8266);

  /* Hostname, par defaut = esp8266-[ChipID] */
  ArduinoOTA.setHostname(nomModule);

  /* Pas d'authentication par defaut */
  // ArduinoOTA.setPassword("admin");

  /* Le mot de passe peut également être défini avec sa valeur md5 ici c'est 'admin' en md5*/
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");
  
  // code à exécuter au démarrage de la mise à jour
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH)
      type = "sketch";
    else // U_SPIFFS
      type = "filesystem";

    // NOTE: si vous mettez à jour SPIFFS, démonter SPIFFS à l'aide de SPIFFS.end ()
    Serial.println("Début de update " + type);
  });
  
  // code à exécuter à la fin de la mise à jour
  ArduinoOTA.onEnd([]() {
    Serial.println("\nFin");
  });
  
  // code à exécuter pendant la mise à jour
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progression : %u%%\r", (progress / (total / 100)));
  });
  
  // code à exécuter en cas d'erreur de la mise à jour
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Erreur[%u] : ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Authentification Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Exécution Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connexion Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Réception Failed");
    else if (error == OTA_END_ERROR) Serial.println("Fin Failed");
  });

  ArduinoOTA.begin();
  Serial.println("Prêt");
  Serial.print("Adresse IP : ");
  Serial.println(WiFi.localIP());
}

void maj_ota() {
   ArduinoOTA.handle();                            // On verifie si une mise a jour OTA nous est envoyée. Si OUI, la lib ArduinoOTA se charge de faire la MAJ.
}

// CONFIGURATION NTP

void setup_ntp(){
  // Begin du NTP
  timeClient.begin();
  Serial.println("NTP initialisation...");
  Serial.print("Heure Ntp : ");
  Serial.println(timeClient.getFormattedTime());
  Serial.print("jour Ntp : ");
  Serial.println(timeClient.getDay());
}

/*
int ntp_heures() {
  // Retour int de l'heure NTP
  timeClient.update();
  return timeClient.getHours();
}

int ntp_minutes(){
  // Retour int des minutes NTP
  timeClient.update();
  return timeClient.getMinutes();
}
*/
