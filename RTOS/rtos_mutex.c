/**
  ******************************************************************************
  * @file    rtos_mutex.c
  * @brief   RTOS mutex creation
  ******************************************************************************
  */
#include "rtos_mutex.h"

osMutexId_t mtx_sensor_data;
osMutexId_t mtx_can_tx;

void rtos_mutex_create(void)
{
    mtx_sensor_data = osMutexNew(NULL);
    mtx_can_tx = osMutexNew(NULL);
}
