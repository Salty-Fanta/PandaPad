// Copyright (c) 2018 Cirque Corp. Restrictions apply. See: www.cirque.com/sw-license
#include "cirque_pinnacle.h"
//#include "i2c_master.h" //new driver, does not work
#include "driver/i2c.h"
#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "rom/ets_sys.h"
#include "cirque_pinnacle_regdefs.h"

// Masks for Cirque Register Access Protocol (RAP)
#define WRITE_MASK 0x80
#define READ_MASK 0xA0

#define CIRQUE_PINNACLE_ADDR        I2C_ADDRESS_DEFAULT

#define I2C_MASTER_SCL_IO           9           /*!< GPIO number used for I2C master clock */
#define I2C_MASTER_SDA_IO           8           /*!< GPIO number used for I2C master data  */
#define I2C_MASTER_NUM              0           /*!< I2C master i2c port number, the number of i2c peripheral interfaces available will depend on the chip */
#define I2C_MASTER_FREQ_HZ          100000      /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE   0           /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0           /*!< I2C master doesn't need buffer */
#define I2C_MASTER_TIMEOUT_MS       1000

extern bool touchpad_init;

static const char *TAG = "i2c-pinnacle-touchpad";

void i2c_init(void)
{
    int i2c_master_port = I2C_MASTER_NUM;

    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };

    i2c_param_config(i2c_master_port, &conf);

    if (i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0) != ESP_OK) {
            ESP_LOGI(TAG, "i2c init failed");
    }
}

/*  RAP Functions */
// Reads <count> Pinnacle registers starting at <address>
void RAP_ReadBytes(uint8_t address, uint8_t* data, uint8_t count) {
    int ret;
    uint8_t cmdByte = READ_MASK | address; // Form the READ command byte
    if (touchpad_init) {
        if ((ret = i2c_master_write_read_device(I2C_MASTER_NUM, CIRQUE_PINNACLE_ADDR, &cmdByte, 1, data, count, CIRQUE_PINNACLE_TIMEOUT / portTICK_PERIOD_MS)) != ESP_OK) {
            ESP_LOGI(TAG, "error cirque_pinnacle i2c_readBytes");
            ESP_LOGI(TAG, "ESP_ERROR: %x", ret);
            touchpad_init = false;
        }
    }
}

// Writes single-byte <data> to <address>
void RAP_Write(uint8_t address, uint8_t data) {
    int ret;
    uint8_t cmdByte = WRITE_MASK | address; // Form the WRITE command byte
    uint8_t write_buf[2] = {cmdByte, data};
    if (touchpad_init) {
        if ((ret = i2c_master_write_to_device(I2C_MASTER_NUM, CIRQUE_PINNACLE_ADDR, write_buf, sizeof(write_buf), CIRQUE_PINNACLE_TIMEOUT / portTICK_PERIOD_MS)) != ESP_OK) {
            ESP_LOGI(TAG, "error cirque_pinnacle i2c_write_register");
            ESP_LOGI(TAG, "ESP_ERROR: %x", ret);
            touchpad_init = false;
        }
    }
}
