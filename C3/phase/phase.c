#include "pico/stdlib.h"
int main()
{
    gpio_set_function(22, GPIO_FUNC_SIO);
    gpio_set_dir(22, true);
    gpio_set_function(21, GPIO_FUNC_SIO);
    gpio_set_dir(21, true);
    while (true)
    {
        gpio_put(22, 0);
        gpio_put(21, 1);
        gpio_put(22, 1);
        gpio_put(21, 0);
    }
}
