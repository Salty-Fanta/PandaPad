// Macropad.cpp
#include "Macropad.hpp"

extern "C" {
#include "led.h"
#include "keypad.h"
#include "cirque_pinnacle.h"
#include "usb_hid.h"
#include "driver/gpio.h"
#include "esp_log.h"
}

static constexpr gpio_num_t SCREEN_POWER_PIN = GPIO_NUM_17;
static constexpr char TAG[] = "Touch_Data";

void Macropad::init() {
    gpio_set_direction(SCREEN_POWER_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(SCREEN_POWER_PIN, 1);
    vTaskDelay(pdMS_TO_TICKS(100));

    init_led();
    turn_on_backlight(2);
    turn_on_backlight(3);

    initialize_keypad();
    cirque_pinnacle_init();
    usb_hid_init();
}

void Macropad::run() {
    while (true) {
        vTaskDelay(pdMS_TO_TICKS(10));
        handleTouchpad();
    }
}

void Macropad::handleTouchpad() {
    pinnacle_data_t touch_results = cirque_pinnacle_read_data();

    if (touch_results.valid && tud_hid_ready()) {
        tud_hid_mouse_report(HID_ITF_PROTOCOL_MOUSE, 0x00,
                              touch_results.yDelta,
                              touch_results.xDelta * -1,
                              0, 0);
        ESP_LOGI(TAG, "X= %d, Y= %d", touch_results.xDelta, touch_results.yDelta);
    }
}