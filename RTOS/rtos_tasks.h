/**
  ******************************************************************************
  * @file    rtos_tasks.h
  * @brief   RTOS task creation
  ******************************************************************************
  */
#ifndef __RTOS_TASKS_H__
#define __RTOS_TASKS_H__

#include "cmsis_os.h"

extern osThreadId_t task_safety;
extern osThreadId_t task_control;
extern osThreadId_t task_motor;
extern osThreadId_t task_comm;
extern osThreadId_t task_sensor;
extern osThreadId_t task_storage;
extern osThreadId_t task_debug;
extern osThreadId_t task_led;

void rtos_tasks_create(void);

#endif /* __RTOS_TASKS_H__ */
