#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
int main()
{
 stdio_init_all();
 adc_init();
 adc_gpio_init(26);
 adc_gpio_init(27);

 while (1) {
   const float conversion_factor = 3.3f / (1 << 12);
   adc_select_input(0);
   uint16_t result = adc_read();
   printf("Raw value 0: 0x%03x, voltage: %f V\n",
                            result, result * conversion_factor);
   adc_select_input(1);
   result = adc_read();
   printf("Raw value 1: 0x%03x, voltage: %f V\n", 
                            result, result * conversion_factor);
   sleep_ms(500);
 }
}
