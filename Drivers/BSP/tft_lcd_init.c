#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "spi.h"
#include "tft_lcd_init.h"


/******************************************************************************
      ����˵����LCD�˿ڳ�ʼ��
      ������ݣ���
      ����ֵ��  ��
******************************************************************************/
void TFT_LCD_GPIO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure = {0};
	
 	TFT_LCD_CLK_ENABLE();
	
	GPIO_InitStructure.Pin = TFT_LCD_RES_PIN|TFT_LCD_CS_PIN|TFT_LCD_DC_PIN|TFT_LCD_BLK_PIN;	 
 	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP; 		 //�������
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;//�ٶ�50MHz
 	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);	         //��ʼ��GPIOB
 	HAL_GPIO_WritePin(GPIOB, TFT_LCD_RES_PIN|TFT_LCD_CS_PIN|TFT_LCD_DC_PIN|TFT_LCD_BLK_PIN, GPIO_PIN_SET);
    
    
    
}


/******************************************************************************
      ����˵����LCD��������д�뺯��(software SPI)
      ������ݣ�dat  Ҫд��Ĵ�������
      ����ֵ��  ��
******************************************************************************/
void TFT_LCD_Writ_Bus(uint8_t dat) 
{	
	//hard SPI
	HAL_SPI_Transmit(&hspi1,&dat,1,1);
	
	//soft SPI
	/*
	u8 i;
	for(i=0;i<8;i++)
	{			  
		LCD_SCLK_Clr();
		if(dat&0x80)
		{
		   LCD_MOSI_Set();
		}
		else
		{
		   LCD_MOSI_Clr();
		}
		LCD_SCLK_Set();
		dat<<=1;
	}	
	*/
}

/******************************************************************************
      ����˵����LCDд������
      ������ݣ�dat д�������
      ����ֵ��  ��
******************************************************************************/
void TFT_LCD_WR_DATA8(uint8_t dat)
{
	TFT_LCD_Writ_Bus(dat);
}



/******************************************************************************
      ����˵����LCDд������
      ������ݣ�dat д�������
      ����ֵ��  ��
******************************************************************************/
void TFT_LCD_WR_DATA(uint16_t dat)
{
//	LCD_Writ_Bus(dat>>8);
//	LCD_Writ_Bus(dat);
	uint8_t temp[2];
	temp[0]=(dat>>8)&0xff;
	temp[1]=dat&0xff;
	HAL_SPI_Transmit(&hspi1,temp,2,1);
	
}


/******************************************************************************
      ����˵����LCDд������
      ������ݣ�dat д�������
      ����ֵ��  ��
******************************************************************************/
void TFT_LCD_WR_REG(uint8_t dat)
{
	TFT_LCD_DC_Clr();//д����
	TFT_LCD_Writ_Bus(dat);
	TFT_LCD_DC_Set();//д����
}

/******************************************************************************
      ����˵����������ʼ�ͽ�����ַ
      ������ݣ�x1,x2 �����е���ʼ�ͽ�����ַ
                y1,y2 �����е���ʼ�ͽ�����ַ
      ����ֵ��  ��
******************************************************************************/
void TFT_LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
	TFT_LCD_WR_REG(0x2a);//�е�ַ����
	TFT_LCD_WR_DATA(x1);
	TFT_LCD_WR_DATA(x2);
	TFT_LCD_WR_REG(0x2b);//�е�ַ����
	TFT_LCD_WR_DATA(y1);
	TFT_LCD_WR_DATA(y2);
	TFT_LCD_WR_REG(0x2c);//������д
}

/******************************************************************************
      ����˵����LCD���ڱ���
      ������ݣ�dc,ռ�ձ�,5%~100%
      ����ֵ��  ��
******************************************************************************/
void TFT_LCD_Set_Light(uint8_t dc)
{
//	if(dc>=5 && dc<=100)
//		__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_3,dc*PWM_PERIOD/100);
}

/******************************************************************************
      ����˵����LCD�رձ���
      ������ݣ���
      ����ֵ��  ��
******************************************************************************/
void LCD_Close_Light(void)
{
//	__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_3,0);
	//HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_3);
}

/******************************************************************************
      ����˵����LCD��������
      ������ݣ���
      ����ֵ��  ��
******************************************************************************/
void LCD_Open_Light(void)
{
//	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);
}

/******************************************************************************
      ����˵����ST7789 SLEEP IN
      ������ݣ���
      ����ֵ��  ��
******************************************************************************/
void TFT_LCD_ST7789_SleepIn(void)
{
	TFT_LCD_WR_REG(0x10);
	HAL_Delay(100);
}

