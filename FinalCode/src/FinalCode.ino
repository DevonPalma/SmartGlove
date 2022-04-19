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
#include "SharedCommands.h"

// For some reason this has to be declared RIGHT after my imports IDFK
MultiplexerCollection *getBestCollection(MultiplexerCollection *comparedCol);


Multiplexer myMulp(P_MULP_ENABLE, P_MULP_S0, P_MULP_S1, P_MULP_S2, P_MULP_S3, P_MULP_SIGNAL);

MultiplexerCollection peaceSign;
MultiplexerCollection thumbsUpSign;
MultiplexerCollection rockOnSign;

int allSignsCount = 3;
MultiplexerCollection *allSigns[] = {&peaceSign, &thumbsUpSign, &rockOnSign};


void setup() {
    myMulp.begin();
}

void loop() {
    if (Serial.available() > 0) {
        Commands cmd = (Commands)Serial.read();

        switch (cmd) {
        case PROGRAM_PEACE:
            cmdProgramPeace();
            break;
        case PROGRAM_THUMB_UP:
            cmdProgramThumbsUp();
            break;
        case PROGRAM_ROCK_ON:
            cmdProgramRockOn();
            break;
        case REQUEST_BEST:
            cmdRequestBest();
            break;
        default:
            Serial.printf("ERROR: Recieved command '%d', not currently implemented.\n", cmd);
            break;
        }
    }
}

void cmdProgramPeace() {
    MultiplexerCollection mpc(&myMulp);
    peaceSign.set(&mpc);
    Serial.write(PROGRAMMED_PEACE);
}

void cmdProgramThumbsUp() {
    MultiplexerCollection mpc(&myMulp);
    thumbsUpSign.set(&mpc);
    Serial.write(PROGRAMMED_THUMB_UP);
}

void cmdProgramRockOn() {
    MultiplexerCollection mpc(&myMulp);
    rockOnSign.set(&mpc);
    Serial.write(PROGRAMMED_ROCK_ON);
}

void cmdRequestBest() {
    MultiplexerCollection mpc(&myMulp);
    MultiplexerCollection *bestCol = getBestCollection(&mpc);
    if (bestCol == &peaceSign) {
        Serial.write(BEST_PEACE);
    } else if (bestCol == &thumbsUpSign) {
        Serial.write(BEST_THUMB_UP);
    } else if (bestCol == &rockOnSign) {
        Serial.write(BEST_ROCK_ON);
    } else {
        Serial.write(BEST_UNKNOWN);
    }
}

MultiplexerCollection *getBestCollection(MultiplexerCollection *comparedCol) {
    int bestVal = 256 * 9; // Impossible to get past this with the algorithm i use
    MultiplexerCollection *bestCollection = 0;

    for (int i = 0; i < allSignsCount; i++) {
        MultiplexerCollection *curSign = allSigns[i];
        if (curSign->isSet()) {
            int curVal = curSign->compare(comparedCol);
            if (curVal < bestVal) {
                bestVal = curVal;
                bestCollection = curSign;
            }
        }
    }

    return bestCollection;
}