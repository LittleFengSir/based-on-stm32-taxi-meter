/**
  ******************************************************************************
  * @文件名           : myInit.c
  * @作 者           : 13552
  * @brief          : None
  * @注意            : None
  * @日 期           : 2024-04-26
  ******************************************************************************
  */
#include "myInit.h"

void myInit(){
  //printf重定向至USART1
  RetargetInit(&huart1);
  //初始化LCD
  ILI9341_Init();
  LCD_Fill(0, 0, xLCD.width, xLCD.height, WHITE);
}