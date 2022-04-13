/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/deedp/Documents/IOT/SmartGlove/NeuralNetTest1/src/NeuralNetTest1.ino"
/*
 * Project NeuralNetTest1
 * Description: Test for neural network only using the pointer and middle finger
 * Author: Devon Palma
 * Date: 4/11/2022
 */
int diff();
int scale(int value, int min, int max);
void setup();
void loop();
#line 7 "c:/Users/deedp/Documents/IOT/SmartGlove/NeuralNetTest1/src/NeuralNetTest1.ino"
SYSTEM_MODE(SEMI_AUTOMATIC);

#include <math.h>

const int POINTER_H_PIN = A2;
const int POINTER_L_PIN = A3;
const int MIDDLE_H_PIN = A4;
const int MIDDLE_L_PIN = A5;

const int RED_BUTTON_PIN = D2;
const int BLUE_BUTTON_PIN = D3;
const int CALIBRATE_LED_PIN = D4;

class ezScale {

public:
    int _min = 1000000;
    int _max = -1000000;

    int diff() {
        return _max - _min;
    }

    int scale(int value, int min, int max) {
        return map(value, _min, _max, min, max);
    }
};

ezScale pHScale;
ezScale pLScale;
ezScale mHScale;
ezScale mLScale;

void setup() {
    Serial.begin(9600);
    while (!Serial)
        ;
    pinMode(POINTER_H_PIN, INPUT);
    pinMode(POINTER_L_PIN, INPUT);
    pinMode(MIDDLE_H_PIN, INPUT);
    pinMode(MIDDLE_L_PIN, INPUT);
    pinMode(RED_BUTTON_PIN, INPUT_PULLUP);
    pinMode(BLUE_BUTTON_PIN, INPUT_PULLUP);
    pinMode(CALIBRATE_LED_PIN, OUTPUT);

}

void loop() {
    static bool lastRedState = digitalRead(RED_BUTTON_PIN);
    static bool lastBlueState = digitalRead(BLUE_BUTTON_PIN);
    bool curRedState = digitalRead(RED_BUTTON_PIN);
    bool curBlueState = digitalRead(BLUE_BUTTON_PIN);


    if (!lastRedState && curRedState) {
        pHScale._min = analogRead(POINTER_H_PIN);
        pLScale._min = analogRead(POINTER_L_PIN);
        mHScale._min = analogRead(MIDDLE_H_PIN);
        mLScale._min = analogRead(MIDDLE_L_PIN);
    }

    if (!lastBlueState && curBlueState) {
        pHScale._max = analogRead(POINTER_H_PIN);
        pLScale._max = analogRead(POINTER_L_PIN);
        mHScale._max = analogRead(MIDDLE_H_PIN);
        mLScale._max = analogRead(MIDDLE_L_PIN);
    }

    int pH = pHScale.scale(analogRead(POINTER_H_PIN), 0, 99);
    int pL = pLScale.scale(analogRead(POINTER_L_PIN), 0, 99);
    int mH = mHScale.scale(analogRead(MIDDLE_H_PIN), 0, 99);
    int mL = mLScale.scale(analogRead(MIDDLE_L_PIN), 0, 99);

    Serial.printf("PH: %02d    PL: %02d   MH: %02d   ML: %02d\n", pH, pL, mH, mL);

    lastRedState = curRedState;
    lastBlueState = curBlueState;
}