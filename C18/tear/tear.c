#pragma GCC optimize("O0")
#include <stdio.h>
#include "pico/stdlib.h"
#include <FreeRTOS.h>
#include <task.h>

volatile uint64_t flag = 0;

void task0(void *arg)
{
    for (;;)
    {
        flag = 0x0;
        flag = 0xFFFFFFFFFFFFFFFF;
        gpio_put(2, 0);
    }
}
void task1(void *arg)
{
    for (;;)
    {
        if (flag != 0xFFFFFFFFFFFFFFFF && flag != 0x0)
        {
            gpio_put(2, 1);

        }
    }
}

int main()
{
    stdio_init_all();
    gpio_init(2);
    gpio_set_dir(2, GPIO_OUT);
    sleep_ms(10);

    UBaseType_t uxCoreAffinityMask;

    TaskHandle_t th0;
    xTaskCreate(task0, "task0", 2048, NULL, 1, &th0);
    uxCoreAffinityMask = 1 << 0;
    vTaskCoreAffinitySet(th0, uxCoreAffinityMask);

    TaskHandle_t th1;
    xTaskCreate(task1, "task1", 2048, NULL, 1, &th1);
    uxCoreAffinityMask = 1 << 1;
    vTaskCoreAffinitySet(th1, uxCoreAffinityMask);

    vTaskStartScheduler();
}
