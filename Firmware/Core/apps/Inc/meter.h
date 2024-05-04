/**
  ******************************************************************************
  * @文件名           : meter.h
  * @作 者           : 小冯Sir
  * @brief          : None
  * @注意            : None
  * @日 期           : 24-5-3
  ******************************************************************************
  */

#ifndef FIRMWARE_CORE_APPS_INC_METER_H_
#define FIRMWARE_CORE_APPS_INC_METER_H_

#include "main.h"



void taxiSystemInit();
float getPrice();
float getSpeed();
float getMileage();
void setMileage(float km);
uint8_t writePriceToConfig(float tempPrice);
uint8_t createOrderFile();
#endif //FIRMWARE_CORE_APPS_INC_METER_H_
