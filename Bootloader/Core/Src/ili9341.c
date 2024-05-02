/**
  ******************************************************************************
  * @文件名           : ili9341.c
  * @作 者           : 13552
  * @brief          : None
  * @注意            : None
  * @日 期           : 2024/1/31
  ******************************************************************************
  */
#include "ili9341.h"
#include "lcdfont.h"
_LCD xLCD;

__inline void wrtieCmd(uint16_t usCmd) {
  *ILI9341_CMD_ADDR = usCmd;
}
__inline void writeData(uint16_t usData) {
  *ILI9341_DATA_ADDR = usData;
}
uint16_t readData(void) {
  return (*(__IO uint16_t *)0x60020000);
}
void LCD_DisplayDir(uint8_t scanDir) {
  uint16_t regval = 0;
  if (scanDir == 0 || scanDir == 3)       // 竖屏
  {
	xLCD.dir = 0;
	xLCD.width = LCD_WIDTH;
	xLCD.height = LCD_HIGH;
  }
  if (scanDir == 5 || scanDir == 6)   // 横屏
  {
	xLCD.dir = 1;
	xLCD.width = LCD_HIGH;
	xLCD.height = LCD_WIDTH;
  }
  if (scanDir == 0) regval |= (0 << 7) | (0 << 6) | (0 << 5); // 从左到右,从上到下
  if (scanDir == 3) regval |= (1 << 7) | (1 << 6) | (0 << 5); // 从右到左,从下到上
  if (scanDir == 5) regval |= (0 << 7) | (1 << 6) | (1 << 5); // 从上到下,从右到左
  if (scanDir == 6) regval |= (1 << 7) | (0 << 6) | (1 << 5); // 从下到上,从左到右
  wrtieCmd(0X36);             // 读写方向，颜色模式
  writeData(regval | 0x08);          //
}
void setCursor(uint16_t x, uint16_t y, uint16_t width, uint16_t height) {
  wrtieCmd(0X2A);                 // 发送指令：设置x坐标
  writeData(x >> 8);
  writeData(x & 0xFF);
  writeData((x + width - 1) >> 8);
  writeData((x + width - 1) & 0xFF);

  wrtieCmd(0X2B);
  writeData(y >> 8);
  writeData(y & 0xFF);
  writeData((y + height - 1) >> 8);
  writeData((y + height - 1) & 0xFF);

  // 发送写GRAM指令
  wrtieCmd(0X2C);
}
void LCD_Fill(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color) {
  uint32_t num = width * height;
  setCursor(x, y, width, height);
  while (num--)
	writeData(color);
}
void ILI9341_Init(void) {
  HAL_GPIO_WritePin(LCD_BK_GPIO_Port, LCD_BK_Pin, GPIO_PIN_SET);

  //尝试9341 ID的读取
  wrtieCmd(0XD3);            // 指令：读ID
  readData();             // 第1个参数：dummy
  readData();               // 第2个参数：IC版本号
  xLCD.id = readData();     // 第3个参数：IC名字(93)
  xLCD.id <<= 8;
  xLCD.id |= readData();    // 第4个参数：IC名字(41)
  //printf("显示屏 检测...        %x\r\n",xLCD.id);  // 打印LCD ID
  if (xLCD.id != 0X9341)    // 9341初始化失败
	return;                // 注意：如果FSMC配置不正确，有可能可显示，但刷新速度慢，且读取不到正确型号

  // Power control B (CFh)
  wrtieCmd(0xCF);
  writeData(0x00);
  writeData(0xC1); //-81
  writeData(0x30);
  // Power on sequence control (EDh)
  wrtieCmd(0xED);
  writeData(0x64);
  writeData(0x03);
  writeData(0x12);
  writeData(0x81);
  // Driver timing control A (E8h)
  wrtieCmd(0xE8); //
  writeData(0x85);
  writeData(0x10);
  writeData(0x7A); //-78
  // Power control A (CBh)
  wrtieCmd(0xCB);
  writeData(0x39);
  writeData(0x2C);
  writeData(0x00);
  writeData(0x34);
  writeData(0x02);
  // Pump ratio control (F7h)
  wrtieCmd(0xF7);
  writeData(0x20);
  // Driver timing control B
  wrtieCmd(0xEA);
  writeData(0x00);
  writeData(0x00);
  // Frame Rate Control (In Normal Mode/Full Colors) (B1h) */
  wrtieCmd(0xB1);
  writeData(0x00);
  writeData(0x1A);  //-1B
  //  Display Function Control (B6h) */
  wrtieCmd(0xB6);
  writeData(0x0A);
  writeData(0xA2);
  // Power Control 1 (C0h)
  wrtieCmd(0xC0);
  writeData(0x1B); //-35
  // Power Control 2 (C1h)
  wrtieCmd(0xC1);
  writeData(0x01); //-11
  // VCOM 控制 1 (C5h)
  wrtieCmd(0xC5);
  writeData(0x30);  // 45
  writeData(0x30);  // 45
  // VCOM 控制 2 (C7h)
  wrtieCmd(0xC7);
  writeData(0xB7);  //-A2
  // 使能3 伽马控制 (F2h)
  wrtieCmd(0xF2);
  writeData(0x00);
  // 伽马设置 (26h)
  wrtieCmd(0x26);
  writeData(0x01);
  // 正极伽马校准 (E0H)
  wrtieCmd(0xE0);
  writeData(0x0F);
  writeData(0x2A); // 26
  writeData(0x28); // 24
  writeData(0x08); //0B
  writeData(0x0E);
  writeData(0x08); // 09
  writeData(0x54);
  writeData(0xA9); // A8
  writeData(0x43); // 46
  writeData(0x0A); // 0c
  writeData(0x0F); // 17
  writeData(0x00); // 00
  writeData(0x00); // 00
  writeData(0x00); // 00
  writeData(0x00);
  // 负极伽马校准 (E1h)
  wrtieCmd(0XE1);
  writeData(0x00);
  writeData(0x15); // 19
  writeData(0x17); // 1B
  writeData(0x07); // 04
  writeData(0x11); // 10
  writeData(0x06); // 07
  writeData(0x2B); // 2A
  writeData(0x56); // 47
  writeData(0x3C); // 39
  writeData(0x05); // 03
  writeData(0x10); // 06
  writeData(0x0F); // 06
  writeData(0x3F); // 30
  writeData(0x3F); // 38
  writeData(0x0F); //
  // 列地址设置
  wrtieCmd(0x2A);
  writeData(0x00);
  writeData(0x00);
  writeData(0x00);
  writeData(0xEF);
  // 页地址设置
  wrtieCmd(0x2B);
  writeData(0x00);
  writeData(0x00);
  writeData(0x01);
  writeData(0x3F);
  // 像素格式设置 (3Ah)
  wrtieCmd(0x3a);         // 像素格式设置
  writeData(0x55);        // 16位接口，16位数据
  // 退出睡眠模式 (11h)
  wrtieCmd(0x11);         // 等待5ms待电路稳定，再执行其它指令
  HAL_Delay(10);
  // 打开显示(29h)
  wrtieCmd(0x29);         // 不会改变帧存储器数据

  LCD_DisplayDir(LCD_DIR);   // 设置显示方向
  LCD_BK_GPIO_Port->BSRR |= LCD_BK_Pin;
  LCD_Fill(0, 0, xLCD.width, xLCD.height, LCD_BGCOLOR);
  xLCD.FlagInit = 1;
}
/*****************************************************************
 * 函  数：LCD_DrawPoint
 * 功  能：画一个点
 * 参  数：x坐标，y坐标, 16位颜色值
 * 返回值：无
 *
 * 备  注： 魔女开发板团队编写   淘宝 https://demoboard.taobao.com
 * 分  享： 不断更新于Q群文件夹：262901124  最后修改_2020年09月01日
******************************************************************/
void LCD_DrawPoint(uint16_t x, uint16_t y, uint16_t color) {
  setCursor(x, y, 1, 1);        //设置光标位置
  writeData(color);
}

