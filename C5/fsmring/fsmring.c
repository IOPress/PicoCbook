#include <stdio.h>
#include "pico/stdlib.h"

int main()
{
    stdio_init_all();
    gpio_set_function(22, GPIO_FUNC_SIO);
    gpio_set_dir(22, false);
    gpio_set_function(21, GPIO_FUNC_SIO);
    gpio_set_dir(21, true);
    gpio_set_function(20, GPIO_FUNC_SIO);
    gpio_set_dir(20, true);
    gpio_set_function(19, GPIO_FUNC_SIO);
    gpio_set_dir(19, true);

    gpio_put(19, 1);
    gpio_put(20, 0);
    gpio_put(21, 0);


    uint64_t t, tpush,twait;
    int s = 0;
    int buttonState = gpio_get(22);
    int edge;
    int buttonNow;

    while (true)
    {
        t = time_us_64();
        buttonNow = gpio_get(22);
        edge = buttonState - buttonNow;
        buttonState = buttonNow;
        switch (s){
        case 0:
            if (edge==1){
                s = 1;
                gpio_put(19, 0);
                gpio_put(20, 1);
                gpio_put(21, 0);
            }
            break;
        case 1:
            if (edge==1){
                s = 2;
                gpio_put(19, 0);
                gpio_put(20, 0);
                gpio_put(21, 1);
            }
            break;
        case 2:
            if (edge==1){
                s = 0;
                gpio_put(19, 1);
                gpio_put(20, 0);
                gpio_put(21, 0);
            }
            break;

        default:
            s = 0;
        }
        sleep_until((absolute_time_t){t + 1000});
    }
}
