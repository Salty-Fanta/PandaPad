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

// Functions

//void backlight_off(void);

void turn_on_backlight(int lednr);
void turn_off_backlight(int lednr);

void init_led(void);


#endif