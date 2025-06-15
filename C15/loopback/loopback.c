#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
int main()
{
    stdio_init_all();
    uart_init(uart1, 9600);
    gpio_set_function(4, GPIO_FUNC_UART);
    gpio_set_function(5, GPIO_FUNC_UART);
    uart_set_format(uart1, 8, 1, UART_PARITY_EVEN);
    uint8_t SendData[] = "Hello World";
    uint8_t RecData[20];
    uart_write_blocking(uart1, SendData, 11);
    uart_read_blocking(uart1, RecData, 11);
    RecData[11]=0;
    printf("%s",RecData);
}
