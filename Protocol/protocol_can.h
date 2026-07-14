/**
  ******************************************************************************
  * @file    protocol_can.h
  * @brief   CAN 通信协议
  *
  *  B板发送给A板 (0x180):
  *    Byte0-1: 转速 RPM (uint16_t, little-endian)
  *    Byte2-3: 热电偶温度 (int16_t, 0.1°C 单位, little-endian)
  *    Byte4:   启动电机状态 (0=停止, 1=运行)
  *    Byte5:   启动电机占空比 (0-100%)
  *    Byte6-7: 保留
  *
  *  A板发送给B板 (0x100):
  *    Byte0-1: 指定转速 RPM (uint16_t, little-endian)
  *    Byte2:   电机使能 (0=停止, 1=启动)
  *    Byte3:   电机占空比 (0-100%)
  *    Byte4:   点火器使能 (0=关, 1=开)
  *    Byte5:   点火器占空比 (0-100%)
  *    Byte6:   点火阀 GLOW (0=关, 1=开)
  *    Byte7:   主燃阀 MAIN (0=关, 1=开)
  ******************************************************************************
  */
#ifndef __PROTOCOL_CAN_H__
#define __PROTOCOL_CAN_H__

#include "main.h"
#include <stdint.h>
#include <stdbool.h>

/* ---- CAN 消息 ID ---- */
#define CAN_ID_B2A_STATUS   0x180   /* B板 → A板: 状态上报 */
#define CAN_ID_A2B_CMD      0x100   /* A板 → B板: 控制指令 */

/* ---- CAN RX 消息队列结构 ---- */
typedef struct {
    uint8_t data[8];
    uint32_t timestamp;
} can_rx_msg_t;

/* ---- A板指令 (接收解析后) ---- */
typedef struct {
    uint16_t target_rpm;        /* 指定转速 */
    uint8_t  motor_en;          /* 电机使能: 0=停止, 1=启动 */
    uint8_t  motor_duty;        /* 电机占空比: 0-100% */
    uint8_t  igniter_en;        /* 点火器使能: 0=关, 1=开 */
    uint8_t  igniter_duty;      /* 点火器占空比: 0-100% */
    uint8_t  valve_glow;        /* 点火阀: 0=关, 1=开 */
    uint8_t  valve_main;        /* 主燃阀: 0=关, 1=开 */
    uint32_t timestamp;         /* 接收时间戳 */
    bool     valid;             /* 数据有效标志 */
} can_cmd_t;

void protocol_can_init(void);

/* 处理从队列收到的CAN消息 (CommTask调用) */
void protocol_can_process_msg(const can_rx_msg_t *msg);

/* 发送B板状态给A板 (CommTask调用) */
void protocol_can_send_status(uint16_t rpm, int16_t temp_x10,
                              uint8_t motor_running, uint8_t motor_duty);

/* 获取最新A板指令 (ControlTask调用) */
const can_cmd_t* protocol_can_get_cmd(void);

/* CAN接收超时检测 */
bool protocol_can_is_timeout(void);

#endif /* __PROTOCOL_CAN_H__ */
