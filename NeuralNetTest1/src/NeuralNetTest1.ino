/*
 * Project NeuralNetTest1
 * Description: Test for neural network only using the pointer and middle finger
 * Author: Devon Palma
 * Date: 4/11/2022
 */
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
    void calibrate(int value) {
        if (value < _min) {
            _min = value;
        }
        if (value > _max) {
            _max = value;
        }
    }

    int diff() {
        return _max - _min;
    }

    int scale(int value, int min, int max) {
        calibrate(value);
        return map(value, _min, _max, min, max);
    }
};

ezScale pHScale;
ezScale pLScale;
ezScale mHScale;
ezScale mLScale;

void setup() {
    Serial.begin(9600);
    while (!Serial);
    pinMode(POINTER_H_PIN, INPUT);
    pinMode(POINTER_L_PIN, INPUT);
    pinMode(MIDDLE_H_PIN, INPUT);
    pinMode(MIDDLE_L_PIN, INPUT);
    pinMode(RED_BUTTON_PIN, INPUT_PULLUP);
    pinMode(BLUE_BUTTON_PIN, INPUT_PULLUP);
    pinMode(CALIBRATE_LED_PIN, OUTPUT);

    digitalWrite(CALIBRATE_LED_PIN, HIGH);
    {
        int startTime = millis();
        while (millis() - startTime < 5000) {
            pHScale.calibrate(analogRead(POINTER_H_PIN));
            pLScale.calibrate(analogRead(POINTER_L_PIN));
            mHScale.calibrate(analogRead(MIDDLE_H_PIN));
            mLScale.calibrate(analogRead(MIDDLE_L_PIN));
        }
        Serial.printf("Pointer High Scale Range: %d -> %d  [%d]\n", pHScale._min, pHScale._max, pHScale.diff());
        Serial.printf("Pointer Low Scale Range: %d -> %d  [%d]\n", pLScale._min, pLScale._max, pLScale.diff());
        Serial.printf("Middle High Scale Range: %d -> %d  [%d]\n", mHScale._min, mHScale._max, mHScale.diff());
        Serial.printf("Middle Low Scale Range: %d -> %d  [%d]\n", mLScale._min, mLScale._max, mLScale.diff());
    }
    digitalWrite(CALIBRATE_LED_PIN, LOW);
}

void loop() {
    static bool lastRedState = digitalRead(RED_BUTTON_PIN);
    static bool lastBlueState = digitalRead(BLUE_BUTTON_PIN);
    bool curRedState = digitalRead(RED_BUTTON_PIN);
    bool curBlueState = digitalRead(BLUE_BUTTON_PIN);

    int pH = pHScale.scale(analogRead(POINTER_H_PIN), 0, 255);
    int pL = pHScale.scale(analogRead(POINTER_L_PIN), 0, 255);
    int mH = pHScale.scale(analogRead(MIDDLE_H_PIN), 0, 255);
    int mL = pHScale.scale(analogRead(MIDDLE_L_PIN), 0, 255);

    if (!lastRedState && curRedState) {
        Serial.printf("R:%d,%d,%d,%d", pH, pL, mH, mL);
    }
    if (!lastBlueState && curBlueState) {
        Serial.printf("B:%d,%d,%d,%d", pH, pL, mH, mL);
    }

    lastRedState = curRedState;
    lastBlueState = curBlueState;
}