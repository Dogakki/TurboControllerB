/**
  ******************************************************************************
  * @file    bsp_pwm.c
  * @brief   PWM BSP wrappers for TIM1 (motor CH1-3 + complementary, ignition CH4)
  ******************************************************************************
  */
#include "bsp_pwm.h"
#include "tim.h"
#include "board_config.h"
#include "pin_config.h"

void bsp_pwm_init(void) { /* TIM1 already configured by CubeMX */ }

void bsp_pwm_start(uint32_t ch) { HAL_TIM_PWM_Start(&htim1, ch); }
void bsp_pwm_stop(uint32_t ch)  { HAL_TIM_PWM_Stop(&htim1, ch); }
void bsp_pwm_start_complementary(uint32_t ch) { HAL_TIMEx_PWMN_Start(&htim1, ch); }
void bsp_pwm_stop_complementary(uint32_t ch)  { HAL_TIMEx_PWMN_Stop(&htim1, ch); }

void bsp_pwm_set_duty(uint32_t ch, uint8_t pct)
{
    if (pct > 100) pct = 100;
    uint32_t pulse = ((uint32_t)pct * (BOARD_TIM1_PERIOD + 1)) / 100;
    __HAL_TIM_SET_COMPARE(&htim1, ch, pulse);
}

void bsp_pwm_start_all_motor(void)
{
    bsp_pwm_start(PWM_CH_U);
    bsp_pwm_start(PWM_CH_V);
    bsp_pwm_start(PWM_CH_W);
    bsp_pwm_start_complementary(PWM_CH_U);
    bsp_pwm_start_complementary(PWM_CH_V);
    bsp_pwm_start_complementary(PWM_CH_W);
}

void bsp_pwm_stop_all_motor(void)
{
    bsp_pwm_set_duty(PWM_CH_U, 0);
    bsp_pwm_set_duty(PWM_CH_V, 0);
    bsp_pwm_set_duty(PWM_CH_W, 0);
    bsp_pwm_stop(PWM_CH_U);
    bsp_pwm_stop(PWM_CH_V);
    bsp_pwm_stop(PWM_CH_W);
    bsp_pwm_stop_complementary(PWM_CH_U);
    bsp_pwm_stop_complementary(PWM_CH_V);
    bsp_pwm_stop_complementary(PWM_CH_W);
}

void bsp_pwm_stop_all(void)
{
    bsp_pwm_stop_all_motor();
    bsp_pwm_set_duty(PWM_CH_IG, 0);
    bsp_pwm_stop(PWM_CH_IG);
}
