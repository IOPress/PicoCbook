#include "pico/stdlib.h"
#include "hardware/pwm.h"

uint32_t pwm_set_freq_duty(uint slice_num, uint chan,
                           uint32_t f, int d)
{
    uint32_t clock = 150000000; // set to for Pico 1 125000000;
    uint32_t divider16 = clock / f / 4096 +
                         (clock % (f * 4096) != 0);
    if (divider16 / 16 == 0)
        divider16 = 16;
    uint32_t wrap = clock * 16 / divider16 / f - 1;
    pwm_set_clkdiv_int_frac(slice_num, divider16 / 16,
                            divider16 & 0xF);
    pwm_set_wrap(slice_num, wrap);
    pwm_set_chan_level(slice_num, chan, wrap * d / 100);
    return wrap;
}
uint32_t pwm_get_wrap(uint slice_num)
{
    return pwm_hw->slice[slice_num].top;
}
void pwm_set_duty(uint slice_num, uint chan, int d)
{
    pwm_set_chan_level(slice_num, chan, pwm_get_wrap(slice_num) * d / 100);
}

int main()
{
    gpio_set_function(20, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(20);
    uint chan20 = pwm_gpio_to_channel(20);
    uint wrap = pwm_set_freq_duty(slice_num, chan20, 50, 50);
    pwm_set_enabled(slice_num, true);
    while (true)
    {
        pwm_set_duty(slice_num, chan20, 25);
        while (pwm_get_counter(slice_num))
        {
        };
        pwm_set_duty(slice_num, chan20, 50);
        while (pwm_get_counter(slice_num))
        {
        };
    }
    return 0;
}
