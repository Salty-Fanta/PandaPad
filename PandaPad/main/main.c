#include <stdint.h>
#include <stdio.h>
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_err.h"
#include "sdkconfig.h"

//include ESP-IDF components
#include "led_strip.h"
#include "iot_button.h"

//include local sources

#include "led.h"
#include "keypad.h"

/* PandaPad key positions

-----------------------------
| 0 | 1 |                   |
---------   E-ink screen    -
| 2 | 3 |                   |
-----------------------------
|           | 4 | 5 | 6 | 7 |
-           -----------------
| Touchpad  | 8 | 9 | A | B |
-           -----------------
|           | C | D | E | F |
-----------------------------
*/



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

    initialize_keypad();

    while(1){
        vTaskDelay(10);

    }
}