/******************************************************************************
      ����˵����ST7789 SLEEP OUT
      ������ݣ���
      ����ֵ��  ��
******************************************************************************/
void LCD_ST7789_SleepOut(void)
{
	TFT_LCD_WR_REG(0x11);
	HAL_Delay(100);
}

/******************************************************************************
      ����˵����LCD��ʼ��
      ������ݣ���
      ����ֵ��  ��
******************************************************************************/
void TFT_LCD_Init(void)
{
    TFT_LCD_GPIO_Init();     // ��ʼ��GPIO
    TFT_LCD_CS_Clr();        // chip select

    TFT_LCD_RES_Clr();       // External reset input  LCD�����룬��Ƭ�����
    HAL_Delay(100);
    TFT_LCD_RES_Set();
    HAL_Delay(100);
    
	TFT_LCD_WR_REG(0x11); 
	HAL_Delay(120); 
	TFT_LCD_WR_REG(0x36);     
    
	if(USE_HORIZONTAL==0)TFT_LCD_WR_DATA8(0x00);
	else if(USE_HORIZONTAL==1)TFT_LCD_WR_DATA8(0xC0);
	else if(USE_HORIZONTAL==2)TFT_LCD_WR_DATA8(0x70);
	else TFT_LCD_WR_DATA8(0xA0); 

	TFT_LCD_WR_REG(0x3A);
	TFT_LCD_WR_DATA8(0x05);

	TFT_LCD_WR_REG(0xB2);
	TFT_LCD_WR_DATA8(0x0C);
	TFT_LCD_WR_DATA8(0x0C);
	TFT_LCD_WR_DATA8(0x00);
	TFT_LCD_WR_DATA8(0x33);
	TFT_LCD_WR_DATA8(0x33); 

	TFT_LCD_WR_REG(0xB7); 
	TFT_LCD_WR_DATA8(0x35);  

	TFT_LCD_WR_REG(0xBB);
	TFT_LCD_WR_DATA8(0x19);

	TFT_LCD_WR_REG(0xC0);
	TFT_LCD_WR_DATA8(0x2C);

	TFT_LCD_WR_REG(0xC2);
	TFT_LCD_WR_DATA8(0x01);

	TFT_LCD_WR_REG(0xC3);
	TFT_LCD_WR_DATA8(0x12);   

	TFT_LCD_WR_REG(0xC4);
	TFT_LCD_WR_DATA8(0x20);  

	TFT_LCD_WR_REG(0xC6); 
	TFT_LCD_WR_DATA8(0x0F);    

	TFT_LCD_WR_REG(0xD0); 
	TFT_LCD_WR_DATA8(0xA4);
	TFT_LCD_WR_DATA8(0xA1);

	TFT_LCD_WR_REG(0xE0);
	TFT_LCD_WR_DATA8(0xD0);
	TFT_LCD_WR_DATA8(0x04);
	TFT_LCD_WR_DATA8(0x0D);
	TFT_LCD_WR_DATA8(0x11);
	TFT_LCD_WR_DATA8(0x13);
	TFT_LCD_WR_DATA8(0x2B);
	TFT_LCD_WR_DATA8(0x3F);
	TFT_LCD_WR_DATA8(0x54);
	TFT_LCD_WR_DATA8(0x4C);
	TFT_LCD_WR_DATA8(0x18);
	TFT_LCD_WR_DATA8(0x0D);
	TFT_LCD_WR_DATA8(0x0B);
	TFT_LCD_WR_DATA8(0x1F);
	TFT_LCD_WR_DATA8(0x23);

	TFT_LCD_WR_REG(0xE1);
	TFT_LCD_WR_DATA8(0xD0);
	TFT_LCD_WR_DATA8(0x04);
	TFT_LCD_WR_DATA8(0x0C);
	TFT_LCD_WR_DATA8(0x11);
	TFT_LCD_WR_DATA8(0x13);
	TFT_LCD_WR_DATA8(0x2C);
	TFT_LCD_WR_DATA8(0x3F);
	TFT_LCD_WR_DATA8(0x44);
	TFT_LCD_WR_DATA8(0x51);
	TFT_LCD_WR_DATA8(0x2F);
	TFT_LCD_WR_DATA8(0x1F);
	TFT_LCD_WR_DATA8(0x1F);
	TFT_LCD_WR_DATA8(0x20);
	TFT_LCD_WR_DATA8(0x23);

	TFT_LCD_WR_REG(0x21); 

	TFT_LCD_WR_REG(0x29);     







}


























