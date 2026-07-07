/**
  ******************************************************************************
  * @file    rtos.c
  * @brief   RTOS master init - creates all queues, mutexes, events, timers, tasks
  ******************************************************************************
  */
#include "rtos.h"
#include "rtos_mutex.h"
#include "rtos_queues.h"
#include "rtos_events.h"
#include "rtos_tasks.h"
#include "rtos_timer.h"

void RTOS_Init(void)
{
    rtos_mutex_create();
    rtos_queues_create();
    rtos_events_create();
    rtos_timers_create();
    rtos_tasks_create();
}
