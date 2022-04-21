#ifndef _PROGRAM_CONTROLLER_H_
#define _PROGRAM_CONTROLLER_H_

#include "MultiplexerCollector.h"
#include "SharedCommands.h"

class ProgramController {
    Multiplexer myMulp;
    MultiplexerCollection *allSigns;

    bool isProgrammerEnabled = false;

public:
    ProgramController(int P_MULP_ENABLE, int P_MULP_S0, int P_MULP_S1, int P_MULP_S2, int P_MULP_S3, int P_MULP_SIGNAL) : myMulp(P_MULP_ENABLE, P_MULP_S0, P_MULP_S1, P_MULP_S2, P_MULP_S3, P_MULP_SIGNAL) {

        allSigns = new MultiplexerCollection[HAND_POS_COUNT];
    }

    ~ProgramController() {
        delete[] allSigns;
    }

    void begin() {
        myMulp.begin();
        for (int i = 0; i < HAND_POS_COUNT; i++) {
            allSigns[i].loadFromEEPROM(i);
        }
    }

    void enableProgrammer() {
        isProgrammerEnabled = true;
    }

    void update() {
        if (isProgrammerEnabled && Serial.available() > 0) {
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
                Serial.printf("Unknown command\n");
                break;
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

    int getBestCollection() {
        MultiplexerCollection mpc(&myMulp);
        return getBestCollection(&mpc);
    }

private:
    void programFingerPosition(byte fingerPos) {
        if (fingerPos < HAND_POS_COUNT) {
            MultiplexerCollection mpc(&myMulp);
            allSigns[fingerPos].set(&mpc);
            allSigns[fingerPos].saveToEEPROM(fingerPos);
            Serial.printf("Programmed finger pos %x\n", fingerPos);
        }
    }

    void handleRequest(byte request) {
        Request req = (Request)request;

        switch (req) {
        case BEST: {
            int bestCol = getBestCollection();
            Serial.printf("Best collection is %d\n", bestCol);
        } break;
        case WIPE: {
            Serial.printf("Beginning wipe\n");
            MultiplexerCollection empty;
            for (int i = 0; i < HAND_POS_COUNT; i++) {
                Serial.printf("Wiped %d/%d\n", i + 1, HAND_POS_COUNT);
                allSigns[i].set(&empty);
                allSigns[i].saveToEEPROM(i);
            }
            Serial.printf("Wipe completed\n");
        } break;
        default:
            break;
        }
    }
};

#endif