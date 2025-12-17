#ifndef NEO_M8N_H
#define NEO_M8N_H

#include "stm32f4xx_hal.h"

#define GPS_BUFFER_SIZE 256

void GPS_Init(UART_HandleTypeDef *huart);
void GPS_ReadLine(char *line, uint16_t max_len);

#endif

