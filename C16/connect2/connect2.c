#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

int setup(uint32_t country, const char *ssid, const char *pass,
          uint32_t auth)
{
    if (cyw43_arch_init_with_country(country))
    {
        return 1;
    }
    cyw43_arch_enable_sta_mode();

    if (cyw43_arch_wifi_connect_async(ssid, pass, auth))
    {
        return 2;
    }
    int flashrate = 1000;
    int status = CYW43_LINK_UP + 1;
    while (status >= 0 && status != CYW43_LINK_UP)
    {
        int new_status = cyw43_tcpip_link_status(&cyw43_state,
                                                 CYW43_ITF_STA);
        if (new_status != status)
        {
            status = new_status;
            flashrate = flashrate / (status + 1);
            printf("connect status: %d %d\n", status, flashrate);
        }
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(flashrate);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        sleep_ms(flashrate);
    }
    if (status < 0)
    {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    }
    else
    {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    }
    return status;
}

char ssid[] = "ssid";
char pass[] = "password";
uint32_t country = CYW43_COUNTRY_WORLDWIDE;
uint32_t auth = CYW43_AUTH_WPA2_MIXED_PSK;

int main()
{
    stdio_init_all();
    setup(country, ssid, pass, auth);
    while (true)
    {
        sleep_ms(1);
    }
}
