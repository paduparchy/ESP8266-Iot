#include <Arduino.h>
#include "capteurs.h"
#include "config.h"

//Nécessaire pour I2C
#include <Wire.h>

// CAPTEUR BMP180 - Capteur d'intensité pression atmosphérique et température
// On intégre les librairies necessaires au Capteur BMP180
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085.h>
/* BMP180 Barometric Pressure & Temp Sensor
   These displays use I2C to communicate, 2 pins are required to  
   interface
   Connections
   ===========
   Connect VCC of the BMP085 sensor to 3.3V (NOT 5.0V!)
   Connect GND to Ground
   Connect SCL to i2c clock - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 5 => correspond au port D1 sur carte ESP8266
   Connect SDA to i2c data - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 4 => correspond au port D2 sur carte ESP8266
   EOC is not used, it signifies an end of conversion
   XCLR is a reset pin, also not used here
*/
// Variables techniques et initialisation 
Adafruit_BMP085 bmp;


// CAPTEUR BH1750 - Capteur d'intensité lumineuse 
// On intégre les librairies necessaires au Capteur BH1750

#include <BH1750.h>
// Initialisation du BH1750
BH1750 lightMeter;

// CAPTEUR DHT11 - capteur de température et humidité
// On intégre les librairies necessaires au Capteur DHT11
#include <DHT.h>
// Variables techniques :
#define DHTPIN D6                                     // PIN digital de connexion DATA du DHT11 (sur lequel il est branché sur la carte)
#define DHTTYPE DHT11                                 // Définition du type de DHT utilisé DHT11, DHT22, ....
// Initialisation du DHT
DHT dht(DHTPIN, DHTTYPE);


// Fonction pour capteur BH1750

void init_bh1750(){
  
  // Initialize the I2C bus (BH1750 library doesn't do this automatically)
  // On esp8266 devices you can select SCL and SDA pins using Wire.begin(D4, D3);
  // Connecter SCL sur D1 et SDA sur D2 sur esp8266
  
  Serial.println("BH1750 initialisation...");
  Wire.begin();
  lightMeter.begin();
}

void getData_bh1750() {

  float lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
}

// Fonction pour capteur DHT11

void init_dht() {
  Serial.println("DHT11 initialisation...");
  dht.begin();                                // Initialisation du capteur DHT  
}

void getData_dht() {

  Serial.println("DHT11 relevé des compteurs...");
  // Relevé et envoi du DHT11 ou DHT22 (Température et humidité)
  float hum = dht.readHumidity();                         // Lecture du taux d'humidité
  float temp = dht.readTemperature();                     // Lecture de la température en Celcius
  float fahr = dht.readTemperature(true);                 // Lecture de la température en Fahrenheit
  float ressenti = dht.computeHeatIndex(fahr, hum);       // Calcul la température ressentie. le calcul s'effectue à partir de la température en Fahrenheit
  
  /*
  Calcul la température ressentie. le calcul s'effectue à partir de la température en Fahrenheit
  float ressenti = dht.computeHeatIndex(fahr, hum);
  float ti = convertFtoC(dht.computeHeatIndex(convertCtoF(temp), hum));
    // Commande bibliothéque 
  convertCtoF(float) : converti la température Celcius en Fahrenheit
  convertFtoC(float) : converti la température Fahrenheit en Celcius
  */

   // On établi le degré de confort d'humidité
   int hum_status = 0;
   if ((hum >= 45) and (hum <= 65))      { hum_status = 2; } // confortable
   else if ((hum >= 35) and (hum < 45))  { hum_status = 1; } // Normal
   else if (hum < 35)                    { hum_status = 0; } // sec
   else if (hum > 65)                    { hum_status = 3; } // humide
 
   // Stop le programme et renvoie un message d'erreur si le capteur ne renvoie aucune mesure
   if (isnan(hum) || isnan(temp) || isnan(fahr)) {
    Serial.println("Echec de lecture !");
    return;
    }

    // on imprime le résultat sur le port serie 
    Serial.print("Humidite: "); 
    Serial.print(hum);
    Serial.print("%\t");
    Serial.print("Temperature: "); 
    Serial.print(temp);
    Serial.print("°C\t");
    Serial.print("Temperature: "); 
    Serial.print(fahr);
    Serial.print("°F\t");
    Serial.print("Temperature ressentie: ");
    Serial.print(dht.convertFtoC(ressenti)); // on converti le resultat obtenu plus haut de fahrenheit a degré
    Serial.println("°C");
    Serial.print("Comfort d'humitité (0:Sec, 1:Normal, 2:Confortable, 3:Humide) : ");
    Serial.println(hum_status);
    
}



// Fonction pour capteur BMP180

void init_bmp180() {
  Serial.println("Pressure Sensor initialisation...");
  /* Initialise the sensor */
  if(!bmp.begin())
  {
    /* There was a problem detecting the BMP180 ... check your connections */
    Serial.print("Ooops, no BMP180 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
 
}

void getData_bmp180() {

    Serial.print("Temperature = ");
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");
    
    Serial.print("Pressure = ");
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");
    
    // Calculate altitude assuming 'standard' barometric
    // pressure of 1013.25 millibar = 101325 Pascal
    Serial.print("Altitude = ");
    Serial.print(bmp.readAltitude());
    Serial.println(" meters");

    Serial.print("Pressure at sealevel (calculated) = ");
    Serial.print(bmp.readSealevelPressure());
    Serial.println(" Pa");

  // you can get a more precise measurement of altitude
  // if you know the current sea level pressure which will
  // vary with weather and such. If it is 1015 millibars
  // that is equal to 101500 Pascals.
  // le 21/12/2021 la valeur etait de 102500 ... aller sycnhoniser l'info sur le site avant de lancer la sonde https://openweathermap.org/city/2998102
    Serial.print("Real altitude = ");
    Serial.print(bmp.readAltitude(102500));
    Serial.println(" meters");
    
    Serial.println();  
}
