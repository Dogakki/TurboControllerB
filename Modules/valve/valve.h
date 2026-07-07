/**
  ******************************************************************************
  * @file    valve.h
  * @brief   GLOW and MAIN valve control module
  ******************************************************************************
  */
#ifndef __VALVE_H__
#define __VALVE_H__

#include <stdbool.h>

void valve_init(void);
void valve_glow_on(void);
void valve_glow_off(void);
void valve_main_on(void);
void valve_main_off(void);
void valve_all_off(void);

#endif /* __VALVE_H__ */
