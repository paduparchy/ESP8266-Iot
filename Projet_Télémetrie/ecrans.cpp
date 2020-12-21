#include <Arduino.h>
#include "ecrans.h"
#include "config.h"

//Nécessaire pour I2C
#include <Wire.h>

// EcranSSD1306 - Ecran 128 * 64
// On intégre les librairies necessaires a l'ecran 
#include "SSD1306Wire.h"

// Variables techniques et initialisation de l écran
SSD1306Wire  display(0x3c, D3, D4);

// The y variable will be used to animate the lines
uint8_t y = 0;
// The direction changes, when y reaches either 0 or 64
sint8_t direction = 1;

void init_ssd1306() {
  // Initialize the driver
  display.init();
  // Set the drawing color once
  display.setColor(WHITE);
  // display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);

}

void print_ssd1306() {

  display.clear();
  display.setFont(ArialMT_Plain_10);

  // The coordinates define the left starting point of the text
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 10, "humidité");

  // The coordinates define the center of the text
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 22, "température");

  // The coordinates define the right end of the text
  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.drawString(128, 33, "pression :");
  display.display();

/*
 https://github.com/ThingPulse/esp8266-oled-ssd1306/
*/ 
  
/*  
  // Change the y value
  y = y + direction; 
  if (y == 64) {
    // decrease y
    direction = -1;
  } else if (y == 0) {
    // increase y
    direction = 1;
  }
  // Clear the frame buffer
  display.clear();
  
  // Draw the lines by using the current y value
  display.drawLine(0, y, 128, 64 - y);
  display.drawLine(0, 64 - y, 128, y);

  // Write the frame buffer to the display.
  display.display();
*/
}
