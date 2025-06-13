#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include <stdio.h>

int main()
{
 stdio_init_all();
 gpio_set_function(20, GPIO_FUNC_PWM);
 gpio_set_function(21, GPIO_FUNC_PWM);
 uint slice_num = pwm_gpio_to_slice_num(20);

    uint chanA = pwm_gpio_to_channel(20);
    uint chanB = pwm_gpio_to_channel(21);
    
    pwm_set_clkdiv_int_frac(slice_num, 23, 0);
    int maxcount=150000*10/23;

    pwm_set_wrap(slice_num, 65535);
    pwm_set_chan_level(slice_num, chanA, 100);
    pwm_set_clkdiv_mode(slice_num, PWM_DIV_B_HIGH);

 while (true)
 {
 	pwm_set_enabled(slice_num, true);
 	sleep_ms(10);
 	pwm_set_enabled(slice_num, false);
 	uint16_t count =pwm_get_counter(slice_num);
 	pwm_set_counter(slice_num, 0);
 	printf("count= %u  duty cycle=%d %%\n", 
                count, (int)count*100/maxcount);
       sleep_ms(1000);
    }
}