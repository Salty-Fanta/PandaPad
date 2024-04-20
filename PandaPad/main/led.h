#ifndef LED_H
#define LED_H

#include <stdint.h>
#include <stdio.h>
#include "led_strip.h"
#include "esp_log.h"
#include "esp_err.h"

// Defines
#define LED_GPIO 13
#define LED_AMOUNT 16

//static uint8_t s_led_state = 0;

//led_strip_handle_t led_strip;

// Functions

void backlight_off(void);

led_strip_handle_t configure_led(void);

#endif