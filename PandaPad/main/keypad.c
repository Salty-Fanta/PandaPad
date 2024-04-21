#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_err.h"
#include "iot_button.h"
#include "led_strip.h"
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
| Touchpad  | 8 | 9 | 10| 11|
-           -----------------
|           | 12| 13| 14| 15|
-----------------------------
*/

static const char *TAG = "BUTTON TEST";

const char* keys[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS] = {
  {"4","5","6","7"},
  {"11","10","9","8"},
  {"12","13","14","15"},
  {"1","0","2","3"}
};

static const char* get_btn_index(button_handle_t btn)
{
    for (size_t i = 0; i < BUTTON_NUM; i++) {
        if (btn == g_btns[i]) {
            // Calculate row and column from the linear index
            size_t row = i / NUMBER_OF_ROWS; // Integer division to get the row
            size_t col = i % NUMBER_OF_COLUMNS; // Modulo operation to get the column
            return keys[row][col];
        }
    }
    return NULL; // Return NULL if the button is not found
}

void button_press_down_cb(void *arg, void *data)
{
    ESP_LOGI(TAG, "BTN%s: BUTTON_PRESS_DOWN", get_btn_index((button_handle_t)arg));
    turn_on_backlight(atoi(get_btn_index((button_handle_t)arg)));
}

void button_press_up_cb(void *arg, void *data)
{
    ESP_LOGI(TAG, "BTN%s: BUTTON_PRESS_UP[%d]", get_btn_index((button_handle_t)arg), iot_button_get_ticks_time((button_handle_t)arg));
    turn_off_backlight(atoi(get_btn_index((button_handle_t)arg)));
}

void button_press_repeat_cb(void *arg, void *data)
{
    ESP_LOGI(TAG, "BTN%s: BUTTON_PRESS_REPEAT[%d]", get_btn_index((button_handle_t)arg), iot_button_get_repeat((button_handle_t)arg));
}

void button_single_click_cb(void *arg, void *data)
{
    ESP_LOGI(TAG, "BTN%s: BUTTON_SINGLE_CLICK", get_btn_index((button_handle_t)arg));
}

void button_double_click_cb(void *arg, void *data)
{
    ESP_LOGI(TAG, "BTN%s: BUTTON_DOUBLE_CLICK", get_btn_index((button_handle_t)arg));
}

void button_long_press_start_cb(void *arg, void *data)
{
    ESP_LOGI(TAG, "BTN%s: BUTTON_LONG_PRESS_START", get_btn_index((button_handle_t)arg));
}

void button_long_press_hold_cb(void *arg, void *data)
{
    ESP_LOGI(TAG, "BTN%s: BUTTON_LONG_PRESS_HOLD[%d],count is [%d]", get_btn_index((button_handle_t)arg), iot_button_get_ticks_time((button_handle_t)arg), iot_button_get_long_press_hold_cnt((button_handle_t)arg));
}

void button_press_repeat_done_cb(void *arg, void *data)
{
    ESP_LOGI(TAG, "BTN%s: BUTTON_PRESS_REPEAT_DONE[%d]", get_btn_index((button_handle_t)arg), iot_button_get_repeat((button_handle_t)arg));
}

void initialize_keypad() {
    // Define the GPIO pins for the keypad rows and columns
    int32_t row_gpio[NUMBER_OF_ROWS] = {38, 39, 40, 12}; // Example GPIOs for rows
    int32_t col_gpio[NUMBER_OF_COLUMNS] = {42, 41, 6, 34}; // Example GPIOs for columns

    button_config_t cfg = {
        .type = BUTTON_TYPE_MATRIX,
        .long_press_time = LONG_PRESS_DURATION_MS,
        .short_press_time = SHORT_PRESS_DURATION_MS,
        .matrix_button_config = {
            .row_gpio_num = 0,
            .col_gpio_num = 0,
        }
    };

    for (int i = 0; i < NUMBER_OF_ROWS; i++) {
        cfg.matrix_button_config.row_gpio_num = row_gpio[i];
        for (int j = 0; j < NUMBER_OF_COLUMNS; j++) {
            cfg.matrix_button_config.col_gpio_num = col_gpio[j];
            g_btns[i * NUMBER_OF_ROWS + j] = iot_button_create(&cfg);
            iot_button_register_cb(g_btns[i * NUMBER_OF_ROWS + j], BUTTON_PRESS_DOWN, button_press_down_cb, NULL);
            iot_button_register_cb(g_btns[i * NUMBER_OF_ROWS + j], BUTTON_PRESS_UP, button_press_up_cb, NULL);
            iot_button_register_cb(g_btns[i * NUMBER_OF_ROWS + j], BUTTON_PRESS_REPEAT, button_press_repeat_cb, NULL);
            iot_button_register_cb(g_btns[i * NUMBER_OF_ROWS + j], BUTTON_SINGLE_CLICK, button_single_click_cb, NULL);
            iot_button_register_cb(g_btns[i * NUMBER_OF_ROWS + j], BUTTON_DOUBLE_CLICK, button_double_click_cb, NULL);
            iot_button_register_cb(g_btns[i * NUMBER_OF_ROWS + j], BUTTON_LONG_PRESS_START, button_long_press_start_cb, NULL);
            iot_button_register_cb(g_btns[i * NUMBER_OF_ROWS + j], BUTTON_LONG_PRESS_HOLD, button_long_press_hold_cb, NULL);
            iot_button_register_cb(g_btns[i * NUMBER_OF_ROWS + j], BUTTON_PRESS_REPEAT_DONE, button_press_repeat_done_cb, NULL);
        }
    }
}



