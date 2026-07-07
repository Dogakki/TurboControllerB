/**
  ******************************************************************************
  * @file    sensor.h
  * @brief   Sensor aggregation module
  ******************************************************************************
  */
#ifndef __SENSOR_H__
#define __SENSOR_H__

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    float    temp_c;
    bool     temp_valid;
    uint32_t rpm;
    uint32_t glow_mA;
    uint16_t adc_raw[4];
    uint32_t tick;
} sensor_data_t;

void sensor_init(void);
void sensor_read_all(void);
bool sensor_get_data(sensor_data_t *out);

#endif /* __SENSOR_H__ */
