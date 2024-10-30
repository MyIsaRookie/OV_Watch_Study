#ifndef _TFT_LCD_INIT_
#define _TFT_LCD_INIT_
#include "sys.h"
/*----------------LCD引脚定义-------------------------*/
#define USE_HORIZONTAL 0  //设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏

#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 240
#define LCD_H 280

#else
#define LCD_W 280
#define LCD_H 240
#endif



#define  TFT_LCD_CLK_ENABLE()               do{__HAL_RCC_GPIOB_CLK_ENABLE();}while(0)

// SPI时钟线
#define  TFT_LCD_SCLK_PORT                  GPIOB
#define  TFT_LCD_SCLK_PIN                   GPIO_PIN_3

// SPI数据线
#define  TFT_LCD_MOSI_PORT                  GPIOB
#define  TFT_LCD_MOSI_PIN                   GPIO_PIN_5

// External reset input
#define  TFT_LCD_RES_PORT			        GPIOB
#define  TFT_LCD_RES_PIN				    GPIO_PIN_7

// Display data/command selection pin in parallel 
#define  TFT_LCD_DC_PORT				    GPIOB
#define  TFT_LCD_DC_PIN				        GPIO_PIN_9

// Chip select input pin  
#define  TFT_LCD_CS_PORT				    GPIOB
#define  TFT_LCD_CS_PIN				        GPIO_PIN_8

// LED back light
#define  TFT_LCD_BLK_PORT			        GPIOB
#define  TFT_LCD_BLK_PIN				    GPIO_PIN_0

#define TFT_LCD_SCLK_Clr() HAL_GPIO_WritePin(TFT_LCD_SCLK_PORT,TFT_LCD_SCLK_PIN,GPIO_PIN_RESET)//SCL=SCLK
#define TFT_LCD_SCLK_Set() HAL_GPIO_WritePin(TFT_LCD_SCLK_PORT,TFT_LCD_SCLK_PIN,GPIO_PIN_SET)

#define TFT_LCD_MOSI_Clr() HAL_GPIO_WritePin(TFT_LCD_MOSI_PORT,TFT_LCD_MOSI_PIN,GPIO_PIN_RESET)//SDA=MOSI
#define TFT_LCD_MOSI_Set() HAL_GPIO_WritePin(TFT_LCD_MOSI_PORT,TFT_LCD_MOSI_PIN,GPIO_PIN_SET)

#define TFT_LCD_RES_Clr()  HAL_GPIO_WritePin(TFT_LCD_RES_PORT,TFT_LCD_RES_PIN,GPIO_PIN_RESET)  //RES
#define TFT_LCD_RES_Set()  HAL_GPIO_WritePin(TFT_LCD_RES_PORT,TFT_LCD_RES_PIN,GPIO_PIN_SET)

#define TFT_LCD_DC_Clr()   HAL_GPIO_WritePin(TFT_LCD_DC_PORT,TFT_LCD_DC_PIN,GPIO_PIN_RESET)    //DC
#define TFT_LCD_DC_Set()   HAL_GPIO_WritePin(TFT_LCD_DC_PORT,TFT_LCD_DC_PIN,GPIO_PIN_SET)

#define TFT_LCD_CS_Clr()   HAL_GPIO_WritePin(TFT_LCD_CS_PORT,TFT_LCD_CS_PIN,GPIO_PIN_RESET)    //CS
#define TFT_LCD_CS_Set()   HAL_GPIO_WritePin(TFT_LCD_CS_PORT,TFT_LCD_CS_PIN,GPIO_PIN_SET)

#define TFT_LCD_BLK_Clr()  HAL_GPIO_WritePin(TFT_LCD_BLK_PORT,TFT_LCD_BLK_PIN,GPIO_PIN_RESET)  //BLK
#define TFT_LCD_BLK_Set()  HAL_GPIO_WritePin(TFT_LCD_BLK_PORT,TFT_LCD_BLK_PIN,GPIO_PIN_SET)

void TFT_LCD_WR_DATA8(uint8_t dat);
void TFT_LCD_WR_DATA(uint16_t dat);
void TFT_LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);
void TFT_LCD_Init(void);

#endif






















