#ifndef _SHARED_COMMANDS_H_
#define _SHARED_COMMANDS_H_


enum MainCommands {
    PROGRAM = 0x0,
    STATUS = 0x1,
    REQUEST = 0x2,
    BEST_FINGER = 0x3,
};

const int HAND_POS_COUNT = 32;
enum FingerPosition {
    F_00000 = 0x00,
    F_00001 = 0x01,
    F_00010 = 0x02,
    F_00011 = 0x03,
    F_00100 = 0x04,
    F_00101 = 0x05,
    F_00110 = 0x06,
    F_00111 = 0x07,
    F_01000 = 0x08,
    F_01001 = 0x09,
    F_01010 = 0x0A,
    F_01011 = 0x0B,
    F_01100 = 0x0C,
    F_01101 = 0x0D,
    F_01110 = 0x0E,
    F_01111 = 0x0F,
    F_10000 = 0x10,
    F_10001 = 0x11,
    F_10010 = 0x12,
    F_10011 = 0x13,
    F_10100 = 0x14,
    F_10101 = 0x15,
    F_10110 = 0x16,
    F_10111 = 0x17,
    F_11000 = 0x18,
    F_11001 = 0x19,
    F_11010 = 0x1A,
    F_11011 = 0x1B,
    F_11100 = 0x1C,
    F_11101 = 0x1D,
    F_11110 = 0x1E,
    F_11111 = 0x1F,
};

enum RequestSubCommands {
    BEST = 0x00,
};

enum Statuses {
    PROGRAM_SUCCESSFUL = 0x00,

    UNIMPLEMENTED_COMMAND = 0x10,
    NO_DATA_AVAILABLE = 0x11,
    REQUEST_FAILED = 0x12,
};

void readCommand(byte *mainCmd, byte *data) {
    if (Serial.available() > 0) {
        byte packet = Serial.read();
        *mainCmd = (packet & 0xE0) >> 5;
        *data = (packet & 0x1F);
    } else {
        *mainCmd = STATUS;
        *data = NO_DATA_AVAILABLE;
    }
}

void sendCommand(byte mainCmd, byte data) {
    Serial.write(mainCmd << 5 | data);
}

#endif