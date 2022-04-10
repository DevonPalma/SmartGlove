#ifndef _I2C_HELPER_H_
#define _I2C_HELPER_H_

#include <Wire.h>

// Wrapper for the Wire to easily and quickly write data
class WireWriter {
public:
    // address = the I2C address to write too
    // Reg = The initial write value AKA the register to enter initially
    WireWriter(byte address, byte reg);
    ~WireWriter();
    // Writes data then returns itself
    void write(byte data);
};

class WireReader {
public:
    // Address = the I2c address to read from
    // Reg = The initial write value AKA the register to enter initally
    // Count = The total count of how many items I wish to read
    WireReader(byte address, byte reg, byte count = 1);
    ~WireReader();
    // Places the read value into saveVar, then returns itself.
    byte read();
};

class BitManipulator {
protected:
    byte _data;
public:
    BitManipulator(byte data = 0x00);
    void setByte(byte data);
    byte getByte();
    bool getBit(byte bitIndex);    // Returns the state of the specified bit
    void setBit(byte bitIndex);    // sets the bit index to high
    void clearBit(byte bitIndex);  // sets the bit index to low
    void toggleBit(byte bitIndex); // Toggles the bit index
};

class WireOverwriter : public BitManipulator {
private:
    byte _address;
    byte _reg;
    bool _cancelled;
    byte _oldData;

public:
    WireOverwriter(byte address, byte reg);
    ~WireOverwriter();
    // Cancels the overwrite
    void cancel();
    // returns the original value of the overwriter
    byte getOld();
};

#endif