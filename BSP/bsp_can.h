/**
  ******************************************************************************
  * @file    bsp_can.h
  * @brief   CAN BSP wrappers
  ******************************************************************************
  */
#ifndef __BSP_CAN_H__
#define __BSP_CAN_H__

#include "main.h"
#include <stdint.h>
#include <stdbool.h>

void bsp_can_start(void);
void bsp_can_config_filter(void);
void bsp_can_activate_rx_irq(void);
bool bsp_can_send(uint32_t id, const uint8_t *data, uint8_t len);
bool bsp_can_receive(uint32_t *id, uint8_t *data, uint8_t *len);

#endif /* __BSP_CAN_H__ */
