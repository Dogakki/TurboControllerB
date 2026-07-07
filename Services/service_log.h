/**
  ******************************************************************************
  * @file    service_log.h
  * @brief   Tagged UART logging service
  ******************************************************************************
  */
#ifndef __SERVICE_LOG_H__
#define __SERVICE_LOG_H__

#include <stdint.h>

void log_init(void);
void log_msg(const char *tag, const char *fmt, ...);
void log_boot(void);

#endif /* __SERVICE_LOG_H__ */
