/**
  ******************************************************************************
  * @file    service_watchdog.c
  * @brief   Software watchdog
  ******************************************************************************
  */
#include "service_watchdog.h"
#include "main.h"

static uint32_t last_feed[WD_TASK_COUNT];

void watchdog_init(void)
{
    for (int i = 0; i < WD_TASK_COUNT; i++) last_feed[i] = HAL_GetTick();
}

void watchdog_feed(uint8_t id)
{
    if (id < WD_TASK_COUNT) last_feed[id] = HAL_GetTick();
}

bool watchdog_check(uint8_t id, uint32_t timeout_ms)
{
    if (id >= WD_TASK_COUNT) return false;
    return ((HAL_GetTick() - last_feed[id]) > timeout_ms);
}
