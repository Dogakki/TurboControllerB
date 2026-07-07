/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SUB_EN_Pin GPIO_PIN_13
#define SUB_EN_GPIO_Port GPIOC
#define ESC_FAULT_Pin GPIO_PIN_0
#define ESC_FAULT_GPIO_Port GPIOA
#define SPEED_Pin GPIO_PIN_1
#define SPEED_GPIO_Port GPIOA
#define IGNITION_Pin GPIO_PIN_2
#define IGNITION_GPIO_Port GPIOA
#define ADC_IN_A_Pin GPIO_PIN_3
#define ADC_IN_A_GPIO_Port GPIOA
#define ADC_IN_B_Pin GPIO_PIN_4
#define ADC_IN_B_GPIO_Port GPIOA
#define ADC_IN_C_Pin GPIO_PIN_5
#define ADC_IN_C_GPIO_Port GPIOA
#define ADC_IN_GLOW_Pin GPIO_PIN_6
#define ADC_IN_GLOW_GPIO_Port GPIOA
#define PWM_U_N_Pin GPIO_PIN_7
#define PWM_U_N_GPIO_Port GPIOA
#define PWM_V_N_Pin GPIO_PIN_0
#define PWM_V_N_GPIO_Port GPIOB
#define PWM_W_N_Pin GPIO_PIN_1
#define PWM_W_N_GPIO_Port GPIOB
#define MAIN_Pin GPIO_PIN_12
#define MAIN_GPIO_Port GPIOB
#define GLOW_Pin GPIO_PIN_13
#define GLOW_GPIO_Port GPIOB
#define PWN_U_Pin GPIO_PIN_8
#define PWN_U_GPIO_Port GPIOA
#define PWM_V_Pin GPIO_PIN_9
#define PWM_V_GPIO_Port GPIOA
#define PWM_W_Pin GPIO_PIN_10
#define PWM_W_GPIO_Port GPIOA
#define IG_PWM_Pin GPIO_PIN_11
#define IG_PWM_GPIO_Port GPIOA
#define B_TX_Pin GPIO_PIN_6
#define B_TX_GPIO_Port GPIOB
#define B_RX_Pin GPIO_PIN_7
#define B_RX_GPIO_Port GPIOB
#define ESC_EN_Pin GPIO_PIN_5
#define ESC_EN_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

#define PULSES_PER_REV          1       /* Speed sensor pulses per revolution */
#define GLOW_OVERCURRENT_MA     10000   /* Glow plug overcurrent threshold in mA */
#define OVERTEMP_LIMIT_C        800.0f  /* Over-temperature limit in degrees C */
#define CAN_RX_TIMEOUT_MS       1000    /* CAN RX timeout in ms */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
