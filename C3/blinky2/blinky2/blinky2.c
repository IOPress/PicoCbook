#include "pico/stdlib.h"
int main()
{
    gpio_init(22);
    gpio_set_dir(22, true);
    while (true)
    {
        gpio_put(22, 1);
        sleep_ms(1000);
        gpio_put(22, 0);
        sleep_ms(1000);
    }
}
