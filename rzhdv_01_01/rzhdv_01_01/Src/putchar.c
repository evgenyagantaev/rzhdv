#include "stm32l4xx_hal.h"

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

void putchar_for_test(int ch)
{
    uint8_t symbol = (uint8_t)ch;
    HAL_UART_Transmit(&huart2, &symbol, 1, 500);  // for discovery board
    //HAL_UART_Transmit(&huart1, &symbol, 1, 500);  // for production board

    //return ch;
}

