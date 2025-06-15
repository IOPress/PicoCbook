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
    uint16_t wBuff[3] = {0x01, 0x80, 0x00};
    uint16_t rBuff[3];
    gpio_put(17, 0);
    int n = spi_write16_read16_blocking(spi0, wBuff, rBuff, 3);
    sleep_us(1);
    gpio_put(17, 1);
    int data = ((int)rBuff[1] & 0x03) << 8 | (int)rBuff[2];
    float volts = (float)data * 3.3f / 1023.0f;
    printf("%f V\n", volts);
}
