#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"

int main()
{
    stdio_init_all();
    spi_init(spi0, 500 * 1000);
    gpio_set_function(4, GPIO_FUNC_SPI);
    gpio_set_function(6, GPIO_FUNC_SPI);
    gpio_set_function(7, GPIO_FUNC_SPI);
    spi_set_format(spi0, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);
    uint16_t wBuff[1] = {0xAA};
    uint16_t rBuff[1];
    int n = spi_write16_read16_blocking(spi0, wBuff, rBuff, 1);
    spi_deinit(spi0);
    printf(" %X %X %d ", wBuff[0], rBuff[0], n);
}