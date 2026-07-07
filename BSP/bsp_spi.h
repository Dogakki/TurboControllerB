/**
  ******************************************************************************
  * @file    bsp_spi.h
  * @brief   SPI BSP wrappers
  ******************************************************************************
  */
#ifndef __BSP_SPI_H__
#define __BSP_SPI_H__

#include "main.h"
#include <stdint.h>
#include <stdbool.h>

bool bsp_spi_receive(uint8_t *buf, uint16_t len, uint32_t timeout_ms);

#endif /* __BSP_SPI_H__ */
