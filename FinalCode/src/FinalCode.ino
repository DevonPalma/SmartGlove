/*
 * Project: A Data Glove
 * Description: Code to read a dataglove
 * Author: Devon Palma
 * Date: 4/18/2022
 */

SYSTEM_MODE(SEMI_AUTOMATIC);

#include "Multiplexer.h"
#include "MultiplexerCollector.h"
#include "PinData.h"

Multiplexer myMulp(P_MULP_ENABLE, P_MULP_S0, P_MULP_S1, P_MULP_S2, P_MULP_S3, P_MULP_SIGNAL);

MultiplexerCollection peaceSign;
bool peaceSignSet = false;

MultiplexerCollection thumbsUpSign;
bool thumbsUpSignSet = false;

MultiplexerCollection* getBestCollection(MultiplexerCollection* currentCol);

void setup() {
    myMulp.begin();
}

void loop() {
    MultiplexerCollection mpc(&myMulp);


    
    if (Serial.available() > 0) {
        String serialData = Serial.readString();
        if (serialData.equals("REQ_PEACE")) {
            peaceSign.set(&mpc);
            peaceSignSet = true;
            Serial.printf("PROG_PEACE");
        } else if (serialData.equals("REQ_THUMB_UP")) {
            thumbsUpSign.set(&mpc);
            thumbsUpSignSet = true;
            Serial.printf("PROG_THUMB_UP");
        } else if (serialData.equals("REQ_BEST")) {
            MultiplexerCollection* bestCollection = getBestCollection(&mpc);
            if (bestCollection == &peaceSign) {
              Serial.printf("BEST_PEACE");
            } else if (bestCollection == &thumbsUpSign) {
              Serial.printf("BEST_THUMB_UP");
            } else {
              Serial.printf("BEST_UNKNOWN");
            }
        }
    }
}

MultiplexerCollection* getBestCollection(MultiplexerCollection* currentCol) {
    int bestVal = 256*9; // Impossible to get past this with the algorithm i use
    MultiplexerCollection *bestCollection;

    if (peaceSignSet) {
        int thisVal = peaceSign.compare(currentCol);
        if (thisVal < bestVal) {
          bestVal = thisVal;
          bestCollection = &peaceSign;
        }
    }

    if (thumbsUpSignSet) {
        int thisVal = thumbsUpSign.compare(currentCol);
        if (thisVal < bestVal) {
          bestVal = thisVal;
          bestCollection = &thumbsUpSign;
        }
    }

    return bestCollection;
}