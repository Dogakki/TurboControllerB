/**
  ******************************************************************************
  * @file    rtos_timer.h
  * @brief   RTOS software timers
  ******************************************************************************
  */
#ifndef __RTOS_TIMER_H__
#define __RTOS_TIMER_H__

#include "cmsis_os.h"

extern osTimerId_t tmr_heartbeat;

void rtos_timers_create(void);

#endif /* __RTOS_TIMER_H__ */
