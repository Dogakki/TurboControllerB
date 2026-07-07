/**
  ******************************************************************************
  * @file    app_tasks.c
  * @brief   Task entry functions - thin wrappers calling modules/services
  ******************************************************************************
  */
#include "app_tasks.h"
#include "task_config.h"
#include "sub_enable.h"
#include "safety.h"
#include "app_main.h"
#include "motor.h"
#include "sensor.h"
#include "protocol_can.h"
#include "protocol_debug.h"
#include "service_log.h"
#include "service_param.h"
#include "service_watchdog.h"
#include "service_fault.h"
#include "rtos_queues.h"
#include "rtos_events.h"
#include "bsp_adc.h"
#include "bsp_power.h"
#include "pin_config.h"
#include "main.h"
#include "cmsis_os.h"

/* ---- SafetyTask: highest priority, 5ms ---- */
void Task_Safety(void *arg)
{
    (void)arg;
    for (;;) {
        sub_enable_check_and_protect();
        safety_check();
        watchdog_feed(WD_TASK_SAFETY);
        osDelay(PERIOD_SAFETY_MS);
    }
}

/* ---- ControlTask: state machine, 10ms ---- */
void Task_Control(void *arg)
{
    (void)arg;
    for (;;) {
        app_control_tick();
        watchdog_feed(WD_TASK_CONTROL);
        osDelay(PERIOD_CONTROL_MS);
    }
}

/* ---- MotorTask: motor duty update, 10ms ---- */
void Task_Motor(void *arg)
{
    (void)arg;
    for (;;) {
        /* Motor duty is set by ControlTask via motor_set_duty().
         * This task could handle ramping/soft-start in the future. */
        osDelay(PERIOD_MOTOR_MS);
    }
}

/* ---- CommTask: CAN RX/TX, 20ms ---- */
void Task_Comm(void *arg)
{
    (void)arg;
    for (;;) {
        /* Process CAN RX from queue */
        can_rx_msg_t msg;
        while (osMessageQueueGet(q_can_rx, &msg, NULL, 0) == osOK) {
            protocol_can_process_msg(&msg);
        }

        /* Send status */
        protocol_can_send_status(
            (uint8_t)app_get_state(),
            fault_get_all(),
            sub_enable_is_active() ? 1 : 0,
            0 /* esc_fault from drv8311 */
        );

        osDelay(PERIOD_COMM_MS);
    }
}

/* ---- SensorTask: ADC, temp, RPM, 50ms ---- */
void Task_Sensor(void *arg)
{
    (void)arg;
    bsp_adc_start_dma();
    for (;;) {
        sensor_read_all();
        osDelay(PERIOD_SENSOR_MS);
    }
}

/* ---- StorageTask: param save, 1s ---- */
void Task_Storage(void *arg)
{
    (void)arg;
    for (;;) {
        param_save();
        osDelay(PERIOD_STORAGE_MS);
    }
}

/* ---- DebugTask: debug CLI, 100ms ---- */
void Task_Debug(void *arg)
{
    (void)arg;
    for (;;) {
        protocol_debug_process();
        osDelay(PERIOD_DEBUG_MS);
    }
}

/* ---- LedTask: status LED, 500ms ---- */
void Task_Led(void *arg)
{
    (void)arg;
    for (;;) {
        /* Toggle LED or output status indicator */
        osDelay(PERIOD_LED_MS);
    }
}
