#include "pico/stdlib.h"
int main()
{
    gpio_set_function(21, GPIO_FUNC_SIO);
    gpio_set_dir(21,false);
    gpio_pull_up(21);

    gpio_set_function(22, GPIO_FUNC_SIO);
    gpio_set_dir(22, true);

    while (true)
    {
        if (gpio_get(21))
        {
            gpio_put(22, 0);
        }
        else
        {
            gpio_put(22, 1);
        }
    }
}
