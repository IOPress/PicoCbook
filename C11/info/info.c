#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

int main()
{
    stdio_init_all();

    i2c_init(i2c0, 100 * 1000);

    gpio_set_function(4, GPIO_FUNC_I2C);
    gpio_set_function(5, GPIO_FUNC_I2C);
    uint8_t buf[] = {0xE7};

    i2c_write_blocking(i2c0, 0x40, buf, 1, false);
    i2c_read_blocking(i2c0, 0x40, buf, 1, false);
    printf("User Register = %X \r\n", buf[0]);
}