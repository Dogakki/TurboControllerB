/**
  ******************************************************************************
  * @file    bsp_can.c
  * @brief   CAN BSP wrappers
  ******************************************************************************
  */
#include "bsp_can.h"
#include "can.h"

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
