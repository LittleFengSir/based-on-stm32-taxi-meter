/**
  ******************************************************************************
  * @文件名           : meter.c
  * @作 者           : 小冯Sir
  * @brief          : None
  * @注意            : None
  * @日 期           : 24-5-3
  ******************************************************************************
  */
#include "meter.h"
#include "rtc.h"
#include "stdlib.h"
#include "fatfs.h"

float price = 3.0f;
char *date;
char *username;
char *pwd;
//单位是米(m)
float wheelRadius = 0.6f;
float Mileage = 0.0f;

float speed = 0;

//日期参数
//默认价钱
//串口用户名和密码
void createConfigFile() {
  FRESULT fre;
  RTC_DateTypeDef sDate;
  HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
  char *temp = malloc(16 * sizeof(char));
  sprintf(temp, "20%02u-%02u-%02u", sDate.Year, sDate.Month, sDate
	  .Date);
  cJSON *a = cJSON_CreateObject();
  cJSON_AddStringToObject(a, "Date", temp);
  cJSON_AddNumberToObject(a, "Price", price);
  cJSON_AddNumberToObject(a, "Wheel_Radius", wheelRadius);
  cJSON_AddStringToObject(a, "username", "admin");
  cJSON_AddStringToObject(a, "pwd", "12345678");
  char *json_string = cJSON_Print(a);

  //打开并创建文件
  fre =
	  f_open(&SDFile, "system/config.txt",
			 FA_READ | FA_WRITE | FA_CREATE_NEW);
  if (fre == FR_OK) {
	printf("Create config.txt ok \r\n");
	UINT bw;
	if (f_write(&SDFile, json_string,
				strlen(json_string), &bw) == FR_OK) {
	  printf("Write config.txt ok \r\n");
	  printf("%s\r\n", json_string);
	}
	f_close(&SDFile);
  } else printf("create config.txt fail %d\r\n", fre);

  free(temp);
  free(json_string);
}

uint8_t checkInitFile() {
  FRESULT fre;
  fre = f_open(&SDFile, "system/config.txt", FA_READ);
  if (fre == FR_OK) {
	f_close(&SDFile);
	return 0;
  } else if(fre == FR_NO_FILE){
	createConfigFile();
  }
  f_close(&SDFile);
  return 1;
}

void taxiSystemInit() {
  DWORD file_size;
  long length;
  uint8_t *data;
  cJSON *json, *item;
  uint8_t res = checkInitFile();
  if (res == 0) {
	printf("config.txt exists\r\n");
  }
  //read config.txt
  FRESULT fre;
  fre = f_open(&SDFile, "system/config.txt", FA_READ);
  if (fre != FR_OK) {
	printf("can't open config.txt file \r\n");
  }
  //get file size
  file_size = f_size(&SDFile);
  if (fre != FR_OK) {
	printf("get file size failure\r\n");
  }
  printf("File size is %lu bytes\r\n", file_size);
  //read file
  UINT br;
  f_lseek(&SDFile, file_size);
  length = f_tell(&SDFile);
  f_lseek(&SDFile, 0);
  data = (uint8_t *)malloc(length + 1);
  if (f_read(&SDFile, data, length, &br) == FR_OK) {
	data[br] = '\0';
	printf("config.txt: %s", data);
  }
  f_close(&SDFile);

  //解析JSON数据
  json = cJSON_Parse((char *)data);
  if (!json) {
	printf("解析JSON失败！\n");
	free(data);
  }
  item = cJSON_GetObjectItemCaseSensitive(json, "Date");
  if (item && cJSON_IsString(item)) {
	date = item->valuestring;
	printf("Date: %s\r\n", date);
  } else {
	printf("Not find name\r\n");
  }
  item = cJSON_GetObjectItemCaseSensitive(json, "Price");
  if (item && cJSON_IsNumber(item) && (item->valueint == 0 ||
	  item->valuedouble != 0)) {
	price = (float)item->valuedouble;
	printf("Price: %.2f\r\n", price);
  } else {
	printf("not find price\r\n");
	price = 3.0f;
  }
  item = cJSON_GetObjectItemCaseSensitive(json, "username");
  if (item && cJSON_IsString(item)) {
	username = item->valuestring;
	printf("username: %s\r\n", username);
  } else {
	printf("Not find username\r\n");
	username = "admin";
  }

  item = cJSON_GetObjectItemCaseSensitive(json, "pwd");
  if (item && cJSON_IsString(item)) {
	pwd = item->valuestring;
	printf("pwd: %s\r\n", pwd);
  } else {
	printf("Not find pwd\r\n");
	pwd = "12345678";
  }
  cJSON_Delete(json);
  free(data);
}

float getPrice() {
  return price;
}
float getSpeed() {
  return speed;
}
float getMileage() {
  return Mileage;
}
void setMileage(float km) {
  Mileage = km;
}

uint8_t writePriceToConfig(float tempPrice) {
  DWORD file_size;
  long length;
  FRESULT fre;
  fre = f_open(&SDFile, "system/config.txt", FA_READ);
  if (fre != FR_OK) {
	printf("can't open config.txt file\r\n");
	return 0;
  }
  file_size = f_size(&SDFile);
  UINT br;
  uint8_t *data;
  f_lseek(&SDFile, file_size);
  length = f_tell(&SDFile);
  f_lseek(&SDFile, 0);
  data = (uint8_t *)malloc(length + 1);
  if (f_read(&SDFile, data, length, &br) == FR_OK) {
	data[br] = '\0';
  }
  f_close(&SDFile);
  cJSON *root = cJSON_Parse((char *)data);
  if (!root) {
	printf("Failed to parse JSON\r\n");
	free(data);
	return 0;
  }
  cJSON *cJSON_price = cJSON_GetObjectItemCaseSensitive(root, "Price");
  if (cJSON_price && cJSON_IsNumber(cJSON_price)) {
	cJSON_SetNumberValue(cJSON_price, tempPrice);
  }
  char *new_data = cJSON_Print(root);
  fre = f_open(&SDFile, "system/config.txt", FA_WRITE);
  if (fre != FR_OK) {
	printf("can't open config.txt\r\n");
	cJSON_Delete(root);
	free(data);
	free(new_data);
	return 0;
  }
  UINT bw;
  if (f_write(&SDFile, new_data, strlen(new_data), &bw) == FR_OK) {
	printf("set up Price successful\r\n");
	price = tempPrice;
	f_close(&SDFile);
	cJSON_Delete(root);
	free(data);
	free(new_data);
	return 1;
  } else {
	printf("set up Price failure\r\n");
	f_close(&SDFile);
	cJSON_Delete(root);
	free(data);
	free(new_data);
	return 0;
  }

}

void createOrderFile(){

}

//定时器中断回调函数
//1ms中断
uint16_t timCount = 0;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
  if (htim->Instance == TIM4) {
	timCount++;
	if (timCount == 1000) {
	  speed = (float)getSensor_Count() / 20.0f * wheelRadius * 3.6f;
	  timCount = 0;
	  setSensor_Count(0);
	  Mileage += speed * 2.0f * 3.14f * wheelRadius * (1.0f / 3600.0f);
	}
  }
}


