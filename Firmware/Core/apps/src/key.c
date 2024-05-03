#include "key.h"

uint16_t sensor_Count = 0;
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
  if (GPIO_Pin == KEY1_Pin) {
	if (HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == GPIO_PIN_SET) {
	  while (HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == GPIO_PIN_SET);
	  keyVal = 1;
	}
  }
  if (GPIO_Pin == KEY2_Pin) {
	if (HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == GPIO_PIN_RESET) {
	  while (HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == GPIO_PIN_RESET);
	  keyVal = 2;
	}
  }
  if (GPIO_Pin == KEY3_Pin) {
	if (HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin) == GPIO_PIN_RESET) {
	  while (HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin) == GPIO_PIN_RESET);
	  keyVal = 3;
	}
  }
  //光耦测速模块
  if(GPIO_Pin == SENOR_Pin){
	if(HAL_GPIO_ReadPin(SENOR_GPIO_Port,SENOR_Pin) == GPIO_PIN_SET){
	  sensor_Count++;
	}
  }
}
uint16_t getSensor_Count(){
  return sensor_Count;
}
void setSensor_Count(uint16_t count){
  sensor_Count = count;
}

