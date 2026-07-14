/**
  ******************************************************************************
  * @file    bsp_can.c
  * @brief   CAN BSP wrappers + ISR callback
  ******************************************************************************
  */
#include "bsp_can.h"
#include "can.h"
#include "protocol_can.h"
#include "rtos_queues.h"
#include <string.h>

void bsp_can_start(void) { HAL_CAN_Start(&hcan1); }

void bsp_can_config_filter(void)
{
    CAN_FilterTypeDef f = {0};
    f.FilterBank = 0;
    f.FilterMode = CAN_FILTERMODE_IDMASK;
    f.FilterScale = CAN_FILTERSCALE_32BIT;
    f.FilterActivation = ENABLE;
    f.FilterFIFOAssignment = CAN_RX_FIFO0;
    HAL_CAN_ConfigFilter(&hcan1, &f);
}

void bsp_can_activate_rx_irq(void)
{
    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
}

bool bsp_can_send(uint32_t id, const uint8_t *data, uint8_t len)
{
    CAN_TxHeaderTypeDef h = {0};
    uint32_t mailbox;
    h.StdId = id;
    h.IDE = CAN_ID_STD;
    h.RTR = CAN_RTR_DATA;
    h.DLC = len;
    return (HAL_CAN_AddTxMessage(&hcan1, &h, (uint8_t *)data, &mailbox) == HAL_OK);
}

bool bsp_can_receive(uint32_t *id, uint8_t *data, uint8_t *len)
{
    CAN_RxHeaderTypeDef h;
    if (HAL_CAN_GetRxFifoFillLevel(&hcan1, CAN_RX_FIFO0) == 0) return false;
    if (HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &h, data) != HAL_OK) return false;
    if (id) *id = h.StdId;
    if (len) *len = h.DLC;
    return true;
}

/**
  * @brief  HAL CAN RX FIFO0 中断回调 (ISR上下文)
  *         只接收A板指令帧 (0x100), 通过队列传给CommTask
  */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    if (hcan->Instance != CAN1) return;

    CAN_RxHeaderTypeDef hdr;
    uint8_t data[8];

    if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &hdr, data) != HAL_OK) return;
    if (hdr.IDE != CAN_ID_STD) return;

    /* 只接收A板指令帧 0x100 */
    if (hdr.StdId != CAN_ID_A2B_CMD) return;

    can_rx_msg_t msg;
    memcpy(msg.data, data, 8);
    msg.timestamp = HAL_GetTick();

    /* 非阻塞写入队列 */
    if (q_can_rx != NULL) {
        osMessageQueuePut(q_can_rx, &msg, 0, 0);
    }
}
