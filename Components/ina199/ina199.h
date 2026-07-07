/**
  ******************************************************************************
  * @file    ina199.h
  * @brief   INA199 current sense amplifier driver
  ******************************************************************************
  */
#ifndef __INA199_H__
#define __INA199_H__

#include "main.h"
#include <stdint.h>
#include <stdbool.h>

float ina199_get_current_mA(uint16_t adc_raw);
bool ina199_is_overcurrent(uint16_t adc_raw, uint32_t threshold_mA);

#endif /* __INA199_H__ */
