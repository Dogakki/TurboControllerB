/**
  ******************************************************************************
  * @file    service_fault.c
  * @brief   Fault flag register service
  ******************************************************************************
  */
#include "service_fault.h"
#include "fault_config.h"
#include <string.h>

static uint32_t flags;

void fault_init(void) { flags = 0; }
void fault_set(uint32_t id)   { flags |= id; }
void fault_clear(uint32_t id) { flags &= ~id; }
void fault_clear_all(void)    { flags = 0; }
uint32_t fault_get_all(void)  { return flags; }
bool fault_has(uint32_t id)   { return (flags & id) != 0; }
bool fault_has_any(void)      { return flags != 0; }

const char* fault_get_string(void)
{
    static char buf[64]; buf[0] = '\0';
    if (flags & FAULT_ID_SUB_DISABLED)      strcat(buf, "SUB_DIS ");
    if (flags & FAULT_ID_ESC)               strcat(buf, "ESC ");
    if (flags & FAULT_ID_GLOW_OVERCURRENT)  strcat(buf, "GLOW_OC ");
    if (flags & FAULT_ID_THERMOCOUPLE_OPEN) strcat(buf, "TC_OPEN ");
    if (flags & FAULT_ID_OVERTEMP)          strcat(buf, "OTEMP ");
    if (flags & FAULT_ID_SPEED_LOST)        strcat(buf, "SPD ");
    if (flags & FAULT_ID_CAN_TIMEOUT)       strcat(buf, "CAN ");
    return buf;
}
