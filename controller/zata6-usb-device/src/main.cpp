#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "lib/DebounceButton.h"

#define PIN_WS2818 18
#define NUM_OF_PLAYERS 1
#define LOW_BRIGHTNESS 20
#define HIGH_BRIGHTNESS 50 

DebounceButton button1(23);
DebounceButton button2(22);
Adafruit_NeoPixel pixels(NUM_OF_PLAYERS, PIN_WS2818, NEO_RGB + NEO_KHZ800);

void setup() {
    Serial.begin(115200);
    button1.begin();
    button2.begin();
    pixels.begin();
    Serial.println("Setup complete. Waiting for button presses...");
    pixels.clear();
    pixels.setPixelColor(0, pixels.Color(LOW_BRIGHTNESS, 0, 0));

    button1.onPress([]() {
        Serial.println("Button 1 (GPIO 23) pressed!");
        pixels.setPixelColor(0, pixels.Color(HIGH_BRIGHTNESS, 0, 0));
    });

    button1.onRelease([]() {
        Serial.println("Button 1 (GPIO 23) released!");
        pixels.setPixelColor(0, pixels.Color(LOW_BRIGHTNESS, 0, 0));
    });

    button2.onPress([]() {
        Serial.println("Button 2 (GPIO 22) pressed!");
        pixels.setPixelColor(0, pixels.Color(HIGH_BRIGHTNESS, 0, 0));
    });

    button2.onRelease([]() {
        Serial.println("Button 2 (GPIO 22) released!");
        pixels.setPixelColor(0, pixels.Color(LOW_BRIGHTNESS, 0, 0));
    });
}

void loop() {
    button1.update();
    button2.update();
    pixels.show();
    delay(10);  // light loop delay
}
