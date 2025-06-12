#include "pico/stdlib.h"
int main()
{
    gpio_set_function(21, GPIO_FUNC_SIO);
    gpio_set_dir(21, false);
    gpio_pull_down(21);

    gpio_set_function(22, GPIO_FUNC_SIO);
    gpio_set_dir(22, true);
    gpio_put(22, 0);

    uint64_t t;

    while (true)
    {
        while (gpio_get(21) == 0){};
        t = time_us_64();
        sleep_ms(1);
        while (gpio_get(21) == 1){};
        t = (uint64_t)(time_us_64() - t);
        if (t < 2000*1000)
        {
            gpio_put(22, 1);
            sleep_ms(1000);
            gpio_put(22, 0);
        }
        else
        {
            for (int i = 0; i < 10; i++)
            {
                gpio_put(22, 1);
                sleep_ms(100);
                gpio_put(22, 0);
                sleep_ms(100);
            }
        }
    }
}
