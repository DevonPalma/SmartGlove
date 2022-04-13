#ifndef _EZ_BUTTON_H_
#define _EZ_BUTTON_H_

typedef void (*callFunction)(void);

class EZButton {
private:
    int p;
    bool lastState;
    callFunction _onPressed = nullptr;
    callFunction _onRelease = nullptr;
    

public:
    EZButton(int pin, PinMode mode = INPUT_PULLUP) {
        p = pin;
        pinMode(p, mode);
        lastState = digitalRead(p);
    }

    void onRelease(callFunction onReleaseFunc) {
        _onRelease = onReleaseFunc;
    }

    void onPressed(callFunction onPressedFunc) {
        _onPressed = onPressedFunc;
    }

    void update() {
        bool curState = digitalRead(p);
        
        if (curState && !lastState && _onRelease != nullptr) {
            _onRelease();
        }

        if (!curState && lastState && _onPressed != nullptr) {
            _onPressed();
        }

        lastState = curState;
    }
};

#endif