#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
int main()
{
    stdio_init_all();
    i2c_init(i2c0, 100 * 1000);
    gpio_set_function(4, GPIO_FUNC_I2C);
    gpio_set_function(5, GPIO_FUNC_I2C);
    uint8_t buf[4] = {0xE3};
    i2c_write_blocking(i2c0, 0x40, buf, 1, true);
    i2c_read_blocking(i2c0, 0x40, buf, 3, false);
    uint8_t msb = buf[0];
    uint8_t lsb = buf[1];
    uint8_t check = buf[2];
    printf("msb %d \n\r lsb %d \n\r checksum %d \n\r",
                                                  msb, lsb, check);
};
