/**
  ******************************************************************************
  * @file    sensor.c
  * @brief   Sensor aggregation module (mutex-protected)
  ******************************************************************************
  */
#include "sensor.h"
#include "bsp_adc.h"
#include "max6675.h"
#include "ina199.h"
#include "rpm.h"
#include "pin_config.h"
#include "rtos_mutex.h"
#include "main.h"
#include <string.h>

static sensor_data_t data;

void sensor_init(void) { memset(&data, 0, sizeof(data)); }

void sensor_read_all(void)
{
    bsp_adc_update_filter();
    sensor_data_t tmp;
    tmp.temp_valid = max6675_read_temp(&tmp.temp_c);
    tmp.rpm = rpm_get_value();
    tmp.glow_mA = (uint32_t)ina199_get_current_mA(bsp_adc_get_raw(ADC_IDX_GLOW));
    for (int i = 0; i < 4; i++) tmp.adc_raw[i] = bsp_adc_get_raw(i);
    tmp.tick = HAL_GetTick();

    if (osMutexAcquire(mtx_sensor_data, 5) == osOK) {
        memcpy(&data, &tmp, sizeof(data));
        osMutexRelease(mtx_sensor_data);
    }
}

bool sensor_get_data(sensor_data_t *out)
{
    if (!out) return false;
    if (osMutexAcquire(mtx_sensor_data, 5) == osOK) {
        memcpy(out, &data, sizeof(data));
        osMutexRelease(mtx_sensor_data);
        return true;
    }
    return false;
}
