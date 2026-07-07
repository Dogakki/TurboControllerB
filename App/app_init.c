/**
  ******************************************************************************
  * @file    app_init.c
  * @brief   Application init chain: BSP → Components → Services → Modules
  ******************************************************************************
  */
#include "app_init.h"

/* BSP */
#include "bsp.h"

/* Components */
#include "drv8311.h"
#include "max6675.h"

/* Services */
#include "service_log.h"
#include "service_fault.h"
#include "service_param.h"
#include "service_watchdog.h"

/* Modules */
#include "motor.h"
#include "valve.h"
#include "ignition.h"
#include "sensor.h"
#include "rpm.h"
#include "safety.h"
#include "sub_enable.h"

/* Protocol */
#include "protocol_can.h"
#include "protocol_debug.h"

void App_Init(void)
{
    /* 1. BSP - hardware abstraction */
    BSP_Init();

    /* 2. Components - chip drivers */
    drv8311_init();
    max6675_init();

    /* 3. Services - system services */
    log_init();
    fault_init();
    param_init();
    watchdog_init();

    /* 4. Protocol */
    protocol_can_init();
    protocol_debug_init();

    /* 5. Modules - application logic */
    motor_init();
    valve_init();
    ignition_init();
    sensor_init();
    rpm_init();
    sub_enable_init();
    safety_init();

    /* 6. Log boot */
    log_boot();
}
