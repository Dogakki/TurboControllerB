/**
  ******************************************************************************
  * @file    protocol_debug.h
  * @brief   Debug UART protocol
  ******************************************************************************
  */
#ifndef __PROTOCOL_DEBUG_H__
#define __PROTOCOL_DEBUG_H__

#include <stdint.h>

void protocol_debug_init(void);
void protocol_debug_process(void);

#endif /* __PROTOCOL_DEBUG_H__ */
