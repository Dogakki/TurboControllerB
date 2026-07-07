/**
  ******************************************************************************
  * @file    app_main.h
  * @brief   Application main - state machine
  ******************************************************************************
  */
#ifndef __APP_MAIN_H__
#define __APP_MAIN_H__

#include <stdint.h>

typedef enum {
    STATE_DISABLED = 0,
    STATE_IDLE,
    STATE_PREHEAT,
    STATE_IGNITION,
    STATE_PUMP_START,
    STATE_MAIN_FUEL,
    STATE_RUN,
    STATE_SHUTDOWN,
    STATE_FAULT
} system_state_t;

void app_control_tick(void);
system_state_t app_get_state(void);
const char* app_get_state_string(void);

#endif /* __APP_MAIN_H__ */
