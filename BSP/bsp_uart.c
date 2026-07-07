/**
  ******************************************************************************
  * @file    bsp_uart.c
  * @brief   UART BSP wrappers
  ******************************************************************************
  */
#include "bsp_uart.h"
#include "usart.h"
#include <stdio.h>
#include <stdarg.h>

static char buf[128];

void bsp_uart_transmit(const uint8_t *data, uint16_t len)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)data, len, 100);
}

void bsp_uart_printf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    int n = vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    if (n > 0) bsp_uart_transmit((uint8_t *)buf, (uint16_t)n);
}
