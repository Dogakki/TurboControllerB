/**
  ******************************************************************************
  * @file    app_main.c
  * @brief   主状态机 — 根据A板CAN指令控制执行器
  *
  *  A板指令 (0x100):
  *    target_rpm / motor_en / motor_duty / igniter_en / igniter_duty
  *    valve_glow / valve_main
  *
  *  B板状态:
  *    DISABLED  — SUB_EN=LOW, 所有执行器关闭
  *    IDLE      — SUB_EN=HIGH, 等待A板指令
  *    PREHEAT   — 点火器工作中
  *    RUNNING   — 电机+阀门工作中
  *    FAULT     — 故障, 所有执行器关闭
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

static void transition(system_state_t ns)
{
    if (ns != state) {
        log_msg("STATE", "%s -> %s", app_get_state_string(),
                (ns == STATE_DISABLED)  ? "DISABLED" :
                (ns == STATE_IDLE)      ? "IDLE" :
                (ns == STATE_PREHEAT)   ? "PREHEAT" :
                (ns == STATE_IGNITION)  ? "IGNITION" :
                (ns == STATE_PUMP_START)? "PUMP_START" :
                (ns == STATE_MAIN_FUEL) ? "MAIN_FUEL" :
                (ns == STATE_RUN)       ? "RUN" :
                (ns == STATE_SHUTDOWN)  ? "SHUTDOWN" : "FAULT");
        state = ns;
    }
}

system_state_t app_get_state(void) { return state; }

const char* app_get_state_string(void)
{
    switch (state) {
        case STATE_DISABLED:    return "DISABLED";
        case STATE_IDLE:        return "IDLE";
        case STATE_PREHEAT:     return "PREHEAT";
        case STATE_IGNITION:    return "IGNITION";
        case STATE_PUMP_START:  return "PUMP_START";
        case STATE_MAIN_FUEL:   return "MAIN_FUEL";
        case STATE_RUN:         return "RUN";
        case STATE_SHUTDOWN:    return "SHUTDOWN";
        case STATE_FAULT:       return "FAULT";
        default:                return "?";
    }
}

/**
  * @brief  根据A板CAN指令直接控制执行器
  *         A板通过 motor_en/igniter_en/valve_glow/valve_main 直接控制
  */
static void apply_can_commands(void)
{
    if (!sub_enable_is_active()) return;

    const can_cmd_t *cmd = protocol_can_get_cmd();
    if (!cmd->valid) return;

    /* ---- 电机控制 ---- */
    if (cmd->motor_en) {
        if (!motor_is_running()) motor_start();
        motor_set_duty(cmd->motor_duty);
    } else {
        if (motor_is_running()) motor_stop();
    }

    /* ---- 点火器控制 ---- */
    if (cmd->igniter_en) {
        bsp_pwm_start(PWM_CH_IG);
        ignition_set_duty(cmd->igniter_duty);
    } else {
        ignition_off();
    }

    /* ---- 点火阀 GLOW ---- */
    if (cmd->valve_glow) {
        valve_glow_on();
    } else {
        valve_glow_off();
    }

    /* ---- 主燃阀 MAIN ---- */
    if (cmd->valve_main) {
        valve_main_on();
    } else {
        valve_main_off();
    }
}

/**
  * @brief  根据当前执行器状态推导系统状态 (用于上报A板)
  */
static void update_state(void)
{
    if (!sub_enable_is_active()) {
        transition(STATE_DISABLED);
        return;
    }

    if (fault_has_any()) {
        transition(STATE_FAULT);
        return;
    }

    const can_cmd_t *cmd = protocol_can_get_cmd();
    if (!cmd->valid || (!cmd->motor_en && !cmd->igniter_en &&
                        !cmd->valve_glow && !cmd->valve_main)) {
        transition(STATE_IDLE);
        return;
    }

    /* 有点火器工作 → PREHEAT */
    if (cmd->igniter_en && !cmd->motor_en) {
        transition(STATE_PREHEAT);
        return;
    }

    /* 电机+阀门运行 → RUN */
    if (cmd->motor_en || cmd->valve_main) {
        transition(STATE_RUN);
        return;
    }

    /* 仅点火阀 → IGNITION */
    if (cmd->valve_glow) {
        transition(STATE_IGNITION);
        return;
    }

    transition(STATE_IDLE);
}

/**
  * @brief  ControlTask 每10ms调用一次
  */
void app_control_tick(void)
{
    /* SUB_EN 由 SafetyTask (更高优先级) 检查 */

    /* SUB_EN=LOW → 强制关闭所有执行器 */
    if (!sub_enable_is_active()) {
        safety_emergency_stop();
        transition(STATE_DISABLED);
        return;
    }

    /* 故障状态 → 保持关闭 */
    if (state == STATE_FAULT) {
        safety_emergency_stop();
        return;
    }

    /* 应用A板CAN指令 */
    apply_can_commands();

    /* 更新状态 */
    update_state();
}
