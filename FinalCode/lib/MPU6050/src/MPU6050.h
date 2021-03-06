/*
 * Project MPU6050 Controller
 * Description: Manage all aspects of an MPU controller
 * Author: Devon Palma
 * Date: 3/29/2022
 */

#ifndef _MPU6050_H_
#define _MPU6050_H_

#include <Math.h>
#include "I2CHelper.h"

const int MPU6050_ADDRESS_GROUND = 0x68;
const int MPU6050_ADDRESS_HIGH = 0x69;

template <typename T>
struct Vector3 {
    T X;
    T Y;
    T Z;
};

enum MPU6050_Registers {
    SELF_TEST_X = 0x0D,        // R/W
    SELF_TEST_Y = 0x0E,        // R/W
    SELF_TEST_Z = 0x0F,        // R/W
    SELF_TEST_A = 0x10,        // R/W
    SMPLRT_DIV = 0x19,         // R/W
    CONFIG = 0x1A,             // R/W
    GYRO_CONFIG = 0x1B,        // R/W
    ACCEL_CONFIG = 0x1C,       // R/W
    FIFO_EN = 0x23,            // R/W
    I2C_MST_CTRL = 0x24,       // R/W
    I2C_SLV0_ADDR = 0x25,      // R/W
    I2C_SLV0_REG = 0x26,       // R/W
    I2C_SLV0_CTRL = 0x27,      // R/W
    I2C_SLV1_ADDR = 0x28,      // R/W
    I2C_SLV1_REG = 0x29,       // R/W
    I2C_SLV1_CTRL = 0x2A,      // R/W
    I2C_SLV2_ADDR = 0x2B,      // R/W
    I2C_SLV2_REG = 0x2C,       // R/W
    I2C_SLV2_CTRL = 0x2D,      // R/W
    I2C_SLV3_ADDR = 0x2E,      // R/W
    I2C_SLV3_REG = 0x2F,       // R/W
    I2C_SLV3_CTRL = 0x30,      // R/W
    I2C_SLV4_ADDR = 0x31,      // R/W
    I2C_SLV4_REG = 0x32,       // R/W
    I2C_SLV4_DO = 0x33,        // R/W
    I2C_SLV4_CTRL = 0x34,      // R/W
    I2C_SLV4_DI = 0x35,        // R
    I2C_MST_STATUS = 0x36,     // R
    INT_PIN_CFG = 0x37,        // R/W
    INT_ENABLE = 0x38,         // R/W
    INT_STATUS = 0x3A,         // R
    ACCEL_XOUT_H = 0x3B,       // R
    ACCEL_XOUT_L = 0x3C,       // R
    ACCEL_YOUT_H = 0x3D,       // R
    ACCEL_YOUT_L = 0x3E,       // R
    ACCEL_ZOUT_H = 0x3F,       // R
    ACCEL_ZOUT_L = 0x40,       // R
    TEMP_OUT_H = 0x41,         // R
    TEMP_OUT_L = 0x42,         // R
    GYRO_XOUT_H = 0x43,        // R
    GYRO_XOUT_L = 0x44,        // R
    GYRO_YOUT_H = 0x45,        // R
    GYRO_YOUT_L = 0x46,        // R
    GYRO_ZOUT_H = 0x47,        // R
    GYRO_ZOUT_L = 0x48,        // R
    EXT_SENS_DATA_00 = 0x49,   // R
    EXT_SENS_DATA_01 = 0x4A,   // R
    EXT_SENS_DATA_02 = 0x4B,   // R
    EXT_SENS_DATA_03 = 0x4C,   // R
    EXT_SENS_DATA_04 = 0x4D,   // R
    EXT_SENS_DATA_05 = 0x4E,   // R
    EXT_SENS_DATA_06 = 0x4F,   // R
    EXT_SENS_DATA_07 = 0x50,   // R
    EXT_SENS_DATA_08 = 0x51,   // R
    EXT_SENS_DATA_09 = 0x52,   // R
    EXT_SENS_DATA_10 = 0x53,   // R
    EXT_SENS_DATA_11 = 0x54,   // R
    EXT_SENS_DATA_12 = 0x55,   // R
    EXT_SENS_DATA_13 = 0x56,   // R
    EXT_SENS_DATA_14 = 0x57,   // R
    EXT_SENS_DATA_15 = 0x58,   // R
    EXT_SENS_DATA_16 = 0x59,   // R
    EXT_SENS_DATA_17 = 0x5A,   // R
    EXT_SENS_DATA_18 = 0x5B,   // R
    EXT_SENS_DATA_19 = 0x5C,   // R
    EXT_SENS_DATA_20 = 0x5D,   // R
    EXT_SENS_DATA_21 = 0x5E,   // R
    EXT_SENS_DATA_22 = 0x5F,   // R
    EXT_SENS_DATA_23 = 0x60,   // R
    I2C_SLV0_DO = 0x63,        // R/W
    I2C_SLV1_DO = 0x64,        // R/W
    I2C_SLV2_DO = 0x65,        // R/W
    I2C_SLV3_DO = 0x66,        // R/W
    I2C_MST_DELAY_CTRL = 0x67, // R/W
    SIGNAL_PATH_RESET = 0x68,  // R/W
    USER_CTRL = 0x6A,          // R/W
    PWR_MGMT_1 = 0x6B,         // R/W
    PWR_MGMT_2 = 0x6C,         // R/W
    FIFO_COUNTH = 0x72,        // R/W
    FIFO_COUNTL = 0x73,        // R/W
    FIFO_R_W = 0x74,           // R/W
    WHO_AM_I = 0x75,           // R
};

