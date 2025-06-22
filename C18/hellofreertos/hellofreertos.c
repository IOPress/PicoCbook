#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include <FreeRTOS.h>
#include <task.h>

void task(void *arg){
    printf("Hello FreeRTOS World \n");
}

int main()
{
    stdio_init_all();
    xTaskCreate(task, "task", 2048,NULL, 1, NULL);
    vTaskStartScheduler();
}
