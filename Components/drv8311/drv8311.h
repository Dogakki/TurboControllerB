/**
  ******************************************************************************
  * @file    drv8311.h
  * @brief   DRV8311 ESC chip driver
  ******************************************************************************
  */
#ifndef __DRV8311_H__
#define __DRV8311_H__

#include "main.h"
#include <stdbool.h>

void drv8311_init(void);
void drv8311_enable(void);
void drv8311_disable(void);
bool drv8311_is_fault(void);

#endif /* __DRV8311_H__ */
