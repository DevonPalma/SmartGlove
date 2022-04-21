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
bool timer10MS();
#line 8 "c:/Users/deedp/Documents/IOT/SmartGlove/FinalCode/src/FinalCode.ino"
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

ProgramController programmer(P_MULP_ENABLE, P_MULP_S0, P_MULP_S1, P_MULP_S2, P_MULP_S3, P_MULP_SIGNAL);
MPU6050 myMPU;

SequenceSaver comparer(3);
SequenceSaver curData(3);

void setup() {
    programmer.begin();
    programmer.enableProgrammer(); // Enables programming the controller via byte commands if needed
    myMPU.begin();
    comparer.push(P_10011);
    comparer.push(P_00010);
    comparer.push(P_00110);
}

void loop() {
    programmer.update(); // does basically nothing if enableProgrammer isn't called

    if (timer10MS()) {
        static FingerPosition lastPos;
        static FingerPosition lastAdded;
        static int lastChangeTime = millis();
        FingerPosition curPos = (FingerPosition)programmer.getBestCollection();
        int curTime = millis();

        if (lastPos != curPos) {
            if (curTime - lastChangeTime > 600 && lastAdded != curPos) {
                curData.push(curPos);
                lastAdded = curPos;
                Serial.printf("Added ");
                Serial.printf("%d", (curPos & 0x10) >> 4);
                Serial.printf("%d", (curPos & 0x08) >> 3);
                Serial.printf("%d", (curPos & 0x04) >> 2);
                Serial.printf("%d", (curPos & 0x02) >> 1);
                Serial.printf("%d", (curPos & 0x01));
                Serial.printf(" to curData\n", curPos);
            }
            lastPos = curPos;
            lastChangeTime = curTime;
        }
    }
}

bool timer10MS() {
    static int lastTime = millis();
    int curTime = millis();

    if (curTime - lastTime > 10) {
        lastTime = curTime;
        return true;
    }
    return false;
}