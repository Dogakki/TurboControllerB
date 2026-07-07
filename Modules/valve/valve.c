/**
  ******************************************************************************
  * @file    valve.c
  * @brief   GLOW and MAIN valve control module
  ******************************************************************************
  */
#include "valve.h"
#include "bsp_power.h"

void valve_init(void) { valve_all_off(); }
void valve_glow_on(void)  { bsp_glow_valve_set(true); }
void valve_glow_off(void) { bsp_glow_valve_set(false); }
void valve_main_on(void)  { bsp_main_valve_set(true); }
void valve_main_off(void) { bsp_main_valve_set(false); }
void valve_all_off(void)  { valve_glow_off(); valve_main_off(); }
