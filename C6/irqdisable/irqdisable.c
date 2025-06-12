#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/structs/iobank0.h"
#include "hardware/sync.h"
void gpio_set_irq_active(uint gpio, uint32_t events, bool enabled)
{
    io_bank0_irq_ctrl_hw_t *irq_ctrl_base = get_core_num() ? &iobank0_hw->proc1_irq_ctrl : &iobank0_hw->proc0_irq_ctrl;
  
    io_rw_32 *en_reg = &irq_ctrl_base->inte[gpio / 8];
    events <<= 4 * (gpio % 8);
    if (enabled)
        hw_set_bits(en_reg, events);
    else
        hw_clear_bits(en_reg, events);
}

uint64_t t;

void MyIRQHandler(uint gpio, uint32_t events)
{
    t = time_us_64();
    printf("GPIO %d %X %llu \n", gpio, events, t);
}

int main()
{
    stdio_init_all();
    gpio_set_function(22, GPIO_FUNC_SIO);
    gpio_set_dir(22, false);
    gpio_pull_up(22);

    gpio_set_irq_enabled_with_callback(22, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &MyIRQHandler);
    while (1)
    {
        gpio_set_irq_active(22, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, false);
        printf("doing something\n\r");
        gpio_set_irq_active(22, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true);
    };

    return 0;
}
