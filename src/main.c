#include <stdio.h>
#include "pico/stdlib.h"

// Placeholder: blinks the on-board LED and prints over USB serial.
// Replace with the real desk logic once the architecture is decided.
int main(void) {
    stdio_init_all();
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    while (true) {
        gpio_put(PICO_DEFAULT_LED_PIN, 1);
        sleep_ms(500);
        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        sleep_ms(500);
        printf("alive\n");
    }
}
