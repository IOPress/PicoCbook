#include <stdio.h>
#include "pico/stdlib.h"

int main()
{
    stdio_init_all();
    gpio_set_function(22, GPIO_FUNC_SIO);
    gpio_set_dir(22, false);
    gpio_pull_up(22);

    printf("Press Button\n");
    sleep_ms(20000);
    if (!gpio_get(22))
    {
        printf("Button Pressed\n");
    }
    else
    {
        printf("Button Not Pressed\n");
    }
}
