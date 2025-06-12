#include <stdio.h>
#include "pico/stdlib.h"

int main()
{
    stdio_init_all();
    gpio_set_function(22, GPIO_FUNC_SIO);
    gpio_set_dir(22, false);
    uint64_t t;
    int s = 0;
    int i;
    int count=0;
    while (true)
    {
        i = gpio_get(22);
        t = time_us_64() + 100;
        switch (s){
        case 0: //button not pushed
            if (i){
                s = 1;
                count++;
                printf("Button Push %d \n\r",count);
            }
            break;
        case 1: //Button pushed
            if (!i){
                s = 0;
            }
            break;
        default:
            s = 0;
        }
        sleep_until((absolute_time_t){t});
    }
}