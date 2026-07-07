/**
  ******************************************************************************
  * @file    ignition.c
  * @brief   Glow plug ignition control module
  ******************************************************************************
  */
#include "ignition.h"
#include "bsp_pwm.h"
#include "bsp_adc.h"
#include "ina199.h"
#include "pin_config.h"
#include "fault_config.h"

static uint8_t duty;

void ignition_init(void) { duty = 0; }

void ignition_set_duty(uint8_t pct)
{
    if (pct > 100) pct = 100;
    duty = pct;
    bsp_pwm_set_duty(PWM_CH_IG, pct);
}

void ignition_off(void) { duty = 0; bsp_pwm_set_duty(PWM_CH_IG, 0); }
uint8_t ignition_get_duty(void) { return duty; }

float ignition_get_current_mA(void)
{
    return ina199_get_current_mA(bsp_adc_get_raw(ADC_IDX_GLOW));
}

bool ignition_is_overcurrent(void)
{
    return ina199_is_overcurrent(bsp_adc_get_raw(ADC_IDX_GLOW), GLOW_OVERCURRENT_MA);
}
