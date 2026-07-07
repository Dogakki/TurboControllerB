/**
  ******************************************************************************
  * @file    app_main.c
  * @brief   Application main - state machine
  ******************************************************************************
  */
#include "app_main.h"
#include "sub_enable.h"
#include "safety.h"
#include "motor.h"
#include "valve.h"
#include "ignition.h"
#include "protocol_can.h"
#include "service_fault.h"
#include "service_log.h"
#include "bsp_pwm.h"
#include "pin_config.h"
#include "fault_config.h"
#include "main.h"

static system_state_t state = STATE_DISABLED;
static uint32_t preheat_start;

static void transition(system_state_t ns)
{
    if (ns != state) {
        log_msg("STATE", "%s -> %s", app_get_state_string(),
                (ns == STATE_DISABLED) ? "DISABLED" :
                (ns == STATE_IDLE) ? "IDLE" :
                (ns == STATE_PREHEAT) ? "PREHEAT" :
                (ns == STATE_IGNITION) ? "IGNITION" :
                (ns == STATE_PUMP_START) ? "PUMP_START" :
                (ns == STATE_MAIN_FUEL) ? "MAIN_FUEL" :
                (ns == STATE_RUN) ? "RUN" :
                (ns == STATE_SHUTDOWN) ? "SHUTDOWN" : "FAULT");
        state = ns;
    }
}

system_state_t app_get_state(void) { return state; }

const char* app_get_state_string(void)
{
    switch (state) {
        case STATE_DISABLED: return "DISABLED";
        case STATE_IDLE: return "IDLE";
        case STATE_PREHEAT: return "PREHEAT";
        case STATE_IGNITION: return "IGNITION";
        case STATE_PUMP_START: return "PUMP_START";
        case STATE_MAIN_FUEL: return "MAIN_FUEL";
        case STATE_RUN: return "RUN";
        case STATE_SHUTDOWN: return "SHUTDOWN";
        case STATE_FAULT: return "FAULT";
        default: return "?";
    }
}

static void process_commands(void)
{
    if (!sub_enable_is_active()) return;

    const proto_cmd_t *c = protocol_can_get_cmd();
    if (!c->valid) return;

    switch (c->command) {
        case CMD_STOP:
            safety_emergency_stop();
            transition(STATE_IDLE);
            break;
        case CMD_START_SEQUENCE:
            if (state == STATE_IDLE) transition(STATE_PREHEAT);
            break;
        case CMD_IGNITION_ENABLE:
            if (state == STATE_PREHEAT) transition(STATE_IGNITION);
            break;
        case CMD_PUMP_ENABLE:
            if (state == STATE_IGNITION) transition(STATE_PUMP_START);
            break;
        case CMD_MAIN_VALVE_ENABLE:
            if (state == STATE_PUMP_START || state == STATE_RUN)
                transition(STATE_MAIN_FUEL);
            break;
        case CMD_CLEAR_FAULT:
            if (state == STATE_FAULT) {
                fault_clear_all();
                safety_emergency_stop();
                transition(STATE_IDLE);
            }
            break;
        default: break;
    }
}

static void run_state(void)
{
    switch (state) {
        case STATE_DISABLED:
        case STATE_IDLE:
            break;
        case STATE_PREHEAT:
            if (preheat_start == 0) {
                preheat_start = HAL_GetTick();
                bsp_pwm_start(PWM_CH_IG);
                ignition_set_duty(30);
            }
            if ((HAL_GetTick() - preheat_start) > PREHEAT_TIMEOUT_MS) {
                ignition_off();
                fault_set(FAULT_ID_SPEED_LOST);
                transition(STATE_FAULT);
            }
            break;
        case STATE_IGNITION:
            valve_glow_on();
            break;
        case STATE_PUMP_START:
            motor_start();
            motor_set_duty(10);
            valve_glow_on();
            break;
        case STATE_MAIN_FUEL:
            valve_main_on();
            transition(STATE_RUN);
            break;
        case STATE_RUN: {
            const proto_cmd_t *c = protocol_can_get_cmd();
            if (c->valid) motor_set_duty((uint8_t)(c->pump_target & 0xFF));
            break;
        }
        case STATE_SHUTDOWN:
            valve_main_off();
            motor_stop();
            valve_glow_off();
            ignition_off();
            transition(STATE_IDLE);
            break;
        case STATE_FAULT:
            safety_emergency_stop();
            break;
    }
}

void app_control_tick(void)
{
    /* SUB_EN check is done by SafetyTask (higher priority) */

    /* If SUB_EN goes low, force DISABLED */
    if (!sub_enable_is_active() && state != STATE_DISABLED) {
        safety_emergency_stop();
        transition(STATE_DISABLED);
    }

    process_commands();
    run_state();
}
