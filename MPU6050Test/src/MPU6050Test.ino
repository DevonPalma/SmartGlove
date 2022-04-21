#include <MPU6050.h>

SYSTEM_MODE(SEMI_AUTOMATIC);

const int INTERRUPT_PIN = A2;

int lastTimeFacingUp;

MPU6050 myMPU;

void setup() {
    myMPU.begin();
    myMPU.setGyroscopeRange(2);
}

void loop() {
    Vector3<float> gravityData = myMPU.getGravityData();
    Vector3<float> rotationData = myMPU.getRotationData();

    if (rotationData.X > 400) {
        Serial.printf("Rotating +X\n");
    } else if (rotationData.X < -400) {
        Serial.printf("Rotating -X\n");
    }

    // Serial.printf("GX: %04.2f    GY: %04.2f    GZ: %04.2f   ", gravityData.X, gravityData.Y, gravityData.Z);
    Serial.printf("RX: %04.2f    RY: %04.2f    RZ: %04.2f\n", rotationData.X, rotationData.Y, rotationData.Z);
}