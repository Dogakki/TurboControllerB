/**
  ******************************************************************************
  * @file    board_config.h
  * @brief   Board-level hardware configuration
  ******************************************************************************
  */
#ifndef __BOARD_CONFIG_H__
#define __BOARD_CONFIG_H__

/* MCU */
#define BOARD_MCU_STM32F412CEU6
#define BOARD_FLASH_SIZE_KB     512
#define BOARD_RAM_SIZE_KB       256

/* Clock */
#define BOARD_SYSCLK_HZ        84000000UL
#define BOARD_HCLK_HZ           42000000UL
#define BOARD_PCLK1_HZ          21000000UL
#define BOARD_PCLK2_HZ          42000000UL
#define BOARD_APB1_TIM_HZ      42000000UL

/* PWM */
#define BOARD_TIM1_PWM_FREQ_HZ  20000   /* 20 kHz motor PWM */
#define BOARD_TIM1_PERIOD       2099    /* 42MHz / 20kHz - 1 */

/* CAN */
#define BOARD_CAN_BAUDRATE      500000  /* 500 kbps */

/* UART */
#define BOARD_DEBUG_BAUDRATE    115200

/* SPI */
#define BOARD_SPI_MODE          1       /* SPI Mode 1 for MAX6675 */

#endif /* __BOARD_CONFIG_H__ */
