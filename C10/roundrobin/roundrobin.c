#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

int main()
{
    stdio_init_all();

    adc_init();
    adc_gpio_init(26);
    adc_gpio_init(27);
    adc_set_round_robin(0x03);
    adc_fifo_setup(true,false,0,false,false);
    adc_run(true);
    const float conversion_factor = 3.3f / (1 << 12);
    while (1)
    {
        uint16_t result = adc_fifo_get();
        printf("Raw value 0: 0x%03x, voltage: %f V\n",
                          result, result * conversion_factor);
        int level = adc_fifo_get_level();
        printf("level: %d \n", level);
    }
}
