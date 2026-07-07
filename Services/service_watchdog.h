/**
  ******************************************************************************
  * @file    service_watchdog.h
  * @brief   Software watchdog for task heartbeat monitoring
  ******************************************************************************
  */
#ifndef __SERVICE_WATCHDOG_H__
#define __SERVICE_WATCHDOG_H__

#include <stdint.h>
#include <stdbool.h>

void watchdog_init(void);
void watchdog_feed(uint8_t task_id);
bool watchdog_check(uint8_t task_id, uint32_t timeout_ms);

#define WD_TASK_CONTROL     0
#define WD_TASK_SAFETY      1
#define WD_TASK_COUNT       2

#endif /* __SERVICE_WATCHDOG_H__ */
