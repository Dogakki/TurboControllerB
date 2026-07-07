/**
  ******************************************************************************
  * @file    bsp_pwm.h
  * @brief   PWM BSP wrappers for TIM1
  ******************************************************************************
  */
#ifndef __BSP_PWM_H__
#define __BSP_PWM_H__

#include "main.h"
#include <stdint.h>
#include <stdbool.h>

void bsp_pwm_init(void);
void bsp_pwm_start(uint32_t channel);
void bsp_pwm_stop(uint32_t channel);
void bsp_pwm_start_complementary(uint32_t channel);
void bsp_pwm_stop_complementary(uint32_t channel);
void bsp_pwm_set_duty(uint32_t channel, uint8_t percent);
void bsp_pwm_start_all_motor(void);
void bsp_pwm_stop_all_motor(void);
void bsp_pwm_stop_all(void);

#endif /* __BSP_PWM_H__ */
