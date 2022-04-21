#ifndef _SEQUENCE_RUNNER_H_
#define _SEQUENCE_RUNNER_H_

#include "SharedCommands.h"

bool tableMatches(int sequenceLength, FingerPosition *tableA, FingerPosition *tableB) {
        for (int i = 0; i < sequenceLength; i++) {
            if (tableA[i] != tableB[i]) {
                return false;
            }
        }

        return true;
}

void tablePush(int sequenceLength, FingerPosition *table, FingerPosition newIndex) {
        for (int i = sequenceLength - 1; i > 0; i--) {
            table[i] = table[i - 1];
        }
        table[0] = newIndex;
}

void tablePrint(int sequenceLength, FingerPosition *table) {
    for (int i = 0; i < sequenceLength; i++) {
        Serial.printf("%d  ", table[i]);
    }
    Serial.printf("\n");
}

#endif