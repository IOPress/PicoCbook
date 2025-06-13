#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/irq.h"
#include "math.h"

uint32_t pwm_get_wrap(uint slice_num)
{
 return pwm_hw->slice[slice_num].top;
}

void pwm_set_duty(uint slice_num, uint chan, int d)
{
 pwm_set_chan_level(slice_num, chan,
                             pwm_get_wrap(slice_num)*d/100);
}
uint slice_num;
uint chan20;
uint state = 0;
uint8_t wave[256];

void MyIRQHandler()
{
 pwm_clear_irq(slice_num);
 pwm_set_duty(slice_num, chan20, wave[state]);
 state = (state + 1) % 256;
}

int main()
{
    for (int i = 0; i < 256; i++)
    {
      wave[i] = (uint8_t)((128.0 + sinf((float)i * 2.0 * 3.14159 /
                                  255.0) * 128.0) * 100.0 / 255.0);
    }

    gpio_set_function(22, GPIO_FUNC_PWM);

    slice_num = pwm_gpio_to_slice_num(22);
    uint chan22 = pwm_gpio_to_channel(22);

    pwm_clear_irq(slice_num);
    pwm_irqn_set_slice_enabled(0,slice_num, true);
    irq_set_exclusive_handler(PWM_IRQ_WRAP_0, MyIRQHandler);
    irq_set_enabled(PWM_IRQ_WRAP_0, true);

    pwm_set_clkdiv_int_frac(slice_num, 1, 0);
    pwm_set_wrap(slice_num, 255);

    pwm_set_enabled(slice_num, true);
    while (true)
    {
    }
    return 0;
}