/*****************************************************************
 * 函  数：LCD_Line
 * 功  能：画线段 (参考野火大神)
 * 参  数：xStart      起始x坐标
 *         yStart      起始y坐标
 *         xEnd        结束x坐标
 *         yEnd        结束y坐标
 *         color       颜色
 * 返回值：
 *
 * 备  注： 魔女开发板团队        淘宝 https://demoboard.taobao.com
 * 分  享： 不断更新于Q群文件夹：262901124  最后修改_2020年09月01日
******************************************************************/
void LCD_Line(uint16_t xStart, uint16_t yStart, uint16_t xEnd, uint16_t yEnd, uint16_t color) {
  uint16_t us;
  uint16_t usX_Current, usY_Current;

  int32_t lError_X = 0, lError_Y = 0, lDelta_X, lDelta_Y, lDistance;
  int32_t lIncrease_X, lIncrease_Y;

  lDelta_X = xEnd - xStart; //计算坐标增量
  lDelta_Y = yEnd - yStart;

  usX_Current = xStart;
  usY_Current = yStart;

  if (lDelta_X > 0)
	lIncrease_X = 1; //设置单步方向
  else if (lDelta_X == 0)
	lIncrease_X = 0;//垂直线
  else {
	lIncrease_X = -1;
	lDelta_X = -lDelta_X;
  }

  if (lDelta_Y > 0)
	lIncrease_Y = 1;
  else if (lDelta_Y == 0)
	lIncrease_Y = 0;//水平线
  else {
	lIncrease_Y = -1;
	lDelta_Y = -lDelta_Y;
  }

  if (lDelta_X > lDelta_Y)
	lDistance = lDelta_X; //选取基本增量坐标轴
  else
	lDistance = lDelta_Y;

  for (us = 0; us <= lDistance + 1; us++)//画线输出
  {
	LCD_DrawPoint(usX_Current, usY_Current, color);//画点

	lError_X += lDelta_X;
	lError_Y += lDelta_Y;

	if (lError_X > lDistance) {
	  lError_X -= lDistance;
	  usX_Current += lIncrease_X;
	}

	if (lError_Y > lDistance) {
	  lError_Y -= lDistance;
	  usY_Current += lIncrease_Y;
	}
  }
}
/*****************************************************************
 * 函  数：LCD_GetPointPixel
 * 功  能：获取某一个坐标点像素的颜色值数据
 * 参  数：x      x坐标
 *         y      y坐标
 * 返回值：16位像素颜色值
 *
 * 备  注： 魔女开发板团队编写   淘宝 https://demoboard.taobao.com
 * 分  享： 不断更新于Q群文件夹：262901124  最后修改_2020年09月01日
******************************************************************/
uint16_t LCD_GetPoint(uint16_t x, uint16_t y) {
  uint16_t r = 0, g = 0, b = 0;

  setCursor(x, y, 1, 1);
  wrtieCmd(0x2E);  // 读GRAN

  r = readData();     // 第1个返回的是无效值
  r = readData();
  b = readData();
  g = readData();

  return (((r >> 11) << 11) | ((g >> 10) << 5) | (b >> 11));
}
/*****************************************************************
 * 函  数：LCD_DisplayOn
 * 功  能：开启显示，亮屏
 * 参  数：
 *
 * 返回值：
 *
 * 备  注： 魔女开发板团队编写   淘宝 https://demoboard.taobao.com
 * 分  享： 不断更新于Q群文件夹：262901124  最后修改_2020年09月01日
******************************************************************/
void LCD_DisplayOn(void) {
  wrtieCmd(0X29);    //开启显示
  LCD_BK_GPIO_Port->BSRR |= LCD_BK_Pin;
}

