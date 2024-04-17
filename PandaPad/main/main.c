#include <stdint.h>
#include <stdio.h>
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_err.h"
#include "led_strip.h"
#include "sdkconfig.h"

//include sources
#include "led.h"

void app_main(void)
{
    gpio_set_direction(17, GPIO_MODE_OUTPUT);
    gpio_set_level(17, 1);
    vTaskDelay(100);

    led_strip_handle_t led_strip = configure_led();


    led_strip_set_pixel(led_strip, 1, 255, 0, 0);
    led_strip_set_pixel(led_strip, 2, 0, 255, 0);
    led_strip_set_pixel(led_strip, 3, 0, 0, 255);
    led_strip_refresh(led_strip);

    while(1){
        
    }
}
