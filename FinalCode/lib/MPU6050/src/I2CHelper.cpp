#include "I2CHelper.h"

// ------------- Wire Writer --------------

WireWriter::WireWriter(byte address, byte reg) {
    Wire.beginTransmission(address);
    Wire.write(reg);
}

WireWriter::~WireWriter() {
    Wire.endTransmission(true);
}

void WireWriter::write(byte data) {
    Wire.write(data);
}

// ------------- Wire Reader --------------

WireReader::WireReader(byte address, byte reg, byte count) {
    Wire.beginTransmission(address);
    Wire.write(reg);
    Wire.endTransmission(false);
    Wire.requestFrom(address, count, false);
}

WireReader::~WireReader() {
    Wire.endTransmission(true);
}

byte WireReader::read() {
    return (byte)Wire.read();
}

// Bit Maniplulator

BitManipulator::BitManipulator(byte data) {
    _data = data;
}

void BitManipulator::setByte(byte data) {
    _data = data;
}

byte BitManipulator::getByte() {
    return _data;
}

bool BitManipulator::getBit(byte bitIndex) {
    return (_data & (1 << bitIndex)) ? true : false;
}

void BitManipulator::setBit(byte bitIndex) {
    _data |= (1 << bitIndex);
}

void BitManipulator::clearBit(byte bitIndex) {
    _data &= ~(1 << bitIndex);
}

void BitManipulator::toggleBit(byte bitIndex) {
    _data ^= 1 << bitIndex;
}



// ------------ Wire Overwriter --------------
WireOverwriter::WireOverwriter(byte address, byte reg) {
    _address = address;
    _reg = reg;
    {
        WireReader reader(address, reg);
        _oldData = reader.read();
    }
    _cancelled = false;
    BitManipulator::setByte(_oldData);
}

WireOverwriter::~WireOverwriter() {
    if (!_cancelled) {
        WireWriter writer(_address, _reg);
        writer.write(BitManipulator::getByte());
    }
}

void WireOverwriter::cancel() {
    _cancelled = true;
}

byte WireOverwriter::getOld() {
    return _oldData;
}