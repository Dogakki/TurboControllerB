/**
  ******************************************************************************
  * @file    drv8311.c
  * @brief   DRV8311 ESC chip driver
  ******************************************************************************
  */
#include "drv8311.h"
#include "bsp_power.h"
#include "bsp_gpio.h"

static bool enabled;

void drv8311_init(void) { enabled = false; }
void drv8311_enable(void)  { bsp_esc_en_set(true);  enabled = true; }
void drv8311_disable(void) { bsp_esc_en_set(false); enabled = false; }
bool drv8311_is_fault(void) { return bsp_esc_fault_read(); }
