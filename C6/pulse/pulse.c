#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/structs/iobank0.h"

uint32_t gpio_get_events(uint gpio)
{
    int32_t mask = 0xF << 4 * (gpio % 8);
    return (iobank0_hw->intr[gpio / 8] & mask) >> 4 * (gpio % 8);
}

void gpio_clear_events(uint gpio, uint32_t events)
{
    gpio_acknowledge_irq(gpio, events);
}

int main()
{
    uint64_t t;
    stdio_init_all();
    gpio_set_function(22, GPIO_FUNC_SIO);
    gpio_set_dir(22, false);
    gpio_pull_up(22);

    while (true)
    {
        gpio_clear_events(22, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL);
        while (!(gpio_get_events(22) & GPIO_IRQ_EDGE_RISE))
        {
        };
        t = time_us_64();
        gpio_clear_events(22, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL);
        while (!(gpio_get_events(22) & GPIO_IRQ_EDGE_FALL))
        {
        };
        t = (uint64_t)(time_us_64() - t);
        printf("%llu\n", t);
        sleep_ms(1000);
    }
}
