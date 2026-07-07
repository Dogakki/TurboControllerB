/**
  ******************************************************************************
  * @file    pin_config.h
  * @brief   All GPIO pin definitions and helper macros
  ******************************************************************************
  */
#ifndef __PIN_CONFIG_H__
#define __PIN_CONFIG_H__

#include "main.h"

/* ---- Inputs ---- */
#define PIN_SUB_EN_PORT         GPIOC
#define PIN_SUB_EN_PIN          GPIO_PIN_13

#define PIN_ESC_FAULT_PORT      GPIOA
#define PIN_ESC_FAULT_PIN       GPIO_PIN_0

#define PIN_SPEED_PORT          GPIOA
#define PIN_SPEED_PIN           GPIO_PIN_1

/* ---- Outputs ---- */
#define PIN_IGNITION_PORT       GPIOA
#define PIN_IGNITION_PIN        GPIO_PIN_2

#define PIN_ESC_EN_PORT         GPIOB
#define PIN_ESC_EN_PIN          GPIO_PIN_5

#define PIN_MAIN_VALVE_PORT     GPIOB
#define PIN_MAIN_VALVE_PIN      GPIO_PIN_12

#define PIN_GLOW_VALVE_PORT     GPIOB
#define PIN_GLOW_VALVE_PIN      GPIO_PIN_13

/* ---- ADC Channels ---- */
#define PIN_ADC_IN_A_PORT       GPIOA
#define PIN_ADC_IN_A_PIN        GPIO_PIN_3

#define PIN_ADC_IN_B_PORT       GPIOA
#define PIN_ADC_IN_B_PIN        GPIO_PIN_4

#define PIN_ADC_IN_C_PORT       GPIOA
#define PIN_ADC_IN_C_PIN        GPIO_PIN_5

#define PIN_ADC_IN_GLOW_PORT    GPIOA
#define PIN_ADC_IN_GLOW_PIN     GPIO_PIN_6

/* ---- PWM (TIM1) ---- */
#define PIN_PWM_U_PORT          GPIOA
#define PIN_PWM_U_PIN           GPIO_PIN_8

#define PIN_PWM_V_PORT          GPIOA
#define PIN_PWM_V_PIN           GPIO_PIN_9

#define PIN_PWM_W_PORT          GPIOA
#define PIN_PWM_W_PIN           GPIO_PIN_10

#define PIN_IG_PWM_PORT         GPIOA
#define PIN_IG_PWM_PIN          GPIO_PIN_11

#define PIN_PWM_U_N_PORT        GPIOA
#define PIN_PWM_U_N_PIN         GPIO_PIN_7

#define PIN_PWM_V_N_PORT        GPIOB
#define PIN_PWM_V_N_PIN         GPIO_PIN_0

#define PIN_PWM_W_N_PORT        GPIOB
#define PIN_PWM_W_N_PIN         GPIO_PIN_1

/* ---- SPI (MAX6675) ---- */
#define PIN_SPI1_NSS_PORT       GPIOA
#define PIN_SPI1_NSS_PIN        GPIO_PIN_15

#define PIN_SPI1_SCK_PORT       GPIOB
#define PIN_SPI1_SCK_PIN        GPIO_PIN_3

#define PIN_SPI1_MISO_PORT      GPIOB
#define PIN_SPI1_MISO_PIN       GPIO_PIN_4

/* ---- CAN ---- */
#define PIN_CAN1_RX_PORT        GPIOB
#define PIN_CAN1_RX_PIN         GPIO_PIN_8

#define PIN_CAN1_TX_PORT        GPIOB
#define PIN_CAN1_TX_PIN         GPIO_PIN_9

/* ---- UART Debug ---- */
#define PIN_DBG_TX_PORT         GPIOB
#define PIN_DBG_TX_PIN          GPIO_PIN_6

#define PIN_DBG_RX_PORT         GPIOB
#define PIN_DBG_RX_PIN          GPIO_PIN_7

/* ---- ADC channel indices (DMA buffer order) ---- */
#define ADC_IDX_PHASE_A         0
#define ADC_IDX_PHASE_B         1
#define ADC_IDX_PHASE_C         2
#define ADC_IDX_GLOW            3
#define ADC_NUM_CHANNELS        4

/* ---- TIM1 PWM channels ---- */
#define PWM_CH_U                TIM_CHANNEL_1
#define PWM_CH_V                TIM_CHANNEL_2
#define PWM_CH_W                TIM_CHANNEL_3
#define PWM_CH_IG               TIM_CHANNEL_4

/* ---- TIM2 Input Capture ---- */
#define IC_CH_SPEED             TIM_CHANNEL_2

#endif /* __PIN_CONFIG_H__ */
