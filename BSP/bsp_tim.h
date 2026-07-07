/**
  ******************************************************************************
  * @file    bsp_tim.h
  * @brief   Timer input capture BSP wrappers
  ******************************************************************************
  */
#ifndef __BSP_TIM_H__
#define __BSP_TIM_H__

#include "main.h"
#include <stdint.h>

void bsp_tim_ic_start(uint32_t channel);
uint32_t bsp_tim_ic_read_capture(uint32_t channel);

#endif /* __BSP_TIM_H__ */
