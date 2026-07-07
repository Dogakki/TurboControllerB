/**
  ******************************************************************************
  * @file    bsp_uart.h
  * @brief   UART BSP wrappers
  ******************************************************************************
  */
#ifndef __BSP_UART_H__
#define __BSP_UART_H__

#include "main.h"
#include <stdint.h>

void bsp_uart_transmit(const uint8_t *data, uint16_t len);
void bsp_uart_printf(const char *fmt, ...);

#endif /* __BSP_UART_H__ */
