
#ifndef __LCD9486_DRV_H__
#define __LCD9486_DRV_H__

#include "main.h"



//      ???????
#define WHITE       0xFFFF
#define BLACK      	0x0000	  
#define BLUE       	0x001F  
#define BRED        0XF81F
#define GRED 			 	0XFFE0
#define GBLUE			 	0X07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define GREEN       0x07E0
#define CYAN        0x7FFF
#define YELLOW      0xFFE0
#define BROWN 			0XBC40 //???
#define BRRED 			0XFC07 //????
#define GRAY  			0X8430 //???
//GUI???


#define DARKBLUE      	 0X01CF	//?????
#define LIGHTBLUE      	 0X7D7C	//????  
#define GRAYBLUE       	 0X5458 //?????
//????????PANEL????? 
 
#define LIGHTGREEN     	0X841F //????
#define LGRAY 			 		0XC618 //????(PANNEL),???屳???

#define LGRAYBLUE      	0XA651 //??????(?м?????)
#define LBBLUE          0X2B12 //??????(??????????)



#define LCD_DIR_MODE	       0           //0????????1????????	


#define LCD9486_BL_CLOSE	   LCD_BK_GPIO_Port->ODR &= ~LCD_BL_Pin  ;
#define LCD9486_BL_OPEN      LCD_BK_GPIO_Port->ODR |=  LCD_BK_Pin  ;


#if LCD_DIR_MODE == 0
	  #define TFT_X_MAX	240
	  #define TFT_Y_MAX	320
#else
		#define TFT_X_MAX	320
		#define TFT_Y_MAX	240
#endif



void WS_TFT_Init(void);
void WS_TFT_Set_Windows(uint16_t xStar, uint16_t yStar,uint16_t xEnd,uint16_t yEnd);



void WS_TFT_Dis_5X7_String   (int x,int y,  char     *string , uint16_t backColor  ,uint16_t forColor) ;
void WS_TFT_Dis_8X16_String  (int x,int y,  char     *string , uint16_t backColor  ,uint16_t forColor)  ;
void WS_TFT_Dis_12X24_String (int x,int y,  char     *string , uint16_t backColor  ,uint16_t forColor);
void WS_TFT_Dis_16X32_String (int x,int y,  char     *string , uint16_t backColor  ,uint16_t forColor)   ;



void WS_TFT_Clear(uint16_t color);
void WS_TFT_Draw_Point       (uint16_t x,uint16_t y,uint16_t color) ;
void WS_TFT_Draw_Rectangle(uint16_t xStar, uint16_t yStar,uint16_t xEnd,uint16_t yEnd,uint16_t color);


__weak uint32_t  WS_Font16_Read_Date(uint8_t *buffer , uint8_t * gbk , uint32_t size);
__weak uint32_t  WS_Font24_Read_Date(uint8_t *buffer , uint8_t * gbk , uint32_t size);
__weak uint32_t  WS_Font32_Read_Date(uint8_t *buffer , uint8_t * gbk , uint32_t size);

 
void WS_TFT_Dis_16X16_Date (int x, int y, uint8_t  *buffer , uint16_t n, uint16_t backColor  ,uint16_t forColor);
void WS_TFT_Dis_24X24_Date (int x, int y, uint8_t  *buffer , uint16_t n, uint16_t backColor  ,uint16_t forColor);
void WS_TFT_Dis_32X32_Date (int x, int y, uint8_t  *buffer , uint16_t n, uint16_t backColor  ,uint16_t forColor);

//    ??TFT???? ??8X16?? ???????
void  WS_TFT_Dis_Debug(int x,int y, uint16_t forColor , char *p,...);

//   ??ADC????λλ??????
//   ???????16λ??X?????16λ??y?
uint32_t WS_TFT_Touth_Get_Point(SPI_HandleTypeDef *hspi);

uint16_t  WS_TFT_Touth_Read_XPT2046(SPI_HandleTypeDef *hspi,uint16_t  cmd);





#endif

