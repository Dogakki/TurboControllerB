/**
  ******************************************************************************
  * @file    rpm.h
  * @brief   Speed sensor RPM module
  ******************************************************************************
  */
#ifndef __RPM_H__
#define __RPM_H__

#include <stdint.h>
#include <stdbool.h>

void rpm_init(void);
uint32_t rpm_get_value(void);
bool rpm_is_valid(void);
void rpm_ic_callback(uint32_t capture_val);

#endif /* __RPM_H__ */
