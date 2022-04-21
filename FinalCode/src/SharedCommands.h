#ifndef _SHARED_COMMANDS_H_
#define _SHARED_COMMANDS_H_


enum MainCommands {
    PROGRAM = 0x0,
    REQUEST = 0x1,
};

enum Request {
    BEST = 0x00,
    WIPE = 0x01,
};

const int HAND_POS_COUNT = 32;
enum FingerPosition {
    P_00000 = 0x00,
    P_00001 = 0x01,
    P_00010 = 0x02,
    P_00011 = 0x03,
    P_00100 = 0x04,
    P_00101 = 0x05,
    P_00110 = 0x06,
    P_00111 = 0x07,
    P_01000 = 0x08,
    P_01001 = 0x09,
    P_01010 = 0x0A,
    P_01011 = 0x0B,
    P_01100 = 0x0C,
    P_01101 = 0x0D,
    P_01110 = 0x0E,
    P_01111 = 0x0F,
    P_10000 = 0x10,
    P_10001 = 0x11,
    P_10010 = 0x12,
    P_10011 = 0x13,
    P_10100 = 0x14,
    P_10101 = 0x15,
    P_10110 = 0x16,
    P_10111 = 0x17,
    P_11000 = 0x18,
    P_11001 = 0x19,
    P_11010 = 0x1A,
    P_11011 = 0x1B,
    P_11100 = 0x1C,
    P_11101 = 0x1D,
    P_11110 = 0x1E,
    P_11111 = 0x1F,
};

void readCommand(byte *mainCmd, byte *data) {
    if (Serial.available() > 0) {
        byte packet = Serial.read();
        *mainCmd = (packet & 0xE0) >> 5;
        *data = (packet & 0x1F);
    }
}

#endif