#ifndef _MULTIPLEXER_H_
#define _MULTIPLEXER_H_

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
    }

    void begin() {
        pinMode(en, OUTPUT);
        pinMode(s0, OUTPUT);
        pinMode(s1, OUTPUT);
        pinMode(s2, OUTPUT);
        pinMode(s3, OUTPUT);
        pinMode(sig, INPUT);

        set(index);
        disable();
    }

    void enable() {
        digitalWrite(en, LOW);
    }

    void disable() {
        digitalWrite(en, HIGH);
    }

    void set(byte index) {
        if (index < 0 || index > 15) {
            Serial.printf("Multiplexer.set() > value must be in the range of 0...15, value = %d\n", index);
            return;
        }

        digitalWrite(s0, (index & 0x1) >> 0);
        digitalWrite(s1, (index & 0x2) >> 1);
        digitalWrite(s2, (index & 0x4) >> 2);
        digitalWrite(s3, (index & 0x8) >> 3);
    }

    int read(byte index) {
        set(index);
        return read();
    }

    int read() {
        enable();
        int val = analogRead(sig);
        disable();
        
        return val;
    }
};

#endif