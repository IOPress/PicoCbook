#include <stdio.h>
#include "pico/stdlib.h"
int main()
{
    stdio_init_all();
    gpio_set_function(22, GPIO_FUNC_SIO);
    gpio_set_dir(22, false);
    uint64_t t;
    uint64_t tpush, twait;
    int s = 0,i;    
    int count = 0;
    while (true){
        i = gpio_get(22);
        t = time_us_64();
        switch (s){
        case 0: //button not pushed
            if (i){
                s = 1;
                tpush = t;
            }
            break;
        case 1: //Button pushed
            if (!i){
                s = 0;
                if ((t - tpush) > 2000000){
                    printf("Button held \n\r");
                }else{
                    printf("Button pushed \n\r");
                }
                fflush(stdout);
            }
            break;
        default:
            s = 0;
        }
        sleep_until((absolute_time_t){t + 1000});
    }
}