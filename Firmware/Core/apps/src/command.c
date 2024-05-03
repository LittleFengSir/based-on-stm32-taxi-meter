/**
  ******************************************************************************
  * @文件名           : command.c
  * @作 者           : 小冯Sir
  * @brief          : None
  * @注意            : None
  * @日 期           : 24-5-3
  ******************************************************************************
  */
#include "command.h"
#include "ctype.h"
#include "rtc.h"
uint8_t flag = 0;

uint8_t parsedate(const char *date_str, int *year, int *month, int *day) {
  if (date_str == NULL || year == NULL || month == NULL || day == NULL) {
	return -1;
  }
  if (sscanf(date_str, "%4d-%2d-%2d", year, month, day) != 3) {
	return -3;
  }
  if (*month < 1 || *month > 12) {
	return -4;
  }
  if (*day < 1 || *day > 31) {
	return -5;
  }
  return 0;
}
uint8_t parseTime(const char *str, int *hour, int *minute, int *second) {
  if(sscanf(str,"%d:%d:%d",hour,minute,second) == 3){
	return 1;
  }
  return 0;
}
void command_Process(uint8_t *str, uint16_t size) {
  int year, month, day;
  int hour, minute, second;
  int result;
  RTC_DateTypeDef sDate;
  RTC_TimeTypeDef sTime;
  if (strstr(str, "setdate")) flag = 1;
  if (strstr(str, "settime")) flag = 2;
  if (flag == 1) {
	printf("请以下日期格式输入：\r\n");
	printf("example: 2024-05-03\r\n");
	result = parsedate(str, &year, &month, &day);
	if (result == 0) {
	  printf("Year: %d, Month: %d, Day: %d\r\n", year, month, day);
	  sDate.Year = (uint8_t )(year % 100);
	  sDate.Month = (uint8_t )month;
	  sDate.Date = (uint8_t )day;
	  HAL_RTC_SetDate(&hrtc,&sDate,RTC_FORMAT_BIN);
	} else {
	  printf("Error parsing date: %d\n", result);
	}
  }
  if (flag == 2) {
	printf("请以一下时间格式输入：\r\n");
	printf("example: 02:44:30\r\n");
	result = parseTime(str,&hour,&minute,&second);
	if(result == 1){
	  printf("Hours: %d, Minutes: %d, Seconds: %d\n", hour, minute, second);
	  sTime.Hours = (uint8_t)hour;
	  sTime.Minutes = (uint8_t)minute;
	  sTime.Seconds = (uint8_t)second;
	  HAL_RTC_SetTime(&hrtc,&sTime,RTC_FORMAT_BIN);
	}
	else{
	  printf("Error parsing time: %d\n",result);
	}
  }

  printf("%s", str);
}