#include "icm20948.h"

#define ICM_ADDR        (0x68 << 1)
#define REG_PWR_MGMT_1  0x06
#define REG_ACCEL_XOUT_H 0x2D

static I2C_HandleTypeDef *icm_i2c;

void ICM20948_Write(uint8_t reg, uint8_t data)
{
    HAL_I2C_Mem_Write(icm_i2c, ICM_ADDR, reg,
                      I2C_MEMADD_SIZE_8BIT, &data, 1, HAL_MAX_DELAY);
}

void ICM20948_Read(uint8_t reg, uint8_t *data, uint8_t len)
{
    HAL_I2C_Mem_Read(icm_i2c, ICM_ADDR, reg,
                     I2C_MEMADD_SIZE_8BIT, data, len, HAL_MAX_DELAY);
}

void ICM20948_Init(I2C_HandleTypeDef *hi2c)
{
    icm_i2c = hi2c;

    // Wake up device
    ICM20948_Write(REG_PWR_MGMT_1, 0x01);
    HAL_Delay(10);
}

void ICM20948_ReadAccel(ICM20948_Accel_t *accel)
{
    uint8_t buf[6];
    ICM20948_Read(REG_ACCEL_XOUT_H, buf, 6);

    accel->ax = (int16_t)(buf[0] << 8 | buf[1]);
    accel->ay = (int16_t)(buf[2] << 8 | buf[3]);
    accel->az = (int16_t)(buf[4] << 8 | buf[5]);
}

