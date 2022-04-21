#ifndef _PROGRAM_CONTROLLER_H_
#define _PROGRAM_CONTROLLER_H_

#include "MultiplexerCollector.h"
#include "SharedCommands.h"

class ProgramController {
    MultiplexerCollection *allSigns;
    Multiplexer *myMulp;

    bool isProgrammerEnabled = false;

public:
    ProgramController(Multiplexer *myMulp) {
        this->myMulp = myMulp;
        allSigns = new MultiplexerCollection[HAND_POS_COUNT];
    }

    ~ProgramController() {
        delete[] allSigns;
    }

    void begin() {
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
        int bestVal = 1000000000; 
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
        MultiplexerCollection mpc(myMulp);
        return getBestCollection(&mpc);
    }

private:
    void programFingerPosition(byte fingerPos) {
        if (fingerPos < HAND_POS_COUNT) {
            MultiplexerCollection mpc(myMulp);
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
            for (int i = 0; i < HAND_POS_COUNT; i++) {
                Serial.printf("Wiped %d/%d\n", i + 1, HAND_POS_COUNT);
                allSigns[i].clear();
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