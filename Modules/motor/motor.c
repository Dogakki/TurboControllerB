/**
  ******************************************************************************
  * @file    motor.c
  * @brief   Motor/pump control module (uses drv8311 + bsp_pwm)
  ******************************************************************************
  */
#include "motor.h"
#include "drv8311.h"
#include "bsp_pwm.h"
#include "pin_config.h"

static uint8_t duty;
static bool running;

void motor_init(void) { duty = 0; running = false; }

void motor_start(void)
{
    drv8311_enable();
    bsp_pwm_start_all_motor();
    running = true;
}

void motor_stop(void)
{
    bsp_pwm_stop_all_motor();
    drv8311_disable();
    duty = 0;
    running = false;
}

void motor_set_duty(uint8_t pct)
{
    if (pct > 100) pct = 100;
    duty = pct;
    bsp_pwm_set_duty(PWM_CH_U, pct);
    bsp_pwm_set_duty(PWM_CH_V, pct);
    bsp_pwm_set_duty(PWM_CH_W, pct);
}

uint8_t motor_get_duty(void) { return duty; }
bool motor_is_running(void) { return running; }
