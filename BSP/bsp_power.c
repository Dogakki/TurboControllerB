/**
  ******************************************************************************
  * @file    bsp_power.c
  * @brief   Power control BSP
  ******************************************************************************
  */
#include "bsp_power.h"
#include "bsp_pwm.h"
#include "pin_config.h"

void bsp_power_init(void) { /* GPIO already init by CubeMX */ }

void bsp_esc_en_set(bool en)
{
    HAL_GPIO_WritePin(PIN_ESC_EN_PORT, PIN_ESC_EN_PIN, en ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void bsp_main_valve_set(bool on)
{
    HAL_GPIO_WritePin(PIN_MAIN_VALVE_PORT, PIN_MAIN_VALVE_PIN, on ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void bsp_glow_valve_set(bool on)
{
    HAL_GPIO_WritePin(PIN_GLOW_VALVE_PORT, PIN_GLOW_VALVE_PIN, on ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void bsp_force_all_outputs_off(void)
{
    bsp_esc_en_set(false);
    bsp_pwm_stop_all();
    bsp_main_valve_set(false);
    bsp_glow_valve_set(false);
}
