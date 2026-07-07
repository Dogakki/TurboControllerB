/**
  ******************************************************************************
  * @file    ignition.h
  * @brief   Glow plug ignition control module
  ******************************************************************************
  */
#ifndef __IGNITION_H__
#define __IGNITION_H__

#include <stdint.h>
#include <stdbool.h>

void ignition_init(void);
void ignition_set_duty(uint8_t percent);
void ignition_off(void);
uint8_t ignition_get_duty(void);
float ignition_get_current_mA(void);
bool ignition_is_overcurrent(void);

#endif /* __IGNITION_H__ */
