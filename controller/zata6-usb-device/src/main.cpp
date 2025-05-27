#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <BleKeyboard.h>

#include "lib/Player.h"

#define PIN_WS2818        18
#define NUM_OF_PLAYERS    2
#define LOW_BRIGHTNESS    20
#define HIGH_BRIGHTNESS   50

Adafruit_NeoPixel pixels(NUM_OF_PLAYERS, PIN_WS2818, NEO_RGB + NEO_KHZ800);
BleKeyboard bleKeyboard("Zata8 Multipad");

// Define players (expand as needed)
Player players[NUM_OF_PLAYERS] = {
    Player(23, 22, 0, LOW_BRIGHTNESS, 0, 0, '1', 'q'),     // Player 1 → Red, keys 1/q
    Player(19, 21, 1, 0, LOW_BRIGHTNESS, 0, '2', 'w')      // Player 2 → Green, keys 2/w
};

void setup() {
    Serial.begin(115200);
    bleKeyboard.begin();
    pixels.begin();
    pixels.clear();

    for (int i = 0; i < NUM_OF_PLAYERS; i++) {
        players[i].leftButton.begin();
        players[i].rightButton.begin();

        // Initialize LEDs to low brightness player color
        pixels.setPixelColor(players[i].pixelIndex, pixels.Color(players[i].r, players[i].g, players[i].b));

        // Capture player index for use in lambdas
        int index = i;

        // Left button callbacks
        players[i].leftButton.onPress([index]() {
            Serial.printf("Player %d LEFT pressed!\n", index + 1);
            pixels.setPixelColor(players[index].pixelIndex, pixels.Color(HIGH_BRIGHTNESS, players[index].g, players[index].b));
            if (bleKeyboard.isConnected()) bleKeyboard.press(players[index].leftKey);
        });
        players[i].leftButton.onRelease([index]() {
            Serial.printf("Player %d LEFT released!\n", index + 1);
            pixels.setPixelColor(players[index].pixelIndex, pixels.Color(LOW_BRIGHTNESS, players[index].g, players[index].b));
            if (bleKeyboard.isConnected()) bleKeyboard.release(players[index].leftKey);
        });

        // Right button callbacks
        players[i].rightButton.onPress([index]() {
            Serial.printf("Player %d RIGHT pressed!\n", index + 1);
            pixels.setPixelColor(players[index].pixelIndex, pixels.Color(HIGH_BRIGHTNESS, players[index].g, players[index].b));
            if (bleKeyboard.isConnected()) bleKeyboard.press(players[index].rightKey);
        });
        players[i].rightButton.onRelease([index]() {
            Serial.printf("Player %d RIGHT released!\n", index + 1);
            pixels.setPixelColor(players[index].pixelIndex, pixels.Color(LOW_BRIGHTNESS, players[index].g, players[index].b));
            if (bleKeyboard.isConnected()) bleKeyboard.release(players[index].rightKey);
        });
    }

    pixels.show();
    Serial.println("Setup complete. Waiting for button presses...");
}

void loop() {
    for (int i = 0; i < NUM_OF_PLAYERS; i++) {
        players[i].leftButton.update();
        players[i].rightButton.update();
    }
    pixels.show();
    delay(10);
}
