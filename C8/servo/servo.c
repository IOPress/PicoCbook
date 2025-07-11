#include "pico/stdlib.h"
#include "hardware/pwm.h"

typedef struct
{
    uint gpio;
    uint slice;
    uint chan;
    uint speed;
    uint resolution;
    bool on;
    bool invert;
} Servo;

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

void pwm_set_dutyH(uint slice_num, uint chan, int d)
{
    pwm_set_chan_level(slice_num, chan, 
                    pwm_get_wrap(slice_num) * d / 10000);
}




void ServoInit(Servo *s, uint gpio, bool invert)
{
    gpio_set_function(gpio, GPIO_FUNC_PWM);
    s->gpio = gpio;
    s->slice = pwm_gpio_to_slice_num(gpio);
    s->chan = pwm_gpio_to_channel(gpio);

    pwm_set_enabled(s->slice, false);
    s->on = false;
    s->speed = 0;
    s->resolution = pwm_set_freq_duty(s->slice, s->chan, 50, 0);
    pwm_set_dutyH(s->slice, s->chan, 250);
    if (s->chan)
    {
        pwm_set_output_polarity(s->slice, false, invert);
    }
    else
    {
        pwm_set_output_polarity(s->slice, invert, false);
    }
    s->invert = invert;
}



void ServoOn(Servo *s)
{
    pwm_set_enabled(s->slice, true);
    s->on = true;
}

void ServoOff(Servo *s)
{
    pwm_set_enabled(s->slice, false);
    s->on = false;
}
void ServoPosition(Servo *s, uint p)
{
    pwm_set_dutyH(s->slice, s->chan, p * 10 + 250);
}

int main()
{
    Servo s1;
    ServoInit(&s1, 22, false);
    ServoOn(&s1);
    while (true)
    {
        ServoPosition(&s1, 0);
        sleep_ms(500);
        ServoPosition(&s1, 100);
        sleep_ms(500);
    }
    return 0;
}