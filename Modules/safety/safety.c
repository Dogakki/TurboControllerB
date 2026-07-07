/**
  ******************************************************************************
  * @file    safety.c
  * @brief   Safety module - fault detection and emergency shutdown
  ******************************************************************************
  */
#include "safety.h"
#include "bsp_power.h"
#include "bsp_gpio.h"
#include "motor.h"
#include "ignition.h"
#include "valve.h"
#include "service_fault.h"
#include "service_watchdog.h"
#include "drv8311.h"
#include "sensor.h"
#include "protocol_can.h"
#include "fault_config.h"

void safety_init(void) { /* Already inited by sub-modules */ }

void safety_emergency_stop(void)
{
    motor_stop();
    ignition_off();
    valve_all_off();
}

void safety_check(void)
{
    /* ESC fault */
    if (drv8311_is_fault() && motor_is_running()) {
        motor_stop();
        fault_set(FAULT_ID_ESC);
    }

    /* Glow overcurrent */
    if (ignition_is_overcurrent() && ignition_get_duty() > 0) {
        ignition_off();
        fault_set(FAULT_ID_GLOW_OVERCURRENT);
    }

    /* Over-temperature */
    sensor_data_t sd;
    if (sensor_get_data(&sd)) {
        if (sd.temp_valid && sd.temp_c > OVERTEMP_LIMIT_C) {
            safety_emergency_stop();
            fault_set(FAULT_ID_OVERTEMP);
        }
        if (!sd.temp_valid) fault_set(FAULT_ID_THERMOCOUPLE_OPEN);
        else fault_clear(FAULT_ID_THERMOCOUPLE_OPEN);
    }

    /* CAN timeout */
    if (protocol_can_is_timeout()) {
        fault_set(FAULT_ID_CAN_TIMEOUT);
    }
}

bool safety_can_start(void)
{
    return (!fault_has(FAULT_ID_SUB_DISABLED) &&
            !fault_has(FAULT_ID_ESC) &&
            !fault_has(FAULT_ID_OVERTEMP));
}
