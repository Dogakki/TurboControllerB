/**
  ******************************************************************************
  * @file    protocol_can.c
  * @brief   CAN 通信协议实现
  ******************************************************************************
  */
#include "protocol_can.h"
#include "bsp_can.h"
#include "fault_config.h"
#include <string.h>

static can_cmd_t last_cmd;
static uint32_t last_rx_tick;

void protocol_can_init(void)
{
    memset(&last_cmd, 0, sizeof(last_cmd));
    last_rx_tick = HAL_GetTick();
}

/* ---- 解析A板指令帧 (0x100) ---- */
static void parse_cmd_frame(const uint8_t *d, uint32_t tick)
{
    last_cmd.target_rpm   = (uint16_t)((d[1] << 8) | d[0]);
    last_cmd.motor_en     = d[2];
    last_cmd.motor_duty   = d[3];
    last_cmd.igniter_en   = d[4];
    last_cmd.igniter_duty = d[5];
    last_cmd.valve_glow   = d[6];
    last_cmd.valve_main   = d[7];
    last_cmd.timestamp    = tick;
    last_cmd.valid        = true;
}

void protocol_can_process_msg(const can_rx_msg_t *msg)
{
    /* 根据实际CAN ID分发 (当前filter接收所有帧, 需检查ID) */
    /* 消息从ISR通过queue传入, ID需在ISR中记录或这里重新判断 */
    /* 简化处理: 只有0x100会进入queue (在ISR中过滤) */
    parse_cmd_frame(msg->data, msg->timestamp);
    last_rx_tick = msg->timestamp;
}

/* ---- 发送B板状态帧 (0x180) ---- */
void protocol_can_send_status(uint16_t rpm, int16_t temp_x10,
                              uint8_t motor_running, uint8_t motor_duty)
{
    uint8_t d[8] = {
        (uint8_t)(rpm & 0xFF),          /* Byte0: RPM低字节 */
        (uint8_t)((rpm >> 8) & 0xFF),   /* Byte1: RPM高字节 */
        (uint8_t)(temp_x10 & 0xFF),     /* Byte2: 温度低字节 */
        (uint8_t)((temp_x10 >> 8) & 0xFF), /* Byte3: 温度高字节 */
        motor_running,                   /* Byte4: 电机状态 */
        motor_duty,                      /* Byte5: 电机占空比 */
        0, 0                             /* Byte6-7: 保留 */
    };
    bsp_can_send(CAN_ID_B2A_STATUS, d, 8);
}

const can_cmd_t* protocol_can_get_cmd(void)
{
    return &last_cmd;
}

bool protocol_can_is_timeout(void)
{
    return ((HAL_GetTick() - last_rx_tick) > CAN_RX_TIMEOUT_MS);
}
