/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "retarget.h"
#include "ws_drive_tft.h"
#include "menu.h"
#include "key.h"
#include "led.h"
#include "command.h"
#include "cJSON.h"
#include "meter.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
extern uint8_t sdMountFlag;
extern uint8_t keyVal;
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define KEY1_Pin GPIO_PIN_0
#define KEY1_GPIO_Port GPIOA
#define KEY1_EXTI_IRQn EXTI0_IRQn
#define KEY2_Pin GPIO_PIN_1
#define KEY2_GPIO_Port GPIOA
#define KEY2_EXTI_IRQn EXTI1_IRQn
#define SENOR_Pin GPIO_PIN_3
#define SENOR_GPIO_Port GPIOA
#define SENOR_EXTI_IRQn EXTI3_IRQn
#define KEY3_Pin GPIO_PIN_4
#define KEY3_GPIO_Port GPIOA
#define KEY3_EXTI_IRQn EXTI4_IRQn
#define LED_R_Pin GPIO_PIN_5
#define LED_R_GPIO_Port GPIOC
#define LED_B_Pin GPIO_PIN_2
#define LED_B_GPIO_Port GPIOB
#define LCD_BK_Pin GPIO_PIN_15
#define LCD_BK_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
