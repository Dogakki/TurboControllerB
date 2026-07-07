/**
  ******************************************************************************
  * @file    bsp_adc.c
  * @brief   ADC BSP wrappers with DMA and simple averaging filter
  ******************************************************************************
  */
#include "bsp_adc.h"
#include "adc.h"
#include <stdbool.h>

static volatile uint16_t dma_buf[ADC_NUM_CHANNELS];
static uint16_t filtered[ADC_NUM_CHANNELS];
#define FILT_DEPTH 8
static uint16_t filt_buf[ADC_NUM_CHANNELS][FILT_DEPTH];
static uint8_t filt_idx;
static uint8_t filt_count;
static bool started;

void bsp_adc_start_dma(void)
{
    if (!started) {
        HAL_ADC_Start_DMA(&hadc1, (uint32_t *)dma_buf, ADC_NUM_CHANNELS);
        started = true;
    }
}

void bsp_adc_update_filter(void)
{
    for (int i = 0; i < ADC_NUM_CHANNELS; i++)
        filt_buf[i][filt_idx] = dma_buf[i];
    filt_idx = (filt_idx + 1) % FILT_DEPTH;
    if (filt_count < FILT_DEPTH) filt_count++;
    uint8_t n = filt_count ? filt_count : 1;
    for (int i = 0; i < ADC_NUM_CHANNELS; i++) {
        uint32_t sum = 0;
        for (int j = 0; j < n; j++) sum += filt_buf[i][j];
        filtered[i] = (uint16_t)(sum / n);
    }
}

uint16_t bsp_adc_get_raw(uint8_t idx)
{
    return (idx < ADC_NUM_CHANNELS) ? filtered[idx] : 0;
}
