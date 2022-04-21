#ifndef _SEQUENCE_RUNNER_H_
#define _SEQUENCE_RUNNER_H_

#include "SharedCommands.h"

class SequenceSaver {
    FingerPosition *poses;
    int length;

public:
    SequenceSaver(int length, FingerPosition * pos) {
        this->length = length;
        poses = pos;
    }

    ~SequenceSaver() {
        delete[] poses;
    }

    void push(FingerPosition pos) {
        for (int i = length - 1; i > 0; i--) {
            // Serial.printf("Setting [%d] to [%d] / %d\n", i, i-1, poses[i-1]);
            poses[i] = poses[i - 1];
        }
        // Serial.printf("Setting [0] to %d\n", pos);
        poses[0] = pos;
    }

    bool matches(int seqLength, FingerPosition *pos) {
        if (seqLength != length) {
            // Serial.printf("Does not match length\n");
            return false;
        }

        for (int i = 0; i < seqLength; i++) {
            if (pos[i] != poses[i]) {
                // Serial.printf("[%d] %d != %d \n", i, pos[i], poses[i]);
                return false;
            }
        }

        return true;
    }

    void print() {
        for (int i = 0 ; i < length; i++) {
            Serial.printf("%d, ", poses[i]);
        }
        Serial.println();
    }
};

#endif