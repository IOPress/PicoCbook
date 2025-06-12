#include <stdio.h>
#include "pico/stdlib.h"


uint64_t t[20];
int count = 0;

void MyIRQHandler(uint gpio, uint32_t events)
{
    t[count++] = time_us_64();
    if (count > 19)
    {
        for (int i = 1; i < 19; i++)
        {
            printf("%llu \n\r", t[i] - t[i - 1]);
            fflush(stdout);
        }
        count = 0;
    }
}

int main()
{
    stdio_init_all();
    gpio_set_function(22, GPIO_FUNC_SIO);
    gpio_set_dir(22, false);
    gpio_pull_up(22);

    gpio_set_irq_enabled_with_callback(22, GPIO_IRQ_EDGE_RISE |
                       GPIO_IRQ_EDGE_FALL, true, &MyIRQHandler);
    while (1){};
    return 0;
}

