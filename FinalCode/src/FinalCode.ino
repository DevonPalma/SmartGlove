/*
 * Project: A Data Glove
 * Description: Code to read a dataglove
 * Author: Devon Palma
 * Date: 4/18/2022
 */

SYSTEM_MODE(SEMI_AUTOMATIC);

#include "MPU6050.h"
#include "Multiplexer.h"
#include "PinData.h"
#include "ProgramController.h"
#include "SequenceRunner.h"
#include "SharedCommands.h"

const int SAMPLE_RATE = 100;

// For some reason this has to be declared RIGHT after my imports IDFK
int getBestCollection(MultiplexerCollection *comparedCol);
void programFingerPosition(FingerPosition fingerPos);

Multiplexer myMulp(P_MULP_ENABLE, P_MULP_S0, P_MULP_S1, P_MULP_S2, P_MULP_S3, P_MULP_SIGNAL);
ProgramController programmer(&myMulp);

FingerPosition countUpMatch[] = {P_PEACE, P_GUN, P_ROCK};
FingerPosition countDownMatch[] = {P_ROCK, P_GUN, P_PEACE};
FingerPosition __curData[3];
SequenceSaver curData(3, __curData);

void setup() {
    myMulp.begin();
    programmer.begin();
    programmer.enableProgrammer(); // Enables programming the controller via byte commands if needed
}

void loop() {
    MultiplexerCollection s(&myMulp);

    programmer.update(); // does basically nothing if enableProgrammer isn't called

    static int fingerPosCounts[8];
    static int totalCount;
    static int startTime = millis();

    static int bestChoice;
    static int bestChoiceCount;

    int i = programmer.getBestCollection();
    fingerPosCounts[i]++;
    totalCount++;

    int curTime = millis();
    if (curTime - startTime > 100) {
        for (int i = 0; i < 8; i++) {
            float perc = (float)fingerPosCounts[i] / (float)totalCount * 100.0;
            if (perc > 80) {
                if (bestChoice == i) {
                    bestChoiceCount++;
                } else {
                    bestChoice = i;
                    bestChoiceCount = 0;
                }
            }
            fingerPosCounts[i] = 0;
        }
        totalCount = 0;
        startTime = curTime;
        if (bestChoiceCount == 6) {
            Serial.printf("Best choice: %d\n", bestChoice);
            curData.push((FingerPosition) bestChoice);
            curData.print();
        }

        if (curData.matches(3, countUpMatch)) {
            Serial.printf("Counted up hoe\n");
        }

        if (curData.matches(3, countDownMatch)) {
            Serial.printf("Counted down hoe\n");
        }
    }
}
