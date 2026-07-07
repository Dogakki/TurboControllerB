/**
  ******************************************************************************
  * @file    rpm.c
  * @brief   Speed sensor RPM module (TIM2 input capture)
  ******************************************************************************
  */
#include "rpm.h"
#include "bsp_tim.h"
#include "pin_config.h"
#include "fault_config.h"
#include "board_config.h"
#include "main.h"

#ifndef PULSES_PER_REV
#define PULSES_PER_REV 1
#endif

#define HIST_SIZE 4
static volatile uint32_t last_cap, last_valid_tick;
static uint32_t hist[HIST_SIZE];
static uint8_t h_idx, h_cnt;

void rpm_init(void)
{
    last_cap = 0; last_valid_tick = 0; h_idx = 0; h_cnt = 0;
    bsp_tim_ic_start(IC_CH_SPEED);
}

void rpm_ic_callback(uint32_t cap)
{
    uint32_t delta = (cap >= last_cap) ? (cap - last_cap) : (0xFFFF - last_cap + cap + 1);
    last_cap = cap;
    hist[h_idx] = delta;
    h_idx = (h_idx + 1) % HIST_SIZE;
    if (h_cnt < HIST_SIZE) h_cnt++;
    last_valid_tick = HAL_GetTick();
}

uint32_t rpm_get_value(void)
{
    if (h_cnt == 0) return 0;
    uint32_t sum = 0;
    for (uint8_t i = 0; i < h_cnt; i++) sum += hist[i];
    uint32_t avg = sum / h_cnt;
    if (avg == 0) return 0;
    /* Timer tick = 1MHz (42MHz / 42 prescaler) */
    return (1000000UL / avg) * 60UL / PULSES_PER_REV;
}

bool rpm_is_valid(void) { return ((HAL_GetTick() - last_valid_tick) < SPEED_LOST_TIMEOUT_MS); }
