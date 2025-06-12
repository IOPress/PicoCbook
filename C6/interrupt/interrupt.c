#include <stdio.h>
#include "pico/stdlib.h"

static uint64_t t=0;
void MyIRQHandler(uint gpio, uint32_t events)
{
    printf("GPIO %d %X %llu \n", gpio, events, time_us_64() - t);
    t = time_us_64();
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
