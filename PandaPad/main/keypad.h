#ifndef KEYPAD_H
#define KEYPAD_H

#include <stdint.h>
#include <stdio.h>
#include "led_strip.h"
#include "esp_log.h"
#include "esp_err.h"
#include "iot_button.h"

// static const char *TAG = "BUTTON TEST";

#define BUTTON_NUM 16
static button_handle_t g_btns[BUTTON_NUM] = {0};

#define NUMBER_OF_ROWS 4
#define NUMBER_OF_COLUMNS 4

#define LONG_PRESS_DURATION_MS 1500
#define SHORT_PRESS_DURATION_MS 500


//static const char* get_btn_index(button_handle_t btn);

// static void button_press_down_cb(void *arg, void *data);
// static void button_press_up_cb(void *arg, void *data);
// static void button_press_repeat_cb(void *arg, void *data);
// static void button_single_click_cb(void *arg, void *data);
// static void button_double_click_cb(void *arg, void *data);
// static void button_long_press_start_cb(void *arg, void *data);
// static void button_long_press_hold_cb(void *arg, void *data);
// static void button_press_repeat_done_cb(void *arg, void *data);

void initialize_keypad();

#endif