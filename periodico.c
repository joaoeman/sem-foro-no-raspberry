#include "pico/stdlib.h"
#include "hardware/timer.h"
#include <stdio.h>
#include "hardware/gpio.h"

const uint LED_G = 11;
const uint LED_B = 12;
const uint LED_R = 13;
static int state = 1; // 0: LED_G, 1: LED_B, 2: LED_R
static int count = 1;
bool repeating_timer_callback(struct repeating_timer *t) {
    
    

    // Liga o LED correspondente ao estado atual
    if (state == 0) {
        gpio_put(LED_G, 1);
        gpio_put(LED_R, 0);
        gpio_put(LED_B, 0);
    } else if (state == 1) {
        gpio_put(LED_G, 0);
        gpio_put(LED_R, 0);
        gpio_put(LED_B, 1);
    } else if (state == 2) {
        gpio_put(LED_G, 0);
        gpio_put(LED_R, 1);
        gpio_put(LED_B, 0);
    }

    // Avança para o próximo estado
    state = (state + 1) % 3;
    count ++;
    return true;
}

int main() {
    stdio_init_all();

    gpio_init(LED_R);
    gpio_set_dir(LED_R, GPIO_OUT);

    gpio_init(LED_G);
    gpio_set_dir(LED_G, GPIO_OUT);

    gpio_init(LED_B);
    gpio_set_dir(LED_B, GPIO_OUT);

    // Desliga todos os LEDs
    gpio_put(LED_G, 0);
    gpio_put(LED_B, 0);
    gpio_put(LED_R, 0);

    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    while (true) {
        if(count == 1){
          gpio_put(LED_G, 1);
        }
        printf("go\n");
        sleep_ms(1000);

    }

    return 0;
}
