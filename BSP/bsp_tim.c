/**
  ******************************************************************************
  * @file    bsp_tim.c
  * @brief   Timer input capture BSP wrappers (TIM2 for speed)
  ******************************************************************************
  */
#include "bsp_tim.h"
#include "tim.h"
#include "rpm.h"

void bsp_tim_ic_start(uint32_t ch)
{
    HAL_TIM_IC_Start_IT(&htim2, ch);
}

uint32_t bsp_tim_ic_read_capture(uint32_t ch)
{
    return HAL_TIM_ReadCapturedValue(&htim2, ch);
}

/**
  * @brief  HAL 输入捕获中断回调 (ISR上下文)
  *         TIM2_CH2 上升沿触发 → 转发给 rpm 模块计算转速
  */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM2 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
    {
        uint32_t val = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
        rpm_ic_callback(val);
    }
}
