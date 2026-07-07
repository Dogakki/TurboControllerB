/**
  ******************************************************************************
  * @file    rtos_events.h
  * @brief   RTOS event group handles
  ******************************************************************************
  */
#ifndef __RTOS_EVENTS_H__
#define __RTOS_EVENTS_H__

#include "cmsis_os.h"

extern osEventFlagsId_t evt_system;

/* Event flags */
#define EVT_CAN_RX          (1U << 0)
#define EVT_STATE_CHANGE    (1U << 1)
#define EVT_FAULT           (1U << 2)

void rtos_events_create(void);

#endif /* __RTOS_EVENTS_H__ */
