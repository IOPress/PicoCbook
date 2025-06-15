#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "blink.pio.h"

int main()
{

    uint offset = pio_add_program(pio0, &blink_program);

    uint sm = pio_claim_unused_sm(pio0, true);
    pio_sm_config c = blink_program_get_default_config(offset);
    
    sm_config_set_in_pins(&c, 2);
    pio_gpio_init(pio0, 2);
   
    pio_sm_set_consecutive_pindirs(pio0, sm, 2, 1, false);
    sm_config_set_clkdiv_int_frac(&c, 255, 0);
    
    pio_sm_init(pio0, sm, offset, &c);
    pio_sm_set_enabled(pio0, sm, true);

    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);
   
 while (true)
    {
        uint32_t flag = pio_sm_get_blocking(pio0, sm);
        if (flag == 0)
        {
            gpio_put(25, 0);
        }
        else
        {
            gpio_put(25, 1);
        }
    }

    return 0;
}