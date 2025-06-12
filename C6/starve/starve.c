#include <stdio.h>
#include "pico/stdlib.h"

 uint64_t t; 

void MyIRQHandler(uint gpio, uint32_t events)
{
    t = time_us_64() ;
    printf("GPIO %d %X %llu \n", gpio, events, t);
}

int main()
{
    stdio_init_all();
    gpio_set_function(22, GPIO_FUNC_SIO);
    gpio_set_dir(22, false);
    gpio_pull_up(22);

    gpio_set_irq_enabled_with_callback(22, GPIO_IRQ_EDGE_RISE |
                         GPIO_IRQ_EDGE_FALL, true, &MyIRQHandler);

    while (1)
    {
        printf("doing something very big and time consuming\n\r");
    };

    return 0;
}
