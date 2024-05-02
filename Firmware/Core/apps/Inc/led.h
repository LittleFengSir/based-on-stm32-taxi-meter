/**
  ******************************************************************************
  * @文件名           : led.h
  * @作 者           : 小冯Sir
  * @brief          : None
  * @注意            : None
  * @日 期           : 24-5-2
  ******************************************************************************
  */
#ifndef APPS_CORE_APPS_INC_LED_H_
#define APPS_CORE_APPS_INC_LED_H_

#include "main.h"

#define LED_RED_ON  HAL_GPIO_WritePin(LED_R_GPIO_Port,LED_R_Pin,GPIO_PIN_RESET)
#define LED_RED_OFF HAL_GPIO_WritePin(LED_R_GPIO_Port,LED_R_Pin,GPIO_PIN_SET)

#define LED_BLUE_ON  HAL_GPIO_WritePin(LED_B_GPIO_Port,LED_B_Pin,GPIO_PIN_RESET)
#define LED_BLUE_OFF HAL_GPIO_WritePin(LED_B_GPIO_Port,LED_B_Pin,GPIO_PIN_SET)

void LED_ON(GPIO_TypeDef *GPIOx,uint16_t PinX,uint8_t mode);
void LED_Toggle_state(GPIO_TypeDef *GPIOx,uint16_t PinX);


#endif //APPS_CORE_APPS_INC_LED_H_
