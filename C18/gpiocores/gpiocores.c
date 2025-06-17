#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"

void task0(void)
{
    for (;;)
    {
       gpio_put(2, 0);
    }
}
void task1(void)
{
    for (;;)
    {
       gpio_put(2, 1);
    }
}

int main()
{
    stdio_init_all();
    gpio_init(2);
    gpio_set_dir(2, true);
    sleep_ms(1);
    multicore_reset_core1();
    multicore_launch_core1(task1);
    task0();
}

