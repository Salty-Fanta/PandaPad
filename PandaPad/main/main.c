#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
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

 


    //led_strip_handle_t led_strip = configure_led();
    init_led();
    turn_on_backlight(2);
    turn_on_backlight(3);

    initialize_keypad();






    while(1){
        vTaskDelay(10);

    }
}
