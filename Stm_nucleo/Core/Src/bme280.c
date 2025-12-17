#include "bme280.h"
#include "stdint.h"

#define BME280_ADDR 0x76 << 1  // HAL expects 8-bit address
#define DS3231_ADDR 0x68 << 1

/* Small helper to read BME280 registers (simplified) */
int bme_read_raw(int16_t *temp, uint32_t *press, int32_t *hum) {
    uint8_t reg = 0xF7; // pressure msb start
    uint8_t data[8];
    if (HAL_I2C_Master_Transmit(&hi2c1, BME280_ADDR, &reg, 1, 100) != HAL_OK) return -1;
    if (HAL_I2C_Master_Receive(&hi2c1, BME280_ADDR, data, 8, 100) != HAL_OK) return -1;
    // parse raw; here we will just make a rough sample parsing
    *press = (uint32_t)((data[0]<<12) | (data[1]<<4) | (data[2]>>4));
    *temp  = (int16_t)((data[3]<<12) | (data[4]<<4) | (data[5]>>4));
    *hum   = (int32_t)(data[6]<<8 | data[7]);
    return 0;
}
