/**
  ******************************************************************************
  * @file    bsp_gpio.h
  * @brief   GPIO BSP wrappers
  ******************************************************************************
  */
#ifndef __BSP_GPIO_H__
#define __BSP_GPIO_H__

#include "main.h"
#include "pin_config.h"
#include <stdbool.h>

void bsp_gpio_init(void);
bool bsp_sub_en_read(void);
bool bsp_esc_fault_read(void);

#endif /* __BSP_GPIO_H__ */
