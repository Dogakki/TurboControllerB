/**
  ******************************************************************************
  * @file    service_log.c
  * @brief   Tagged UART logging service
  ******************************************************************************
  */
#include "service_log.h"
#include "bsp_uart.h"
#include "version.h"
#include <stdio.h>
#include <stdarg.h>

static char buf[128];

void log_init(void) { /* UART already init */ }

void log_msg(const char *tag, const char *fmt, ...)
{
    int n = snprintf(buf, sizeof(buf), "[%s] ", tag);
    va_list args;
    va_start(args, fmt);
    n += vsnprintf(buf + n, sizeof(buf) - n, fmt, args);
    va_end(args);
    if (n > 0 && n < (int)sizeof(buf) - 2) {
        buf[n++] = '\r'; buf[n++] = '\n';
        bsp_uart_transmit((uint8_t *)buf, (uint16_t)n);
    }
}

void log_boot(void)
{
    log_msg("BOOT", "%s v%s %s %s", FW_PROJECT_NAME, FW_VERSION_STRING, FW_BUILD_DATE, FW_BUILD_TIME);
}
