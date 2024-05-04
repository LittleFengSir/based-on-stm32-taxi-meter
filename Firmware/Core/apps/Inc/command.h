/**
  ******************************************************************************
  * @文件名           : command.h
  * @作 者           : 小冯Sir
  * @brief          : None
  * @注意            : None
  * @日 期           : 24-5-3
  ******************************************************************************
  */
#ifndef FIRMWARE_CORE_APPS_INC_COMMAND_H_
#define FIRMWARE_CORE_APPS_INC_COMMAND_H_

#include "main.h"
#include "string.h"

void command_Process(uint8_t *str,uint16_t size);
uint8_t parsedate(const char *date_str, int *year, int *month, int *day);
#endif //FIRMWARE_CORE_APPS_INC_COMMAND_H_
