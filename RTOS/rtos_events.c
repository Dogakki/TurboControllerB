/**
  ******************************************************************************
  * @file    rtos_events.c
  * @brief   RTOS event group creation
  ******************************************************************************
  */
#include "rtos_events.h"

osEventFlagsId_t evt_system;

void rtos_events_create(void)
{
    evt_system = osEventFlagsNew(NULL);
}
