#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

static void delay(int ms) { vTaskDelay(pdMS_TO_TICKS(ms)); }

const gpio_num_t BUTTON1_GPIO = GPIO_NUM_23;
const gpio_num_t BUTTON2_GPIO = GPIO_NUM_22;

const int LED_COUNT = 1;
const int DATA_PIN = 18;
const int CHANNEL = 0;

void setup() {}

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

    while (1) {
        int current_state_1 = gpio_get_level(BUTTON1_GPIO);
        int current_state_2 = gpio_get_level(BUTTON2_GPIO);

        if (current_state_1 != last_state_1) {
            if (current_state_1 == 0) {
                printf("1 down\n");
            } else {
                printf("1 up\n");
            }
            last_state_1 = current_state_1;
        }

        if (current_state_2 != last_state_2) {
            if (current_state_2 == 0) {
                printf("q down\n");
            } else {
                printf("q up\n");
            }
            last_state_2 = current_state_2;
        }
        // Small delay to prevent 100% CPU usage
        delay(10);
    }
}
