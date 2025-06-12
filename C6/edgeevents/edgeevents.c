#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/structs/iobank0.h"

uint32_t gpio_get_events(uint gpio)
{
    int32_t mask = 0xF << 4 * (gpio % 8);
    return (iobank0_hw->intr[gpio / 8] & mask) >> 4 * ( gpio % 8);
}
void gpio_clear_events(uint gpio, uint32_t events)
{
    gpio_acknowledge_irq(gpio, events);
}

int main()
{
    stdio_init_all();
    gpio_set_function(22, GPIO_FUNC_SIO);
    gpio_set_dir(22, false);
    gpio_pull_up(22);

    printf("Press Button\n");
    gpio_clear_events(22, GPIO_IRQ_EDGE_FALL);
    sleep_ms(20000);
    int32_t event=gpio_get_irq_event_mask(22);
    gpio_clear_events(22, GPIO_IRQ_EDGE_FALL);
    if (event & GPIO_IRQ_EDGE_FALL)
    {
        printf("Button Pressed\n");
    }
    else
    {
        printf("Button Not Pressed\n");
    }
}
