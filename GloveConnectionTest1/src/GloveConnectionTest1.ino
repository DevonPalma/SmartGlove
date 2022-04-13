/*
 * Project GloveConnectionTest1
 * Description: Test the full connection of my glove
 * Author: Devon Palma
 * Date: 4/12/2022
 */

SYSTEM_MODE(SEMI_AUTOMATIC);

#include "EZButton.h"
#include "Multiplexer.h"

const int RED_BUTTON_PIN = D8;
const int BLUE_BUTTON_PIN = D7;

const int MULTI_ENABLE_PIN = D6;
const int MULTI_S0_PIN = D2;
const int MULTI_S1_PIN = D3;
const int MULTI_S2_PIN = D4;
const int MULTI_S3_PIN = D5;
const int MULTI_SIGNAL_PIN = A5;

Multiplexer mp(MULTI_ENABLE_PIN, MULTI_S0_PIN, MULTI_S1_PIN, MULTI_S2_PIN, MULTI_S3_PIN, MULTI_SIGNAL_PIN);
EZButton redButton(RED_BUTTON_PIN);
EZButton blueButton(BLUE_BUTTON_PIN);

int maxVals[9];
int minVals[9];

void setup() {
    Serial.begin();
    blueButton.onPressed(&onBluePressed);
    blueButton.onRelease(&onBlueRelease);
    redButton.onPressed(&onRedPressed);
    redButton.onRelease(&onRedRelease);
}

void loop() {
    blueButton.update();
    redButton.update();
}

void onBluePressed() {
    Serial.printf("Differnces between min and max\n");
    for (int i = 0; i < 9; i++) {
        Serial.printf("%d: %d    ", i, maxVals[i] - minVals[i]);
    }
    Serial.printf("\n");
}

void onBlueRelease() {
    Serial.printf("Closer to min val?\n");
    for (int i = 0; i < 9; i++) {
        int curVal = mp.read(i);
        int mid = (maxVals[i] + minVals[i]) / 2;
        Serial.printf("%d: %s    ", i, curVal < mid ? "T" : "F");
    }
    Serial.printf("\n");
}

void onRedPressed() {
    Serial.printf("Updating max vals\n");
    for (int i = 0; i < 9; i++) {
        maxVals[i] = mp.read(i);
        Serial.printf("%d: %d    ", i, maxVals[i]);
    }
    Serial.printf("\n");
}

void onRedRelease() {
    Serial.printf("Updating min vals\n");
    for (int i = 0; i < 9; i++) {
        minVals[i] = mp.read(i);
        Serial.printf("%d: %d    ", i, minVals[i]);
    }
    Serial.printf("\n");
}