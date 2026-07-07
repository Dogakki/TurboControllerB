/**
  ******************************************************************************
  * @file    rtos_queues.c
  * @brief   RTOS queue creation
  ******************************************************************************
  */
#include "rtos_queues.h"

osMessageQueueId_t q_can_rx;

void rtos_queues_create(void)
{
    q_can_rx = osMessageQueueNew(8, sizeof(can_rx_msg_t), NULL);
}
