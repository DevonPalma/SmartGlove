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
int getBestCollection(MultiplexerCollection *comparedCol);
void programFingerPosition(FingerPosition fingerPos);

Multiplexer myMulp(P_MULP_ENABLE, P_MULP_S0, P_MULP_S1, P_MULP_S2, P_MULP_S3, P_MULP_SIGNAL);

MultiplexerCollection allSigns[HAND_POS_COUNT];

void setup() {
    myMulp.begin();
    for (int i = 0; i < HAND_POS_COUNT; i++) {
      allSigns[i].loadFromEEPROM(i);
    }
}

void loop() {
    if (Serial.available() > 0) {
        byte cmd, data;
        readCommand(&cmd, &data);
        switch (cmd) {
        case PROGRAM:
            programFingerPosition(data);
            break;
        case REQUEST:
            handleRequest(data);
            break;
        default:
            sendCommand(STATUS, UNIMPLEMENTED_COMMAND);
            break;
        }
    }
}

void programFingerPosition(byte fingerPos) {
    if (fingerPos < HAND_POS_COUNT) {
        MultiplexerCollection mpc(&myMulp);
        allSigns[fingerPos].set(&mpc);
        allSigns[fingerPos].saveToEEPROM(fingerPos);
        sendCommand(STATUS, PROGRAM_SUCCESSFUL);
    }
}

void handleRequest(byte request) {
    if (request == BEST) {
        MultiplexerCollection mpc(&myMulp);
        int bestCol = getBestCollection(&mpc);
        if (bestCol == -1) {
            sendCommand(STATUS, REQUEST_FAILED);
        } else {
            sendCommand(BEST_FINGER, bestCol);
        }
    }
}

int getBestCollection(MultiplexerCollection *comparedCol) {
    int bestVal = 256 * 9; // Impossible to get past this with the algorithm i use
    int bestColIndex = -1;

    for (int i = 0; i < HAND_POS_COUNT; i++) {
        MultiplexerCollection *curSign = &allSigns[i];
        if (curSign->isSet()) {
            int curVal = curSign->compare(comparedCol);
            if (curVal < bestVal) {
                bestVal = curVal;
                bestColIndex = i;
            }
        }
    }

    return bestColIndex;
}