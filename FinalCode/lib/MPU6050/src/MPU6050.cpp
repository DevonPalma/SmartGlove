#include "MPU6050.h"

// ------------- MPU6050 ----------------

// Protected Functions

void MPU6050::loadAllConfig() {
    loadGyroscopeConfig();
    loadAccelerometerConfig();
    loadPowerManagement1Config();
    loadInterruptEnableConfig();
}

void MPU6050::loadGyroscopeConfig() {
    WireReader reader(_address, GYRO_CONFIG);
    byte cfg = reader.read();

    XG_ST = (cfg & 0b10000000) >> 7;
    YG_ST = (cfg & 0b01000000) >> 6;
    ZG_ST = (cfg & 0b00100000) >> 5;
    FS_SEL = (cfg & 0b00011000) >> 3;
}

void MPU6050::saveGyroscopeConfig() {
    byte cfg = (XG_ST << 7) |
               (YG_ST << 6) |
               (ZG_ST << 5) |
               (FS_SEL << 3);
    WireWriter writer(_address, GYRO_CONFIG);
    writer.write(cfg);
}

void MPU6050::loadAccelerometerConfig() {
    WireReader reader(_address, ACCEL_CONFIG);
    byte cfg = reader.read();

    XA_ST = (cfg & 0b10000000) >> 7;
    YA_ST = (cfg & 0b01000000) >> 6;
    ZA_ST = (cfg & 0b00100000) >> 5;
    AFS_SEL = (cfg & 0b00011000) >> 3;
}

void MPU6050::saveAccelerometerConfig() {
    byte cfg = (XA_ST << 7) |
               (YA_ST << 6) |
               (ZA_ST << 5) |
               (AFS_SEL << 3);
    WireWriter writer(_address, ACCEL_CONFIG);
    writer.write(cfg);
}

void MPU6050::loadInterruptEnableConfig() {
    WireReader reader(_address, INT_ENABLE);
    byte cfg = reader.read();
    FIFO_OFLOW_EN = (cfg & 0b00010000) >> 4;
    I2C_MST_INT_EN = (cfg & 0b00001000) >> 3;
    DATA_RDY_EN = (cfg & 0b00000001);
}

void MPU6050::saveInterruptEnableConfig() {
    byte cfg = (FIFO_OFLOW_EN << 4) |
               (I2C_MST_INT_EN << 3) |
               (DATA_RDY_EN);
    WireWriter writer(_address, INT_ENABLE);
    writer.write(cfg);
}

void MPU6050::loadPowerManagement1Config() {
    WireReader reader(_address, PWR_MGMT_1);
    byte cfg = reader.read();

    DEVICE_RESET = (cfg & 0b10000000) >> 7;
    SLEEP = (cfg & 0b01000000) >> 6;
    CYCLE = (cfg & 0b00100000) >> 5;
    TEMP_DIS = (cfg & 0b00001000) >> 3;
    CLKSEL = (cfg & 0b00000111);
}

void MPU6050::savePowerManagement1Config() {
    byte cfg = (DEVICE_RESET << 7) |
               (SLEEP << 6) |
               (CYCLE << 5) |
               (TEMP_DIS << 3) |
               (CLKSEL);
    WireWriter writer(_address, PWR_MGMT_1);
    writer.write(cfg);
}

// Public Functions

MPU6050::MPU6050(byte address) {
    _address = address;
}

void MPU6050::begin() {
    if (!Wire.isEnabled()) {
        Serial.printf("MPU6050 > Enabling Wire\n");
        Wire.begin();
    }

    loadAllConfig();

    {
        WireWriter writer(_address, PWR_MGMT_1);
        writer.write(0x00);
    }
}

void MPU6050::setGyroscopeRange(byte newRange) {
    if (newRange < 0 || newRange > 3) {
        Serial.printf("MPU6050 > Expected gyroscope range between 0 and 3, got %d\n", newRange);
        return;
    }

    FS_SEL = newRange;

    saveGyroscopeConfig();
}