enum MPU6050_CLOCK_SOURCE {
    PLL_INTERNAL,
    PLL_GYRO_Y,
    PLL_GYRO_X,
    PLL_GYRO_Z,
    PLL_32KHZ,
    PLL_19MHZ,
    PLL_RESERVED,
    PLL_STOP,
};

class MPU6050 {
private:
    byte _address;
    byte _interupted;

    // Register 1B GYRO_CONFIG
    bool XG_ST;
    bool YG_ST;
    bool ZG_ST;
    byte FS_SEL;

    // Register 1C ACCEL_CONFIG
    bool XA_ST;
    bool YA_ST;
    bool ZA_ST;
    byte AFS_SEL;

    // Register 3A INT_ENABLE
    bool FIFO_OFLOW_EN;
    bool I2C_MST_INT_EN;
    bool DATA_RDY_EN;

    // Register 6N: Power Management 1
    bool DEVICE_RESET;
    bool SLEEP;
    bool CYCLE;
    bool TEMP_DIS;
    byte CLKSEL;

protected:
    void loadAllConfig();

    void loadGyroscopeConfig();
    void saveGyroscopeConfig();

    void loadAccelerometerConfig();
    void saveAccelerometerConfig();

    void loadInterruptEnableConfig();
    void saveInterruptEnableConfig();

    void loadPowerManagement1Config();
    void savePowerManagement1Config();

public:
    MPU6050() : MPU6050(MPU6050_ADDRESS_GROUND) {}
    MPU6050(byte address);

    // Starts up the MPU6050
    void begin();


    // -------- CONFIGURATION ----------

    /* Gyroscope accepted ranges
     * Range(0) = +/- 250 DEG/Sec
     * Range(1) = +/- 500 DEG/Sec
     * Range(2) = +/- 1000 DEG/Sec
     * Range(3) = +/- 2000 DEG/Sec
     */
    void setGyroscopeRange(byte newRange);
    
    /* Accelerometer accepted ranges
     * Range(0) = +/- 2g
     * Range(1) = +/- 4g
     * Range(2) = +/- 8g
     * Range(3) = +/- 16g
     */
    void setAccelerometerRange(byte newRange);

    // Sets the source of the clock.
    void setClockSource(MPU6050_CLOCK_SOURCE source);

    void setFifoInterrupt(bool status);
    void setI2CMasterInterrupt(bool status);
    void setDataReadyInterrupt(bool status);


    // ------------ DATA RETRIEVEAL -----------
    void getAccelerationData(int16_t *x, int16_t *y, int16_t *z);
    Vector3<int16_t> getAccelerationData();

    void getGyroscopeData(int16_t *x, int16_t *y, int16_t *z);
    Vector3<int16_t> getGyroscopeData();

    void getGravityData(float *x, float *y, float *z);
    Vector3<float> getGravityData();

    void getRotationData(float *x, float *y, float *z);
    Vector3<float> getRotationData();
};

#endif