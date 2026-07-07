/**
  ******************************************************************************
  * @file    protocol_can.h
  * @brief   CAN protocol packing/unpacking and command dispatch
  ******************************************************************************
  */
#ifndef __PROTOCOL_CAN_H__
#define __PROTOCOL_CAN_H__

#include "main.h"
#include <stdint.h>
#include <stdbool.h>

/* Message IDs */
#define CAN_ID_CMD          0x100
#define CAN_ID_MANUAL       0x101
#define CAN_ID_STATUS       0x180
#define CAN_ID_SENSOR1      0x181
#define CAN_ID_ESC_DATA     0x182
#define CAN_ID_FAULT        0x1F0

/* Command bytes */
#define CMD_STOP                0x00
#define CMD_START_SEQUENCE      0x01
#define CMD_PREHEAT_ONLY        0x02
#define CMD_IGNITION_ENABLE     0x03
#define CMD_PUMP_ENABLE         0x04
#define CMD_MAIN_VALVE_ENABLE   0x05
#define CMD_CLEAR_FAULT         0x06

/* Manual flags */
#define MANUAL_IG_PWM_EN        (1U << 0)
#define MANUAL_GLOW_VALVE_EN    (1U << 1)
#define MANUAL_MAIN_VALVE_EN    (1U << 2)
#define MANUAL_ESC_EN           (1U << 3)

/* CAN RX message for queue */
typedef enum { CAN_MSG_CMD = 0, CAN_MSG_MANUAL } can_msg_type_t;
typedef struct {
    can_msg_type_t type;
    uint8_t data[8];
    uint32_t timestamp;
} can_rx_msg_t;

/* Parsed command */
typedef struct {
    uint8_t command;
    uint16_t pump_target;
    uint16_t glow_target_mA;
    bool valid;
} proto_cmd_t;

typedef struct {
    uint8_t flags;
    uint8_t ig_duty;
    uint8_t pump_duty;
    bool valid;
} proto_manual_t;

void protocol_can_init(void);
void protocol_can_process_msg(const can_rx_msg_t *msg);
void protocol_can_send_status(uint8_t state, uint32_t faults, uint8_t sub_en, uint8_t esc_fault);
void protocol_can_send_sensors(int16_t temp_raw, uint16_t rpm, uint16_t glow_mA);
void protocol_can_send_esc(uint16_t soa, uint16_t sob, uint16_t soc, uint8_t duty);
void protocol_can_send_fault(uint16_t faults, uint8_t state, uint8_t sub_en);
const proto_cmd_t* protocol_can_get_cmd(void);
const proto_manual_t* protocol_can_get_manual(void);
bool protocol_can_is_timeout(void);
void protocol_can_reset_timeout(void);

#endif /* __PROTOCOL_CAN_H__ */
