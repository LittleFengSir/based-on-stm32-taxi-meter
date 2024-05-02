/**
  ******************************************************************************
  * @文件名           : ili9341.h
  * @作 者           : 13552
  * @brief          : None
  * @注意            : None
  * @日 期           : 2024/1/31
  ******************************************************************************
  */

#ifndef FSMC_VET6_CORE_INC_ILI9341_H_
#define FSMC_VET6_CORE_INC_ILI9341_H_

#include "fsmc.h"
#include "stm32f1xx.h"

#define LCD_WIDTH 240
#define LCD_HIGH 320
#define LCD_DIR 0

typedef struct {
  uint8_t FlagInit;
  uint16_t width;
  uint16_t height;
  uint8_t dir;
  uint16_t id;
} _LCD;

extern _LCD xLCD;

/******************************* 定义 ILI934 显示屏常用颜色 ********************************/
#define      WHITE                 0xFFFF       // 白色
#define      BLACK               0x0000       // 黑色
#define      GREY                0xF7DE       // 灰色
#define      RED                 0xF800       // 红
#define      MAGENTA             0xF81F       // 洋红色
#define      GRED                0xFFE0    // 深红色
#define      GREEN               0x07E0       // 绿
#define      CYAN                0x7FFF       // 青色
#define      YELLOW              0xFFE0       // 黄色
#define      LIGHTGREEN          0X841F    // 浅绿色
#define      BLUE                0x001F       // 蓝
#define      GBLUE               0x07FF    // 浅蓝 1
#define      LIGHTBLUE           0X7D7C       // 浅蓝 2
#define      BLUE2               0x051F       // 浅蓝 3
#define      GRAYBLUE            0X5458    // 灰蓝
#define      DARKBLUE               0X01CF    // 深蓝

#define      LGRAY                  0XC618    // 浅灰色,窗体背景色
#define      LGRAYBLUE           0XA651    // 浅灰蓝色(中间层颜色)
#define      LBBLUE              0X2B12    // 浅棕蓝色(选择条目的反色)

#define ILI9341_CMD_ADDR (__IO uint16_t *)0x60000000
#define ILI9341_DATA_ADDR (__IO uint16_t *)0x60020000

#define LCD_BGCOLOR  WHITE

void ILI9341_Init(void);
void LCD_Fill(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);
void LCD_DrawPoint(uint16_t x, uint16_t y, uint16_t color);
void LCD_Line(uint16_t xStart, uint16_t yStart, uint16_t xEnd, uint16_t yEnd, uint16_t color);
uint16_t LCD_GetPoint(uint16_t x, uint16_t y);
void LCD_DisplayOn(void);
void LCD_DisplayOff(void);
void LCD_Rectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color, uint8_t filled);
void LCD_Circle(uint16_t x, uint16_t y, uint16_t radius, uint16_t color, uint8_t filled);
void LCD_Show_String(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t size, char *p, uint16_t color);
void LCD_Fill_Circle(uint16_t x, uint16_t y, uint16_t r, uint16_t color);
void LCD_Show_Char(uint16_t x, uint16_t y, char chr, uint8_t size, uint8_t mode, uint16_t color);

#endif //FSMC_VET6_CORE_INC_ILI9341_H_
