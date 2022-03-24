/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/deedp/Documents/IOT/SmartGlove/DaCode/src/DaCode.ino"
/*
 * Project DaCode
 * Description:
 * Author:
 * Date:
 */

void setup();
void loop();
#line 8 "c:/Users/deedp/Documents/IOT/SmartGlove/DaCode/src/DaCode.ino"
SYSTEM_MODE(SEMI_AUTOMATIC);

#include <Adafruit_SSD1306.h>

const int POINTER_FINGER = A0;
const int MIDDLE_FINGER = A1;

Adafruit_SSD1306 display(D4);


void setup() {
    display.begin(SSD1306_SWITCHCAPVCC, 0x3D); // initialize with the I2C addr 0x3D (for the 128x64)
    display.setTextColor(WHITE);
    display.display();

    pinMode(POINTER_FINGER, INPUT_PULLDOWN);
    pinMode(MIDDLE_FINGER, INPUT_PULLDOWN);
}

void loop() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.printf("F1: %d\n", (int) analogRead(POINTER_FINGER));
  display.printf("F2: %d\n", (int) analogRead(MIDDLE_FINGER));
  display.display();
}