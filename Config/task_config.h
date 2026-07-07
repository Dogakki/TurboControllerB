/**
  ******************************************************************************
  * @file    task_config.h
  * @brief   FreeRTOS task names, stack sizes, priorities, and periods
  ******************************************************************************
  */
#ifndef __TASK_CONFIG_H__
#define __TASK_CONFIG_H__

#include "cmsis_os.h"

/* ---- Task Priorities (higher number = higher priority) ---- */
#define PRIO_SAFETY             osPriorityRealtime          /* 6 - highest */
#define PRIO_CONTROL            osPriorityAboveNormal       /* 4 */
#define PRIO_MOTOR              osPriorityAboveNormal       /* 4 */
#define PRIO_COMM               osPriorityNormal            /* 3 */
#define PRIO_SENSOR             osPriorityNormal            /* 3 */
#define PRIO_STORAGE            osPriorityBelowNormal       /* 2 */
#define PRIO_DEBUG              osPriorityLow               /* 1 */
#define PRIO_LED                osPriorityLow               /* 1 */

/* ---- Task Stack Sizes (in bytes, 4 bytes per word) ---- */
#define STACK_SAFETY            (256 * 4)   /* 1024 B */
#define STACK_CONTROL           (512 * 4)   /* 2048 B */
#define STACK_MOTOR             (256 * 4)   /* 1024 B */
#define STACK_COMM              (256 * 4)   /* 1024 B */
#define STACK_SENSOR            (256 * 4)   /* 1024 B */
#define STACK_STORAGE           (256 * 4)   /* 1024 B */
#define STACK_DEBUG             (256 * 4)   /* 1024 B */
#define STACK_LED               (128 * 4)   /*  512 B */

/* ---- Task Periods (ms) ---- */
#define PERIOD_SAFETY_MS        5       /* 5ms - fastest for safety */
#define PERIOD_CONTROL_MS       10      /* 10ms control loop */
#define PERIOD_MOTOR_MS         10      /* 10ms motor update */
#define PERIOD_COMM_MS          20      /* 20ms comm cycle */
#define PERIOD_SENSOR_MS        50      /* 50ms sensor read */
#define PERIOD_STORAGE_MS       1000    /* 1s storage sync */
#define PERIOD_DEBUG_MS         100     /* 100ms debug output */
#define PERIOD_LED_MS           500     /* 500ms LED blink */

/* ---- Task Names ---- */
#define NAME_SAFETY             "Safety"
#define NAME_CONTROL            "Control"
#define NAME_MOTOR              "Motor"
#define NAME_COMM               "Comm"
#define NAME_SENSOR             "Sensor"
#define NAME_STORAGE            "Storage"
#define NAME_DEBUG              "Debug"
#define NAME_LED                "Led"

#endif /* __TASK_CONFIG_H__ */
