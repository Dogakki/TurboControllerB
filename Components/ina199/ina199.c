/**
  ******************************************************************************
  * @file    ina199.c
  * @brief   INA199 current sense amplifier driver
  *         Vout = I * Rshunt * Gain = I * 0.005 * 50 = I * 0.25
  *         I = Vout / 0.25 = Vout * 4
  *         Vadc = raw * 3.3 / 4095
  *         I_mA = Vadc * 4 * 1000 = raw * 3.3 / 4095 * 4000
  ******************************************************************************
  */
#include "ina199.h"
#include "fault_config.h"

float ina199_get_current_mA(uint16_t adc_raw)
{
    float v = (float)adc_raw * INA199_VREF / 4095.0f;
    return v / (INA199_RSHUNT_OHM * INA199_GAIN) * 1000.0f;
}

bool ina199_is_overcurrent(uint16_t adc_raw, uint32_t threshold_mA)
{
    return (ina199_get_current_mA(adc_raw) > (float)threshold_mA);
}
