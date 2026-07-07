/**
  ******************************************************************************
  * @file    rtos_tasks.c
  * @brief   RTOS task creation - 8 tasks
  ******************************************************************************
  */
#include "rtos_tasks.h"
#include "task_config.h"
#include "app_tasks.h"
#include "cmsis_os.h"

osThreadId_t task_safety, task_control, task_motor;
osThreadId_t task_comm, task_sensor, task_storage;
osThreadId_t task_debug, task_led;

static const osThreadAttr_t attr_safety  = { .name = NAME_SAFETY,  .stack_size = STACK_SAFETY,  .priority = PRIO_SAFETY  };
static const osThreadAttr_t attr_control = { .name = NAME_CONTROL, .stack_size = STACK_CONTROL, .priority = PRIO_CONTROL };
static const osThreadAttr_t attr_motor   = { .name = NAME_MOTOR,   .stack_size = STACK_MOTOR,   .priority = PRIO_MOTOR   };
static const osThreadAttr_t attr_comm    = { .name = NAME_COMM,    .stack_size = STACK_COMM,    .priority = PRIO_COMM    };
static const osThreadAttr_t attr_sensor  = { .name = NAME_SENSOR,  .stack_size = STACK_SENSOR,  .priority = PRIO_SENSOR  };
static const osThreadAttr_t attr_storage = { .name = NAME_STORAGE, .stack_size = STACK_STORAGE, .priority = PRIO_STORAGE };
static const osThreadAttr_t attr_debug   = { .name = NAME_DEBUG,   .stack_size = STACK_DEBUG,   .priority = PRIO_DEBUG   };
static const osThreadAttr_t attr_led     = { .name = NAME_LED,     .stack_size = STACK_LED,     .priority = PRIO_LED     };

void rtos_tasks_create(void)
{
    task_safety  = osThreadNew(Task_Safety,  NULL, &attr_safety);
    task_control = osThreadNew(Task_Control, NULL, &attr_control);
    task_motor   = osThreadNew(Task_Motor,   NULL, &attr_motor);
    task_comm    = osThreadNew(Task_Comm,    NULL, &attr_comm);
    task_sensor  = osThreadNew(Task_Sensor,  NULL, &attr_sensor);
    task_storage = osThreadNew(Task_Storage, NULL, &attr_storage);
    task_debug   = osThreadNew(Task_Debug,   NULL, &attr_debug);
    task_led     = osThreadNew(Task_Led,     NULL, &attr_led);
}
