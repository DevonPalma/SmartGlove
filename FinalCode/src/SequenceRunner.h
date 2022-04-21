#ifndef _SEQUENCE_RUNNER_H_
#define _SEQUENCE_RUNNER_H_

#include "SharedCommands.h"

class SequenceSaver {
    FingerPosition *poses;
    int length;

public:
    SequenceSaver(int length) {
        this->length = length;
        poses = new FingerPosition[length];
    }

    ~SequenceSaver() {
        delete[] poses;
    }

    void push(FingerPosition pos) {
        for (int i = length - 1; i > 0; i--) {
            poses[i] = poses[i - 1];
        }
        poses[0] = pos;
    }

    bool matches(int seqLength, FingerPosition *pos) {
        if (seqLength != length) {
            return false;
        }

        for (int i = 0; i < seqLength; i++) {
            if (pos[i] != poses[i]) {
                return false;
            }
        }

        return true;
    }
};

#endif