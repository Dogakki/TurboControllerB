/**
  ******************************************************************************
  * @file    bsp_power.h
  * @brief   Power control BSP - ESC_EN, force all outputs off
  ******************************************************************************
  */
#ifndef __BSP_POWER_H__
#define __BSP_POWER_H__

#include "main.h"
#include <stdbool.h>

void bsp_power_init(void);
void bsp_esc_en_set(bool enable);
void bsp_main_valve_set(bool on);
void bsp_glow_valve_set(bool on);
void bsp_force_all_outputs_off(void);

#endif /* __BSP_POWER_H__ */
