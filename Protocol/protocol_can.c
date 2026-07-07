/**
  ******************************************************************************
  * @file    protocol_can.c
  * @brief   CAN protocol implementation
  ******************************************************************************
  */
#include "protocol_can.h"
#include "bsp_can.h"
#include "fault_config.h"
#include <string.h>

static proto_cmd_t cmd;
static proto_manual_t manual;
static uint32_t last_rx_tick;

void protocol_can_init(void)
{
    memset(&cmd, 0, sizeof(cmd));
    memset(&manual, 0, sizeof(manual));
    last_rx_tick = HAL_GetTick();
}

void protocol_can_process_msg(const can_rx_msg_t *msg)
{
    if (msg->type == CAN_MSG_CMD) {
        cmd.command = msg->data[0];
        cmd.pump_target = (uint16_t)((msg->data[3] << 8) | msg->data[2]);
        cmd.glow_target_mA = (uint16_t)((msg->data[5] << 8) | msg->data[4]);
        cmd.valid = true;
    } else {
        manual.flags = msg->data[0];
        manual.ig_duty = msg->data[1];
        manual.pump_duty = msg->data[2];
        manual.valid = true;
    }
    last_rx_tick = msg->timestamp;
}

void protocol_can_send_status(uint8_t st, uint32_t fl, uint8_t sub, uint8_t esc)
{
    uint8_t d[8] = {st, (uint8_t)(fl & 0xFF), (uint8_t)(fl >> 8), sub, esc};
    bsp_can_send(CAN_ID_STATUS, d, 8);
}

void protocol_can_send_sensors(int16_t t, uint16_t rpm, uint16_t ma)
{
    uint8_t d[8] = {(uint8_t)t, (uint8_t)(t >> 8), (uint8_t)rpm, (uint8_t)(rpm >> 8),
                    (uint8_t)ma, (uint8_t)(ma >> 8)};
    bsp_can_send(CAN_ID_SENSOR1, d, 8);
}

void protocol_can_send_esc(uint16_t a, uint16_t b, uint16_t c, uint8_t duty)
{
    uint8_t d[8] = {(uint8_t)a, (uint8_t)(a >> 8), (uint8_t)b, (uint8_t)(b >> 8),
                    (uint8_t)c, (uint8_t)(c >> 8), duty};
    bsp_can_send(CAN_ID_ESC_DATA, d, 8);
}

void protocol_can_send_fault(uint16_t fl, uint8_t st, uint8_t sub)
{
    uint8_t d[8] = {(uint8_t)fl, (uint8_t)(fl >> 8), st, sub};
    bsp_can_send(CAN_ID_FAULT, d, 8);
}

const proto_cmd_t* protocol_can_get_cmd(void) { return &cmd; }
const proto_manual_t* protocol_can_get_manual(void) { return &manual; }
bool protocol_can_is_timeout(void) { return ((HAL_GetTick() - last_rx_tick) > CAN_RX_TIMEOUT_MS); }
void protocol_can_reset_timeout(void) { last_rx_tick = HAL_GetTick(); }