void MPU6050::setAccelerometerRange(byte newRange) {
    if (newRange < 0 || newRange > 3) {
        Serial.printf("MPU6050 > Expected accelerometer range between 0 and 3, got %d\n", newRange);
        return;
    }

    AFS_SEL = newRange;

    saveAccelerometerConfig();
}

void MPU6050::setClockSource(MPU6050_CLOCK_SOURCE source) {
    CLKSEL = source;
    savePowerManagement1Config();
}

void MPU6050::setFifoInterrupt(bool status) {
    FIFO_OFLOW_EN = status;
    saveInterruptEnableConfig();
}
void MPU6050::setI2CMasterInterrupt(bool status) {
    I2C_MST_INT_EN = status;
    saveInterruptEnableConfig();
}
void MPU6050::setDataReadyInterrupt(bool status) {
    DATA_RDY_EN = status;
    saveInterruptEnableConfig();
}

void MPU6050::getAccelerationData(int16_t *x, int16_t *y, int16_t *z) {
    WireReader reader(_address, ACCEL_XOUT_H, 6);

    { // reads in the X val
        byte x_h = reader.read();
        byte x_l = reader.read();
        *x = x_h << 8 | x_l;
    }

    { // Reads in the Y val
        byte y_h = reader.read();
        byte y_l = reader.read();
        *y = y_h << 8 | y_l;
    }

    { // Reads in the Z val
        byte z_h = reader.read();
        byte z_l = reader.read();
        *z = z_h << 8 | z_l;
    }
}

Vector3<int16_t> MPU6050::getAccelerationData() {
    Vector3<int16_t> data;
    getAccelerationData(&data.X, &data.Y, &data.Z);
    return data;
}

void MPU6050::getGyroscopeData(int16_t *x, int16_t *y, int16_t *z) {
    WireReader reader(_address, GYRO_XOUT_H, 6);

    { // reads in the X val
        byte x_h = reader.read();
        byte x_l = reader.read();
        *x = x_h << 8 | x_l;
    }

    { // Reads in the Y val
        byte y_h = reader.read();
        byte y_l = reader.read();
        *y = y_h << 8 | y_l;
    }

    { // Reads in the Z val
        byte z_h = reader.read();
        byte z_l = reader.read();
        *z = z_h << 8 | z_l;
    }
}

Vector3<int16_t> MPU6050::getGyroscopeData() {
    Vector3<int16_t> data;
    getGyroscopeData(&data.X, &data.Y, &data.Z);
    return data;
}

void MPU6050::getGravityData(float *x, float *y, float *z) {
    int16_t ax, ay, az;
    getAccelerationData(&ax, &ay, &az);
    float rangeHalf = pow(2, AFS_SEL) * 2;
    *x = map((float)ax, -32767.0, 32767.0, -rangeHalf, rangeHalf);
    *y = map((float)ay, -32767.0, 32767.0, -rangeHalf, rangeHalf);
    *z = map((float)az, -32767.0, 32767.0, -rangeHalf, rangeHalf);
}

Vector3<float> MPU6050::getGravityData() {
    Vector3<float> data;
    getGravityData(&data.X, &data.Y, &data.Z);
    return data;
}

void MPU6050::getRotationData(float *x, float *y, float *z) {
    int16_t ax, ay, az;
    getGyroscopeData(&ax, &ay, &az);
    float rangeHalf = pow(2, FS_SEL) * 250;
    *x = map((float)ax, -32767.0, 32767.0, -rangeHalf, rangeHalf);
    *y = map((float)ay, -32767.0, 32767.0, -rangeHalf, rangeHalf);
    *z = map((float)az, -32767.0, 32767.0, -rangeHalf, rangeHalf);
}

Vector3<float> MPU6050::getRotationData() {
    Vector3<float> data;
    getRotationData(&data.X, &data.Y, &data.Z);
    return data;
}