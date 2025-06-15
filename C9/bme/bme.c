#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"

int main()
{
    stdio_init_all();
    spi_init(spi0, 500 * 1000);
    spi_set_format(spi0, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);

    gpio_set_function(16, GPIO_FUNC_SPI);
    gpio_set_function(18, GPIO_FUNC_SPI);
    gpio_set_function(19, GPIO_FUNC_SPI);
    gpio_init(17);
    gpio_set_dir(17, GPIO_OUT);
    gpio_put(17, 1);
    sleep_ms(1);
    uint8_t wBuff[1] = {0xD0};
    uint8_t rBuff[8];

    gpio_put(17, 0);
    sleep_us(1);
    spi_write_blocking(spi0, wBuff, 1);
    spi_read_blocking(spi0, 0, rBuff, 1);
    sleep_us(1);
    gpio_put(17, 1);
    printf("Chip ID is 0x%x\n", rBuff[0]);
    gpio_put(17, 0);
    sleep_us(1);
    wBuff[0] = 0xF2;
    wBuff[1] = 0x1;
    spi_write_blocking(spi0, wBuff, 2);
    wBuff[0] = 0xF4;
    wBuff[1] = 0x27;
    spi_write_blocking(spi0, wBuff, 2);
    gpio_put(17, 1);
    sleep_us(1);

    wBuff[0] = 0xF7;
    gpio_put(17, 0);
    sleep_us(1);
    spi_write_blocking(spi0, wBuff, 1);

    spi_read_blocking(spi0, 0, rBuff, 8);
    sleep_us(1);
    gpio_put(17, 1);

    uint32_t pressure = ((uint32_t)rBuff[0] << 12) |
                        ((uint32_t)rBuff[1] << 4) | (rBuff[2] >> 4);
    uint32_t temperature = ((uint32_t)rBuff[3] << 12) |
                           ((uint32_t)rBuff[4] << 4) | (rBuff[5] >> 4);
    uint32_t humidity = (uint32_t)rBuff[6] << 8 | rBuff[7];

    printf("Humidity = %d\n", humidity);
    printf("Pressure = %d\n", pressure);
    printf("Temp. = %d\n", temperature);
}