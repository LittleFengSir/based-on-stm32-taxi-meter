/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file   fatfs.c
  * @brief  Code for fatfs applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
#include "sdio.h"
#include "ws_drive_tft.h"
/* USER CODE END Header */
#include "fatfs.h"

uint8_t retSD;    /* Return value for SD */
char SDPath[4];   /* SD logical drive path */
FATFS SDFatFS;    /* File system object for SD logical drive */
FIL SDFile;       /* File object for SD */

/* USER CODE BEGIN Variables */
FRESULT fatfs_mount_fresult = FR_DISK_ERR;
/* USER CODE END Variables */

void MX_FATFS_Init(void)
{
  /*## FatFS: Link the SD driver ###########################*/
  retSD = FATFS_LinkDriver(&SD_Driver, SDPath);

  /* USER CODE BEGIN Init */
  FRESULT fre;
  fre = f_mount(&SDFatFS, SDPath, 1);
  fatfs_mount_fresult = fre;
  if (fre == FR_OK) {
	printf("\r\n");
	printf("SD card  mount OK \r\n");
	printf("SD cara init OK  size %.1f M\r\n", (float)hsd.SdCard.BlockNbr * hsd.SdCard.BlockSize / 1024 / 1024);
	sdMountFlag = 1;
  } else {
	printf("SD card  mount fail \r\n");
	sdMountFlag = 0;
  }
	/* additional user code for init */
  /* USER CODE END Init */
}

/**
  * @brief  Gets Time from RTC
  * @param  None
  * @retval Time in DWORD
  */
DWORD get_fattime(void)
{
  /* USER CODE BEGIN get_fattime */
  return 0;
  /* USER CODE END get_fattime */
}

/* USER CODE BEGIN Application */

/* USER CODE END Application */
