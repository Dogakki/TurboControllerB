/**
  ******************************************************************************
  * @file    rtos_timer.c
  * @brief   RTOS software timers
  ******************************************************************************
  */
#include "rtos_timer.h"
#include "service_watchdog.h"

osTimerId_t tmr_heartbeat;

static void heartbeat_cb(void *arg) { (void)arg; /* TODO: check watchdog */ }

void rtos_timers_create(void)
{
    tmr_heartbeat = osTimerNew(heartbeat_cb, osTimerPeriodic, NULL, NULL);
}
