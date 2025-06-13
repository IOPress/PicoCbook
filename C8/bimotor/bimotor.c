#include "pico/stdlib.h"
#include "hardware/pwm.h"
typedef struct
{
    uint gpioForward;
    uint gpioBackward;
    uint slice;
    uint Fchan;
    uint Bchan;
    bool forward;
    uint speed;
    uint freq;
    uint resolution;
    bool on;
} BiMotor;

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
    pwm_set_chan_level(slice_num, chan, 
                        pwm_get_wrap(slice_num) * d / 100);
}

void BiMotorInit(BiMotor *m, uint gpioForward,
                             uint gpioBackward, uint freq)
{
    gpio_set_function(gpioForward, GPIO_FUNC_PWM);
    m->gpioForward = gpioForward;
    m->slice = pwm_gpio_to_slice_num(gpioForward);
    m->Fchan = pwm_gpio_to_channel(gpioForward);

    gpio_set_function(gpioBackward, GPIO_FUNC_PWM);
    m->gpioBackward = gpioBackward;
    m->Bchan = pwm_gpio_to_channel(gpioBackward);

    m->freq = freq;
    m->speed = 0;
    m->forward = true;
    m->resolution = pwm_set_freq_duty(m->slice, m->Fchan,
                                               m->freq, 0);
    pwm_set_duty(m->slice, m->Bchan, 0);
    m->on = false;
}

void BiMotorspeed(BiMotor *m, int s, bool forward)
{
    if (forward)
    {
        pwm_set_duty(m->slice, m->Bchan, 0);
        pwm_set_duty(m->slice, m->Fchan, s);
        m->forward = true;
    }
    else
    {
        pwm_set_duty(m->slice, m->Fchan, 0);
        pwm_set_duty(m->slice, m->Bchan, s);
        m->forward = false;
    }
    m->speed = s;
}

void BiMotorOn(BiMotor *m)
{
    pwm_set_enabled(m->slice, true);
    m->on = true;
}


void BiMotorOff(BiMotor *m)
{
    pwm_set_enabled(m->slice, false);
    m->on = false;
}

int main()
{
    BiMotor mot1;
    BiMotorInit(&mot1, 20, 21, 2000);

    BiMotorOn(&mot1);
    while (true)
    {
        BiMotorspeed(&mot1, 50, true);
        sleep_ms(2000);
        BiMotorspeed(&mot1, 25, false);
        sleep_ms(2000);
    }

    return 0;
}
