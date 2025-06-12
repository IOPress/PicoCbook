#include <stdio.h>
#include "pico/stdlib.h"
int main()
{
    stdio_init_all();
    gpio_set_function(22, GPIO_FUNC_SIO);
    gpio_set_dir(22, false);
    uint64_t t;

    while (true)
    {
        while (gpio_get(22) == 1)
        {
        };
        while (gpio_get(22) == 0)
        {
        };
        t = time_us_64();
        while (gpio_get(22) == 1)
        {
        };
        t = (uint64_t)(time_us_64() - t);
        printf("%llu\n", t);
        sleep_ms(1000);
    }
}