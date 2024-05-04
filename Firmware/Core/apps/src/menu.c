/**
  ******************************************************************************
  * @文件名           : menu.c
  * @作 者           : 小冯Sir
  * @brief          : None
  * @注意            : None
  * @日 期           : 24-4-28
  ******************************************************************************
  */
#include <math.h>
#include "menu.h"
#include "sdio.h"
#include "rtc.h"
#include "tim.h"

void Staring_Menu() {
  WS_TFT_Clear(WHITE);
  char buffer[120];
  if (sdMountFlag == 1) {
	WS_TFT_Dis_12X24_String(0, 0, "SD card mount OK!", WHITE, GREEN);
	WS_TFT_Dis_12X24_String(0, 25, "SD card init OK!", WHITE, GREEN);
	sprintf(buffer, "size: %.1f M", (float)hsd.SdCard.BlockNbr * (float)hsd.SdCard
		.BlockSize / 1024 / 1024);
	WS_TFT_Dis_12X24_String(0, 49, buffer, WHITE, GREEN);
	WS_TFT_Dis_12X24_String(0, 73, "System Init OK!", WHITE, GREEN);
  } else {
	WS_TFT_Dis_12X24_String(0, 0, "SD card mount fail!", WHITE, RED);
	WS_TFT_Dis_12X24_String(0, 0, "Please Check sdCard", WHITE, RED);
  }
  HAL_Delay(20);
  WS_TFT_Clear(WHITE);
}

void showTime() {
  RTC_TimeTypeDef sTime;
  RTC_DateTypeDef sDate;
  HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
  HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
  char buffer[32];
  sprintf(buffer, "20%02u-%02u-%02u", sDate.Year, sDate.Month, sDate
	  .Date);
  WS_TFT_Dis_12X24_String(60, 0, buffer, WHITE, BLUE);
  sprintf(buffer, "%02u:%02u:%02u", sTime.Hours, sTime.Minutes, sTime.Seconds);
  WS_TFT_Dis_12X24_String(72, 25, buffer, WHITE, BLUE);

}
uint8_t beginFlag = 0;
void user_Menu() {

  showTime();
  char temp[22] = {0};
  sprintf(temp, "Price: %.2f CNY/Km", getPrice());
  WS_TFT_Dis_12X24_String(10, 120, temp, WHITE, BLUE);
  sprintf(temp, "Speed: %.2f KM/h", getSpeed());
  WS_TFT_Dis_12X24_String(10, 145, temp, WHITE, BLUE);
  sprintf(temp, "Mileage: %.3f KM", getMileage());
  WS_TFT_Dis_12X24_String(10, 170, temp, WHITE, BLUE);
  sprintf(temp, "TotalPrice: %.2f CNY", getMileage() * getPrice());
  WS_TFT_Dis_12X24_String(0, 220, temp, WHITE, BLACK);
  if (keyVal == 3) {
	beginFlag++;
	keyVal = 0;
  }
  if (beginFlag == 1) {
	HAL_TIM_Base_Start_IT(&htim4);
	setMileage(0);
	LED_BLUE_ON;
	beginFlag = 2;
  }
  if (beginFlag == 3) {
	HAL_TIM_Base_Stop_IT(&htim4);
	uint8_t ret = createOrderFile();
	if(ret == 1){
	  printf("create order successful\r\n");
	}else{
	  printf("Create order fail\r\n");
	}
	LED_BLUE_OFF;
	beginFlag = 0;
  }
}
uint8_t changeFlag = 0;
uint8_t getChangeFlag() {
  return changeFlag;
}
static float tempPrice = 0;
void changePriceMenu() {
  WS_TFT_Dis_12X24_String(10, 0, "SETTING PRICE", WHITE, BLUE);
  char temp[18];
  sprintf(temp, "Price: %.2f KM/h", getPrice() - tempPrice);
  if(changeFlag == 0) WS_TFT_Dis_12X24_String(10, 50, temp, WHITE, BLUE);
  if (keyVal == 3) {
	changeFlag++;
	keyVal = 0;
  }
  //修改价格步进为0.1时
  if (changeFlag == 1) {
	WS_TFT_Dis_12X24_String(10, 50, temp, BLUE, WHITE);
	WS_TFT_Dis_12X24_String(10, 75, "x 0.1 ", WHITE, BLACK);
	if (keyVal == 1) {
	  tempPrice -= 0.1f;
	  keyVal = 0;
	}
	if (keyVal == 2) {
	  tempPrice += 0.1f;
	  if ((float)fabs((double)tempPrice) >= getPrice()) {
		tempPrice = getPrice();
	  }
	  keyVal = 0;
	}
  }
  //修改价格步进为1时
  if (changeFlag == 2) {
	WS_TFT_Dis_12X24_String(10, 50, temp, BLUE, WHITE);
	WS_TFT_Dis_12X24_String(10, 75, "x 1    ", WHITE, BLACK);
	if (keyVal == 1) {
	  tempPrice -= 1.0f;
	  keyVal = 0;
	}
	if (keyVal == 2) {
	  tempPrice += 1.0f;
	  if ((float)fabs((double)tempPrice) >= getPrice()) {
		tempPrice = getPrice();
	  }
	  keyVal = 0;
	}
  }
  if(changeFlag == 3){
	WS_TFT_Dis_12X24_String(10, 50, temp, BLUE, WHITE);
	if(writePriceToConfig(getPrice() - tempPrice) == 1){
	  WS_TFT_Dis_12X24_String(10,100,"Set up price ok",WHITE,BLUE);
	  changeFlag = 0;
	  tempPrice = 0;
	}
	else{
	  WS_TFT_Dis_12X24_String(10,100,"Set up price fail",WHITE,BLUE);
	  changeFlag = 0;
	  tempPrice = 0;
	}
  }
}

