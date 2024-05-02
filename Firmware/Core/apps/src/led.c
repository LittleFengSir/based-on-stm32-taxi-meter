/**
  ******************************************************************************
  * @文件名           : led.c
  * @作 者           : 小冯Sir
  * @brief          : None
  * @注意            : None
  * @日 期           : 24-5-2
  ******************************************************************************
  */
#include "led.h"

void LED_ON(GPIO_TypeDef *GPIOx,uint16_t PinX,uint8_t mode){
  if(mode == 0){
	HAL_GPIO_WritePin(GPIOx,PinX,GPIO_PIN_RESET);
  }
  if (mode == 1){
	HAL_GPIO_WritePin(GPIOx,PinX,GPIO_PIN_SET);
  }
}

void LED_Toggle_state(GPIO_TypeDef *GPIOx,uint16_t PinX){
  HAL_GPIO_TogglePin(GPIOx,PinX);
}