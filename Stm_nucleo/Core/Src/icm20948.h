#ifndef ICM20948_H
#define ICM20948_H

#include "stm32f4xx_hal.h"

typedef struct {
    int16_t ax;
    int16_t ay;
    int16_t az;
} ICM20948_Accel_t;

void ICM20948_Init(I2C_HandleTypeDef *hi2c);
void ICM20948_ReadAccel(ICM20948_Accel_t *accel);

#endif