/*****************************************************************
 * 函  数：LCD_DisplayOff
 * 功  能：关闭显示, 熄屏
 * 参  数：
 *
 * 返回值：
 *
 * 备  注： 魔女开发板团队编写   淘宝 https://demoboard.taobao.com
 * 分  享： 不断更新于Q群文件夹：262901124  最后修改_2020年09月01日
******************************************************************/
void LCD_DisplayOff(void) {
  wrtieCmd(0X28);    //关闭显示
  LCD_BK_GPIO_Port->BSRR |= (uint32_t)LCD_BK_Pin << 16;
}
/*****************************************************************
 * 函  数：LCD_Rectangle
 * 功  能：画一个矩形 (参考野火大神)
 * 参  数：x       起始x坐标
 *         y       起始y坐标
 *         width   矩形的像素宽度
 *         height  矩形的像素高度
 *         color   颜色
 *         filled  是否实体填充
 * 返回值：
 *
 * 备  注： 魔女开发板团队编写   淘宝 https://demoboard.taobao.com
 * 分  享： 不断更新于Q群文件夹：262901124  最后修改_2020年09月01日
******************************************************************/
void LCD_Rectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color, uint8_t filled) {
  if (filled) {
	LCD_Fill(x, y, width, height, color);
  } else {
	LCD_Line(x, y, x + width - 1, y, color);
	LCD_Line(x, y + height - 1, x + width - 1, y + height - 1, color);
	LCD_Line(x, y, x, y + height - 1, color);
	LCD_Line(x + width - 1, y, x + width - 1, y + height - 1, color);
  }
}
/*****************************************************************
 * 函  数：LCD_Circle
 * 功  能：画一个圆形  (参考野火大神)
 * 参  数：x       起始x坐标
 *         y       起始y坐标
 *         radius  半径
 *         color   颜色
 *         filled  是否实体填充
 * 返回值：
 *
 * 备  注： 魔女开发板团队编写   淘宝 https://demoboard.taobao.com
 * 分  享： 不断更新于Q群文件夹：262901124  最后修改_2020年09月01日
******************************************************************/
void LCD_Circle(uint16_t x, uint16_t y, uint16_t radius, uint16_t color, uint8_t filled) {
  int16_t sCurrentX, sCurrentY;
  int16_t sError;

  sCurrentX = 0;
  sCurrentY = radius;
  sError = 3 - (radius << 1);     //判断下个点位置的标志

  while (sCurrentX <= sCurrentY) {
	int16_t sCountY;

	if (filled)
	  for (sCountY = sCurrentX; sCountY <= sCurrentY; sCountY++) {
		LCD_DrawPoint(x + sCurrentX, y + sCountY, color);           //1，研究对象
		LCD_DrawPoint(x - sCurrentX, y + sCountY, color);           //2
		LCD_DrawPoint(x - sCountY, y + sCurrentX, color);           //3
		LCD_DrawPoint(x - sCountY, y - sCurrentX, color);           //4
		LCD_DrawPoint(x - sCurrentX, y - sCountY, color);           //5
		LCD_DrawPoint(x + sCurrentX, y - sCountY, color);           //6
		LCD_DrawPoint(x + sCountY, y - sCurrentX, color);           //7
		LCD_DrawPoint(x + sCountY, y + sCurrentX, color);           //0
	  }
	else {
	  LCD_DrawPoint(x + sCurrentX, y + sCurrentY, color);             //1，研究对象
	  LCD_DrawPoint(x - sCurrentX, y + sCurrentY, color);             //2
	  LCD_DrawPoint(x - sCurrentY, y + sCurrentX, color);             //3
	  LCD_DrawPoint(x - sCurrentY, y - sCurrentX, color);             //4
	  LCD_DrawPoint(x - sCurrentX, y - sCurrentY, color);             //5
	  LCD_DrawPoint(x + sCurrentX, y - sCurrentY, color);             //6
	  LCD_DrawPoint(x + sCurrentY, y - sCurrentX, color);             //7
	  LCD_DrawPoint(x + sCurrentY, y + sCurrentX, color);             //0
	}

	sCurrentX++;

	if (sError < 0)
	  sError += 4 * sCurrentX + 6;
	else {
	  sError += 10 + 4 * (sCurrentX - sCurrentY);
	  sCurrentY--;
	}
  }
}
void LCD_Draw_Hline(uint16_t x, uint16_t y, uint16_t len, uint16_t color) {
  if ((len == 0) || (x > xLCD.width) || (y > xLCD.height))return;
  LCD_Fill(x, y, x + len - 1, y, color);
}
void LCD_Fill_Circle(uint16_t x, uint16_t y, uint16_t r, uint16_t color) {
  uint32_t i;
  uint32_t imax = ((uint32_t)r * 707) / 1000 + 1;
  uint32_t sqmax = (uint32_t)r * (uint32_t)r + (uint32_t)r / 2;
  uint32_t xr = r;
  LCD_Draw_Hline(x - r, y, 2 * r, color);
  for (i = 0; i <= imax; i++) {
	if ((i * i + xr * xr) > sqmax) {
	  if (xr > imax) {
		LCD_Draw_Hline(x - i + 1, y + xr, 2 * (i - 1), color);
		LCD_Draw_Hline(x - i + 1, y - xr, 2 * (i - 1), color);
	  }
	  xr--;
	}
	LCD_Draw_Hline(x - xr, y + i, 2 * xr, color);
	LCD_Draw_Hline(x - xr, y - i, 2 * xr, color);
  }
}
void LCD_Show_Char(uint16_t x, uint16_t y, char chr, uint8_t size, uint8_t mode, uint16_t color) {
  uint8_t temp, t1, t;
  uint16_t y0 = y;
  uint8_t csize = 0;
  uint8_t *pfont = 0;
  csize = (size / 8 + ((size % 8) ? 1 : 0)) * (size / 2);
  chr = chr - ' ';
  switch (size) {
	case 12: pfont = (uint8_t *)asc2_1206[chr];
	  break;
	case 16: pfont = (uint8_t *)asc2_1608[chr];  /* 调用1608字体 */
	  break;
	case 24: pfont = (uint8_t *)asc2_2412[chr];  /* 调用2412字体 */
	  break;
	case 32: pfont = (uint8_t *)asc2_3216[chr];  /* 调用3216字体 */
	  break;
	default: return;
  }
  for (t = 0; t < csize; t++) {
	temp = pfont[t];
	for (t1 = 0; t1 < 8; t1++)   /* 一个字节8个点 */
	{
	  if (temp & 0x80)        /* 有效点,需要显示 */
	  {
		LCD_DrawPoint(x, y, color);        /* 画点出来,要显示这个点 */
	  } else if (mode == 0)     /* 无效点,不显示 */
	  {
		LCD_DrawPoint(x, y, LCD_BGCOLOR); /* 画背景色,相当于这个点不显示(注意背景色由全局变量控制) */
	  }
	  temp <<= 1; /* 移位, 以便获取下一个位的状态 */
	  y++;
	  if (y >= xLCD.height)return;  /* 超区域了 */
	  if ((y - y0) == size)   /* 显示完一列了? */
	  {
		y = y0; /* y坐标复位 */
		x++;    /* x坐标递增 */
		if (x >= xLCD.width)return;   /* x坐标超区域了 */
		break;
	  }
	}
  }
}
void LCD_Show_String(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t size, char *p, uint16_t color)
{
  uint8_t x0 = x;
  width += x;
  height += y;

  while ((*p <= '~') && (*p >= ' '))   /* 判断是不是非法字符! */
  {
	if (x >= width)
	{
	  x = x0;
	  y += size;
	}

	if (y >= height)break;  /* 退出 */

	LCD_Show_Char(x, y, *p, size, 0, color);
	x += size / 2;
	p++;
  }
}