/**
  ******************************************************************************
  * @file    rtos_mutex.h
  * @brief   RTOS mutex handles
  ******************************************************************************
  */
#ifndef __RTOS_MUTEX_H__
#define __RTOS_MUTEX_H__

#include "cmsis_os.h"

extern osMutexId_t mtx_sensor_data;
extern osMutexId_t mtx_can_tx;

void rtos_mutex_create(void);

#endif /* __RTOS_MUTEX_H__ */
