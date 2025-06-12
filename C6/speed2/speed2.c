#include <stdio.h>
#include "pico/stdlib.h"

uint64_t t[20];
int count = 0;

void MyIRQHandler()
{
    t[count++] = time_us_64();
    gpio_acknowledge_irq(22, GPIO_IRQ_EDGE_RISE | 
                                  GPIO_IRQ_EDGE_FALL);
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
    gpio_add_raw_irq_handler(22,  &MyIRQHandler);
    gpio_set_irq_enabled (22, GPIO_IRQ_EDGE_RISE |  
                              GPIO_IRQ_EDGE_FALL,true);
    irq_set_enabled(IO_IRQ_BANK0, true);

    while (1)
    {
    };
    return 0;
}
