/**
  ******************************************************************************
  * @file    rtos_queues.h
  * @brief   RTOS queue handles
  ******************************************************************************
  */
#ifndef __RTOS_QUEUES_H__
#define __RTOS_QUEUES_H__

#include "cmsis_os.h"
#include "protocol_can.h"

extern osMessageQueueId_t q_can_rx;

void rtos_queues_create(void);

#endif /* __RTOS_QUEUES_H__ */
