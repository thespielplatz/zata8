#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include <SmartLeds.h>

static void delay(int ms) { vTaskDelay(pdMS_TO_TICKS(ms)); }

const gpio_num_t BUTTON1_GPIO = GPIO_NUM_23;
const gpio_num_t BUTTON2_GPIO = GPIO_NUM_22;

const int LED_COUNT = 1;
const int DATA_PIN = 18;
const int CHANNEL = 0;

const uint8_t DEFAULT_BRIGHTNESS = 10; // Default brightness value
const uint8_t ACTIVE_BRIGHTNESS = 20; // Brightness when button is pressed

SmartLed leds(LED_WS2812B, LED_COUNT, DATA_PIN, CHANNEL, DoubleBuffer);

void setup() {}

uint8_t rValue = 0;

extern "C" void app_main(void) {
    // Configure both GPIOs as input with pull-up
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << BUTTON1_GPIO) | (1ULL << BUTTON2_GPIO),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);

    printf("Monitoring GPIO %d (1) and GPIO %d (q)\n", BUTTON1_GPIO, BUTTON2_GPIO);

    int last_state_1 = gpio_get_level(BUTTON1_GPIO);
    int last_state_2 = gpio_get_level(BUTTON2_GPIO);

    rValue = DEFAULT_BRIGHTNESS;
    while (1) {
        int current_state_1 = gpio_get_level(BUTTON1_GPIO);
        int current_state_2 = gpio_get_level(BUTTON2_GPIO);

        if (current_state_1 != last_state_1) {
            if (current_state_1 == 0) {
                printf("1 down\n");
                rValue = ACTIVE_BRIGHTNESS;
            } else {
                printf("1 up\n");
                rValue = DEFAULT_BRIGHTNESS;
            }
            last_state_1 = current_state_1;
        }

        if (current_state_2 != last_state_2) {
            if (current_state_2 == 0) {
                printf("q down\n");
                rValue = ACTIVE_BRIGHTNESS;
            } else {
                printf("q up\n");
                rValue = DEFAULT_BRIGHTNESS;
            }
            last_state_2 = current_state_2;
        }

        leds[0] = Rgb { rValue, 0, 0 };
        leds.show();

        // Small delay to prevent 100% CPU usage
        vTaskDelay(5);
    }
}
