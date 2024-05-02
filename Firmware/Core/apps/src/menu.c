/**
  ******************************************************************************
  * @文件名           : menu.c
  * @作 者           : 小冯Sir
  * @brief          : None
  * @注意            : None
  * @日 期           : 24-4-28
  ******************************************************************************
  */
#include "menu.h"
#include "sdio.h"

void Staring_Menu(){
  WS_TFT_Clear(WHITE);
  char buffer[120];
  if(sdMountFlag == 1){
	WS_TFT_Dis_12X24_String(0,0,"SD card mount OK!",WHITE,GREEN);
	WS_TFT_Dis_12X24_String(0,25,"SD card init OK!",WHITE,GREEN);
	sprintf(buffer,"size: %.1f M",(float )hsd.SdCard.BlockNbr * hsd.SdCard
	.BlockSize/ 1024 / 1024);
	WS_TFT_Dis_12X24_String(0,49,buffer,WHITE,GREEN);
	WS_TFT_Dis_12X24_String(0,73,"System Init OK!",WHITE,GREEN);
  }else{
	WS_TFT_Dis_12X24_String(0,0,"SD card mount fail!",WHITE,RED);
	WS_TFT_Dis_12X24_String(0,0,"Please Check sdCard",WHITE,RED);
  }
}

void user_Menu(){
  HAL_Delay(20);
}