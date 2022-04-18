/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/deedp/Documents/IOT/SmartGlove/FinalCode/src/FinalCode.ino"
/*
 * Project: A Data Glove
 * Description: Code to read a dataglove
 * Author: Devon Palma
 * Date: 4/18/2022
 */

void setup();
void loop();
#line 8 "c:/Users/deedp/Documents/IOT/SmartGlove/FinalCode/src/FinalCode.ino"
SYSTEM_MODE(SEMI_AUTOMATIC);

#include "PinData.h"
#include "Multiplexer.h"
#include "MultiplexerCollector.h"

Multiplexer myMulp(P_MULP_ENABLE, P_MULP_S0, P_MULP_S1, P_MULP_S2, P_MULP_S3, P_MULP_SIGNAL);

void setup() {
  myMulp.begin();
}

void loop() {
  if (Serial.available() > 0) {
    String dat = Serial.readString();
    // Serial.printf(dat);
    if (dat.equals("PEACE_REQUEST")) {
      Serial.printf("PEACE_COMPLETE");
    }
  }
  // MultiplexerCollection dat(&myMulp);

  // Serial.printf("%.2f     ", dat.thumb);

  // Serial.printf("%.2f  ", dat.pointer_high);
  // Serial.printf("%.2f     ", dat.pointer_low);

  // Serial.printf("%.2f  ", dat.middle_high);
  // Serial.printf("%.2f     ", dat.middle_low);

  // Serial.printf("%.2f  ", dat.ring_high);
  // Serial.printf("%.2f     ", dat.ring_low);

  // Serial.printf("%.2f  ", dat.pinky_high);
  // Serial.printf("%.2f     ", dat.pinky_low);
  // Serial.printf("\n");
}