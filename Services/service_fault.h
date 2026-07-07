/**
  ******************************************************************************
  * @file    service_fault.h
  * @brief   Fault flag register service
  ******************************************************************************
  */
#ifndef __SERVICE_FAULT_H__
#define __SERVICE_FAULT_H__

#include "main.h"
#include <stdint.h>
#include <stdbool.h>

void fault_init(void);
void fault_set(uint32_t id);
void fault_clear(uint32_t id);
void fault_clear_all(void);
uint32_t fault_get_all(void);
bool fault_has(uint32_t id);
bool fault_has_any(void);
const char* fault_get_string(void);

#endif /* __SERVICE_FAULT_H__ */
