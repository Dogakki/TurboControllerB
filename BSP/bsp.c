/**
  ******************************************************************************
  * @file    bsp.c
  * @brief   BSP layer init
  ******************************************************************************
  */
#include "bsp.h"
#include "bsp_gpio.h"
#include "bsp_pwm.h"
#include "bsp_power.h"

void BSP_Init(void)
{
    bsp_gpio_init();
    bsp_pwm_init();
    bsp_power_init();
    bsp_force_all_outputs_off();
}
