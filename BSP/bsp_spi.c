/**
  ******************************************************************************
  * @file    bsp_spi.c
  * @brief   SPI BSP wrappers
  ******************************************************************************
  */
#include "bsp_spi.h"
#include "spi.h"

bool bsp_spi_receive(uint8_t *buf, uint16_t len, uint32_t timeout_ms)
{
    return (HAL_SPI_Receive(&hspi1, buf, len, timeout_ms) == HAL_OK);
}
