/**
  ******************************************************************************
  * @file    safety.h
  * @brief   Safety module - fault detection and emergency shutdown
  ******************************************************************************
  */
#ifndef __SAFETY_H__
#define __SAFETY_H__

#include <stdint.h>
#include <stdbool.h>

void safety_init(void);
void safety_check(void);
void safety_emergency_stop(void);
bool safety_can_start(void);

#endif /* __SAFETY_H__ */
