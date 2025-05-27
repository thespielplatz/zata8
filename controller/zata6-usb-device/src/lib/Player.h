#ifndef PLAYER_H
#define PLAYER_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <BleKeyboard.h>
#include "DebounceButton.h"

struct Player {
    DebounceButton leftButton;
    DebounceButton rightButton;
    uint16_t pixelIndex;
    uint8_t r, g, b;   // player color
    char leftKey;
    char rightKey;

    Player(uint8_t leftPin, uint8_t rightPin, uint16_t pixel, uint8_t red, uint8_t green, uint8_t blue, char lKey, char rKey)
        : leftButton(leftPin), rightButton(rightPin),
          pixelIndex(pixel), r(red), g(green), b(blue),
          leftKey(lKey), rightKey(rKey) {}
};

#endif  // PLAYER_H
