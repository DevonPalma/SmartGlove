#ifndef _MULTIPLEXER_COLLECTOR_H_
#define _MULTIPLEXER_COLLECTOR_H_

#include "Multiplexer.h"
#include "PinData.h"
#include <math.h>

struct MultiplexerCollection {
    float thumb;
    float pointer_high;
    float pointer_low;
    float middle_high;
    float middle_low;
    float ring_high;
    float ring_low;
    float pinky_high;
    float pinky_low;

    MultiplexerCollection(Multiplexer *mulp, bool scaledToOne = true) {
        thumb = mulp->read(M_THUMB);
        pointer_high = mulp->read(M_POINTER_HIGH);
        pointer_low = mulp->read(M_POINTER_LOW);
        middle_high = mulp->read(M_MIDDLE_HIGH);
        middle_low = mulp->read(M_MIDDLE_LOW);
        ring_high = mulp->read(M_RING_HIGH);
        ring_low = mulp->read(M_RING_LOW);
        pinky_high = mulp->read(M_PINKY_HIGH);
        pinky_low = mulp->read(M_PINKY_LOW);

        if (scaledToOne) {
            thumb /= 4096;
            pointer_high /= 4096;
            pointer_low /= 4096;
            middle_high /= 4096;
            middle_low /= 4096;
            ring_high /= 4096;
            ring_low /= 4096;
            pinky_high /= 4096;
            pinky_low /= 4096;
        }
    }
};
#endif