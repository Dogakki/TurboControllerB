/**
  ******************************************************************************
  * @file    sub_enable.c
  * @brief   SUB_EN monitoring - highest priority safety check
  *         When SUB_EN goes LOW, all actuators must be immediately disabled.
  ******************************************************************************
  */
#include "sub_enable.h"
#include "bsp_gpio.h"
#include "bsp_power.h"
#include "service_fault.h"
#include "fault_config.h"

static bool was_active = true;

void sub_enable_init(void) { was_active = true; }

bool sub_enable_is_active(void) { return bsp_sub_en_read(); }

void sub_enable_check_and_protect(void)
{
    bool active = bsp_sub_en_read();
    if (!active) {
        /* SUB_EN = LOW: force all outputs off immediately */
        bsp_force_all_outputs_off();
        fault_set(FAULT_ID_SUB_DISABLED);
    } else {
        fault_clear(FAULT_ID_SUB_DISABLED);
    }
    was_active = active;
}
