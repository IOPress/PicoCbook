#include "pico/stdlib.h"
int main()
{
    gpio_set_function(22, GPIO_FUNC_SIO);
    gpio_set_dir(22, true);
    gpio_set_function(21, GPIO_FUNC_SIO);
    gpio_set_dir(21, true);

    uint32_t mask = (1 << 22) | (1 << 21);
    uint32_t value1 = 1 << 21;
    uint32_t value2 = 1 << 22;
    while (true)
    {
        gpio_put_masked(mask, value1);
        gpio_put_masked(mask, value2);
    }
}
