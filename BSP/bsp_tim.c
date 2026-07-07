/**
  ******************************************************************************
  * @file    bsp_tim.c
  * @brief   Timer input capture BSP wrappers (TIM2 for speed)
  ******************************************************************************
  */
#include "bsp_tim.h"
#include "tim.h"

void bsp_tim_ic_start(uint32_t ch)
{
    HAL_TIM_IC_Start_IT(&htim2, ch);
}

uint32_t bsp_tim_ic_read_capture(uint32_t ch)
{
    return HAL_TIM_ReadCapturedValue(&htim2, ch);
}
