#ifndef _MULTIPLEXER_COLLECTOR_H_
#define _MULTIPLEXER_COLLECTOR_H_

#include "Multiplexer.h"
#include "PinData.h"
#include <math.h>

struct MultiplexerCollection {
    byte thumb;
    byte pointer;
    byte middle;
    byte ring;
    byte pinky;

    // Analogread (which is what the multiplexer reads w/) returns w/ 12 bit percision (0-4095)
    // It returns the value in a uint32_t which is 4 bytes. As I plan on writing this struct to
    // EEPROM I decided it'd be better to use a single byte for each finger.
    // This results in a simple range conversion of [VAL * (2^8/2^12)] or [VAL / 2^4] or [VAL/16]
    // Fingers range now between 0-255

    MultiplexerCollection() {}

    MultiplexerCollection(Multiplexer *mulp) {
        thumb = mulp->read(M_THUMB) / 16;
        pointer = mulp->read(M_POINTER) / 16;
        middle = mulp->read(M_MIDDLE) / 16;
        ring = mulp->read(M_RING) / 16;
        pinky = mulp->read(M_PINKY) / 16;
    }

    void set(MultiplexerCollection *mulpC) {
        thumb = mulpC->thumb;
        pointer = mulpC->pointer;
        middle = mulpC->middle;
        ring = mulpC->ring;
        pinky = mulpC->pinky;
    }

    void clear() {
        thumb = 0;
        pointer = 0;
        middle = 0;
        ring = 0;
        pinky = 0;
    }

    bool isSet() {
        return thumb != 0 &&
               pointer != 0 &&
               middle != 0 &&
               ring != 0 &&
               pinky != 0;
    }

    // compares how close a mulp is to another (Sum of differences between each finger)
    int compare(MultiplexerCollection *mulpC) {
        int val = 0;
        val += abs(thumb - mulpC->thumb) ;
        val += abs(pointer - mulpC->pointer);
        val += abs(middle - mulpC->middle);
        val += abs(ring - mulpC->ring);
        val += abs(pinky - mulpC->pinky) ;
        return val;
    }

    void saveToEEPROM(int index) {
        int startIndex = index * 5;
        EEPROM.write(startIndex + 0, thumb);
        EEPROM.write(startIndex + 1, pointer);
        EEPROM.write(startIndex + 2, middle);
        EEPROM.write(startIndex + 3, ring);
        EEPROM.write(startIndex + 4, pinky);
    }

    void loadFromEEPROM(int index) {
        int startIndex = index * 5;
        thumb = EEPROM.read(startIndex + 0);
        pointer = EEPROM.read(startIndex + 1);
        middle = EEPROM.read(startIndex + 2);
        ring = EEPROM.read(startIndex + 3);
        pinky = EEPROM.read(startIndex + 4);
    }
};
#endif