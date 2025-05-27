#ifndef DEBOUNCEBUTTON_H
#define DEBOUNCEBUTTON_H

#include <Arduino.h>
#include <functional>

class DebounceButton {
private:
    uint8_t pin;
    unsigned long debounceDelay;
    unsigned long lastDebounceTime;
    bool lastState;
    bool debouncedState;

    std::function<void()> onPressCallback;
    std::function<void()> onReleaseCallback;

public:
    DebounceButton(uint8_t buttonPin, unsigned long debounceMs = 50)
        : pin(buttonPin),
          debounceDelay(debounceMs),
          lastDebounceTime(0),
          lastState(HIGH),
          debouncedState(HIGH),
          onPressCallback(nullptr),
          onReleaseCallback(nullptr) {}

    void begin() {
        pinMode(pin, INPUT_PULLUP);
    }

    void onPress(std::function<void()> callback) {
        onPressCallback = callback;
    }

    void onRelease(std::function<void()> callback) {
        onReleaseCallback = callback;
    }

    void update() {
        bool reading = digitalRead(pin);
        if (reading != lastState) {
            lastDebounceTime = millis();
            lastState = reading;
        }

        if ((millis() - lastDebounceTime) > debounceDelay) {
            if (reading != debouncedState) {
                debouncedState = reading;

                if (debouncedState == LOW && onPressCallback) {
                    onPressCallback();
                } else if (debouncedState == HIGH && onReleaseCallback) {
                    onReleaseCallback();
                }
            }
        }
    }

    bool isPressed() {
        return debouncedState == LOW;
    }

    bool isReleased() {
        return debouncedState == HIGH;
    }
};

#endif
