#include "pico/stdlib.h"
#include "hardware/pwm.h"

int main()
{
    gpio_set_function(22, GPIO_FUNC_PWM);
    int slice = pwm_gpio_to_slice_num(22);
    int channel = pwm_gpio_to_channel(22);
    pwm_set_phase_correct(slice, false);
    pwm_set_clkdiv_int_frac(slice, 45, 13);
    pwm_set_wrap(slice, 65483);
    pwm_set_chan_level(slice, PWM_CHAN_A, 65483/2);
    pwm_set_enabled(slice, true);
}
