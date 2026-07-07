/**
  ******************************************************************************
  * @file    bsp_adc.h
  * @brief   ADC BSP wrappers
  ******************************************************************************
  */
#ifndef __BSP_ADC_H__
#define __BSP_ADC_H__

#include "main.h"
#include "pin_config.h"
#include <stdint.h>

void bsp_adc_start_dma(void);
uint16_t bsp_adc_get_raw(uint8_t idx);
void bsp_adc_update_filter(void);

#endif /* __BSP_ADC_H__ */
