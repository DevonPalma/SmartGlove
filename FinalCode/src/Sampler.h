#ifndef _SAMPLER_H_
#define _SAMPLER_H_

#include "SharedCommands.h"

const int SAMPLE_DURATION = 70;

class Sampler {
private:
    int lastSampleTime;
    int sampleCount[HAND_POS_COUNT];
    int totalSamples;

public:
    Sampler() {
        lastSampleTime = millis();
    }


    bool timerDone() {
        int curTime = millis();
        if (curTime - lastSampleTime > SAMPLE_DURATION) {
            lastSampleTime = curTime;
            return true;
        }
        return false;
    }

    void addSample(int s) {
        if (s < 0 || s > HAND_POS_COUNT) {
            Serial.printf("Sample out of bounds\n");
            return;
        }
        sampleCount[s]++;
        totalSamples++;
    }

    int getBestSample() {
        int bestSample = 0;

        for (int i = 1; i < HAND_POS_COUNT; i++) {
            if (sampleCount[i] > sampleCount[bestSample]) {
                bestSample = i;
            }
        }

        return bestSample;
    }

    float getSamplePercentage(int s) {
        return (float)sampleCount[s] / (float)totalSamples * 100.0;
    }

    void reset() {
        for (int i = 0; i < HAND_POS_COUNT; i++) {
            sampleCount[i] = 0;
        }
        totalSamples = 0;
    }
};

#endif