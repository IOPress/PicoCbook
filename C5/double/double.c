#include "pico/stdlib.h"
int main()
{
    gpio_set_function(21, GPIO_FUNC_SIO);
    gpio_set_dir(21, false);
    gpio_pull_up(21);

    gpio_set_function(22, GPIO_FUNC_SIO);
    gpio_set_dir(22, true);
    gpio_put(22, 0);
    while (true)
    {
        while (gpio_get(21) == 1){};
        while (gpio_get(21) == 0){};
        gpio_put(22, 1);
        sleep_ms(1000);
        gpio_put(22, 0);
    }
}
