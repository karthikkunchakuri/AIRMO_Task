#include "neo_m8n.h"
#include <string.h>

static UART_HandleTypeDef *gps_uart;

void GPS_Init(UART_HandleTypeDef *huart)
{
    gps_uart = huart;
}

void GPS_ReadLine(char *line, uint16_t max_len)
{
    uint8_t ch;
    uint16_t idx = 0;

    while (idx < max_len - 1)
    {
        HAL_UART_Receive(gps_uart, &ch, 1, HAL_MAX_DELAY);

        if (ch == '\n')
        {
            break;
        }
        line[idx++] = ch;
    }
    line[idx] = '\0';
}

