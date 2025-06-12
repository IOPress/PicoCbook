#include "pico/stdlib.h"
#include "hardware/pwm.h"
int main()
{
    int wrap = 14999; // 12499 for the Pico 1
    int level = 3750; // 3125 for the Pico 1
    gpio_set_function(22, GPIO_FUNC_PWM);
    int slice = pwm_gpio_to_slice_num(22);
    int channel = pwm_gpio_to_channel(22);
    pwm_set_phase_correct(slice, false);
    pwm_set_wrap(slice, wrap);
    pwm_set_chan_level(slice, PWM_CHAN_A, level);
    pwm_set_enabled(slice, true);
}
