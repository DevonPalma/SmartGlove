#ifndef _MULTIPLEXER_COLLECTOR_H_
#define _MULTIPLEXER_COLLECTOR_H_

#include "Multiplexer.h"
#include "PinData.h"

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

    MultiplexerCollection(Multiplexer *mulp) {
        thumb         = mulp->read(M_THUMB);
        pointer_high  = mulp->read(M_POINTER_HIGH);
        pointer_low   = mulp->read(M_POINTER_LOW);
        middle_high   = mulp->read(M_MIDDLE_HIGH);
        middle_low    = mulp->read(M_MIDDLE_LOW);
        ring_high     = mulp->read(M_RING_HIGH);
        ring_low      = mulp->read(M_RING_LOW);
        pinky_high    = mulp->read(M_PINKY_HIGH);
        pinky_low     = mulp->read(M_PINKY_LOW);
    }
};
#endif