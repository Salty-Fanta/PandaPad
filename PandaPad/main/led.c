#include <stdint.h>
#include <stdio.h>
#include "led.h"
#include "led_strip.h"
#include "esp_log.h"
#include "esp_err.h"

static const char *TAG = "LED";

// void backlight_off(void)
// {
//     led_strip_clear(led_strip);
// }

led_strip_handle_t configure_led(void)
{
    ESP_LOGI(TAG, "Example configured to blink addressable LED!");
    /* LED strip initialization with the GPIO and pixels number*/
    led_strip_config_t strip_config = {
        .strip_gpio_num = LED_GPIO,                 // The GPIO that connected to the LED strip's data line
        .max_leds = LED_AMOUNT,                     // The number of LEDs in the strip,
        .led_pixel_format = LED_PIXEL_FORMAT_GRB,   // Pixel format of your LED strip
        .led_model = LED_MODEL_SK6812,              // LED strip model
        .flags.invert_out = false,                  // whether to invert the output signal
    };
   
    // LED strip backend configuration: RMT
    led_strip_rmt_config_t rmt_config = {
        .resolution_hz = 10 * 1000 * 1000, // 10MHz
        .flags.with_dma = false,
    };

    // LED Strip object handle
    led_strip_handle_t led_strip;
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));
    ESP_LOGI(TAG, "Created LED strip object with RMT backend");
    return led_strip;


    /* Set all LED off to clear all pixels */
    led_strip_clear(led_strip);
}