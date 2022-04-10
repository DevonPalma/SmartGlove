#include <MPU6050.h>

SYSTEM_MODE(SEMI_AUTOMATIC);

const int INTERRUPT_PIN = A2;

MPU6050 myMPU;

void setup() {
    myMPU.begin();
    myMPU.setDataReadyInterrupt(true);
    pinMode(INTERRUPT_PIN, INPUT);
}

void loop() {
    if (digitalRead(INTERRUPT_PIN)) {
        Serial.printf("Yo data ready Bitch");
    }
    // Vector3<float> gravityData = myMPU.getGravityData();
    // Vector3<float> rotationData = myMPU.getRotationData();

    // Serial.printf("GX: %.2f    GY: %.2f    GZ: %.2f   ", gravityData.X, gravityData.Y, gravityData.Z);
    // Serial.printf("RX: %.2f    RY: %.2f    RZ: %.2f\n", rotationData.X, rotationData.Y, rotationData.Z);
    
}