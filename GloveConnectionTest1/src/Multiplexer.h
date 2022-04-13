#ifndef _MULTIPLEXER_H_
#define _MULITPLEXER_H_

class Multiplexer {
    byte en;
    byte s0, s1, s2, s3;
    byte sig;
    byte index;

public:

    Multiplexer(byte enablePin, byte select0Pin, byte select1Pin, byte select2Pin, byte select3Pin, byte signalPin) {
        en = enablePin;
        s0 = select0Pin;
        s1 = select1Pin;
        s2 = select2Pin;
        s3 = select3Pin;
        sig = signalPin;

        pinMode(en, OUTPUT);
        pinMode(s0, OUTPUT);
        pinMode(s1, OUTPUT);
        pinMode(s2, OUTPUT);
        pinMode(s3, OUTPUT);
        pinMode(sig, INPUT);
    }

    void set(byte index) {

    }

    void read(byte index) {

    }

    int  read() {

    }
}

#endif