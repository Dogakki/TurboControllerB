/**
  ******************************************************************************
  * @file    max6675.h
  * @brief   MAX6675 K-type thermocouple IC driver
  ******************************************************************************
  */
#ifndef __MAX6675_H__
#define __MAX6675_H__

#include "main.h"
#include <stdbool.h>

void max6675_init(void);
bool max6675_read_temp(float *temp_c);
bool max6675_is_open_circuit(void);

#endif /* __MAX6675_H__ */
