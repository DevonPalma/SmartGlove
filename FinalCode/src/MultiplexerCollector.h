#ifndef _MULTIPLEXER_COLLECTOR_H_
#define _MULTIPLEXER_COLLECTOR_H_

#include "Multiplexer.h"
#include "PinData.h"
#include <math.h>

struct MultiplexerCollection {
    byte thumb;
    byte pointer_high;
    byte pointer_low;
    byte middle_high;
    byte middle_low;
    byte ring_high;
    byte ring_low;
    byte pinky_high;
    byte pinky_low;

    // Analogread (which is what the multiplexer reads w/) returns w/ 12 bit percision (0-4095)
    // It returns the value in a uint32_t which is 4 bytes. As I plan on writing this struct to 
    // EEPROM I decided it'd be better to use a single byte for each finger. 
    // This results in a simple range conversion of [VAL * (2^8/2^12)] or [VAL / 2^4] or [VAL/16]
    // Fingers range now between 0-255

    MultiplexerCollection() {}
    
    MultiplexerCollection(Multiplexer *mulp) {
        thumb = mulp->read(M_THUMB) / 16; 
        pointer_high = mulp->read(M_POINTER_HIGH) / 16;
        pointer_low = mulp->read(M_POINTER_LOW) / 16;
        middle_high = mulp->read(M_MIDDLE_HIGH) / 16;
        middle_low = mulp->read(M_MIDDLE_LOW) / 16;
        ring_high = mulp->read(M_RING_HIGH) / 16;
        ring_low = mulp->read(M_RING_LOW) / 16;
        pinky_high = mulp->read(M_PINKY_HIGH) / 16;
        pinky_low = mulp->read(M_PINKY_LOW) / 16;
    }

    void set(MultiplexerCollection *mulpC) {
        thumb = mulpC->thumb; 
        pointer_high = mulpC->pointer_high; 
        pointer_low = mulpC->pointer_low; 
        middle_high = mulpC->middle_high; 
        middle_low = mulpC->middle_low; 
        ring_high = mulpC->ring_high; 
        ring_low = mulpC->ring_low; 
        pinky_high = mulpC->pinky_high; 
        pinky_low = mulpC->pinky_low;
    }


    bool isSet() {
        return  thumb != 0 && 
                pointer_high != 0 &&
                pointer_low != 0 &&
                middle_high != 0 &&
                middle_low != 0 &&
                ring_high != 0 &&
                ring_low != 0 &&
                pinky_high != 0 &&
                pinky_low != 0; 
    }

    // compares how close a mulp is to another (Sum of differences between each finger)
    int compare(MultiplexerCollection *mulpC) {
        int val = 0;
        val += abs(thumb - mulpC->thumb);
        val += abs(pointer_high - mulpC->pointer_high);
        val += abs(pointer_low - mulpC->pointer_low);
        val += abs(middle_high - mulpC->middle_high);
        val += abs(middle_low - mulpC->middle_low);
        val += abs(ring_high - mulpC->ring_high);
        val += abs(ring_low - mulpC->ring_low);
        val += abs(pinky_high - mulpC->pinky_high);
        val += abs(pinky_low - mulpC->pinky_low);
        return val;
    }
};
#endif