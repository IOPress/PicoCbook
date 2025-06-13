#include <stdio.h>
#include "pico/stdlib.h"

typedef struct
{
    uint gpio;
    uint speed;
    bool forward;
    uint32_t gpiomask;
    uint phase;
} StepperBi;

uint32_t stepTable[8] = 
            (uint32_t[8]){0x8, 0xC, 0x4, 0x6, 0x2, 0x3, 0x1, 0x9};
/*
    {1, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 1},
    {0, 0, 0, 1},
    {1, 0, 0, 1}
*/
void StepperBiInit(StepperBi *s, uint gpio)
{
    s->gpio = gpio;
    for (int i = 0; i < 4; i++){
        gpio_set_function((s->gpio) + i, GPIO_FUNC_SIO);
        gpio_set_dir((s->gpio) + i, true);
    }
    s->gpiomask = 0x0F << gpio;
    volatile uint32_t mask = stepTable[0] << gpio;
    gpio_put_masked(s->gpiomask, mask);
    s->phase = 0;
    s->speed = 0;
    s->forward = true;
}

void setPhase(StepperBi *s, uint p)
{
    uint32_t mask = stepTable[p] << (s->gpio);
    gpio_put_masked(s->gpiomask, mask);
}
void stepForward(StepperBi *s)
{
    s->phase = (s->phase + 1) % 8;
    setPhase(s, s->phase);
}
void stepReverse(StepperBi *s)
{
    s->phase = (s->phase - 1) % 8;
    setPhase(s, s->phase);
}
void rotate(StepperBi *s, bool dir, int speed)
{
    s->forward = dir;
    s->speed = speed;
}
int main()
{
    stdio_init_all();
    StepperBi s1;
    StepperBiInit(&s1, 18);
    while (true)
    {
        stepForward(&s1);
        sleep_ms(1);
    }
    return 0;
}
