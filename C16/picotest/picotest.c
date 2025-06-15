#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

int main()
{
    stdio_init_all();
    adc_init();
    adc_select_input(3);
    uint16_t result = adc_read();
    const float conversion_factor = result*3.3f / (1 << 12);
    if (result < 0xFF) {
        printf("Pico W\n");
    }else{
        printf("Pico\n");
    };
}
