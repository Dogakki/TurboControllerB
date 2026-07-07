/**
  ******************************************************************************
  * @file    bsp_gpio.c
  * @brief   GPIO BSP wrappers
  ******************************************************************************
  */
#include "bsp_gpio.h"

void bsp_gpio_init(void) { /* CubeMX MX_GPIO_Init already done */ }

bool bsp_sub_en_read(void)
{
    return (HAL_GPIO_ReadPin(PIN_SUB_EN_PORT, PIN_SUB_EN_PIN) == GPIO_PIN_SET);
}

bool bsp_esc_fault_read(void)
{
    return (HAL_GPIO_ReadPin(PIN_ESC_FAULT_PORT, PIN_ESC_FAULT_PIN) == GPIO_PIN_RESET);
}
