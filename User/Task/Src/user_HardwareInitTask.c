

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

#include "CST816.h"
#include "tft_lcd_init.h"
#include "lcd.h"

#include "lvgl.h"
#include "lv_port_indev.h"
#include "lv_port_disp.h"

#include "version.h"
#include "ui.h"

//void HardwareInitTask(void *argument)
//{
//    int i = 1,j = 2,c = 3;
//    while (1)
//    {
//        vTaskSuspendAll(); // 挂起调度器,这时候要创建其它的任务，所以将任务调度器挂起，专心执行当前任务，不被其它任务打断。

//        delay_init();
//        
//        // touch
//        CST816_GPIO_Init();
//        CST816_RESET(); 

//        // lcd
//        TFT_LCD_Init();
//        LCD_Fill(0,0, LCD_W, LCD_H, BLACK);
//        delay_ms(10);
//        LCD_ShowString(72,LCD_H/2,(uint8_t*)"Welcome you", WHITE, BLACK, 24, 0);//12*6,16*8,24*12,32*16
////        uint8_t lcd_buf_str[17];
////        sprintf(lcd_buf_str, "OV-Watch V%d.%d.%d", watch_version_major(), watch_version_minor(), watch_version_patch());
//        uint8_t lcd_buf_str[17];
//        sprintf((char*)lcd_buf_str, "OV-Watch V%d.%d.%d", i, j, c);
//        LCD_ShowString(34, LCD_H/2+48, (uint8_t*)lcd_buf_str, WHITE, BLACK, 24, 0);       
//        delay_ms(1000);
//        LCD_Fill(0, LCD_H/2-24, LCD_W, LCD_H/2+49, BLACK);       
//        
//        lv_init();
//        lv_port_disp_init();
//        lv_port_indev_init();
////        ui_init();
////        Test_study_obj();
////        Test_study_swtich();
//        xTaskResumeAll();  // 
//        
//		vTaskDelete(NULL); // 该任务就是为了创建其它的任务，完成工作后就可以将其释放掉了。
//		osDelay(500);         
//    }



//}


void HardwareInitTask(void *argument)
{
	while(1)
	{
    vTaskSuspendAll(); // 挂起调度器

    // RTC Wake        
//    if(HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, 2000, RTC_WAKEUPCLOCK_RTCCLK_DIV16) != HAL_OK)
//    {
//      Error_Handler();
//    }
    // usart start
//    HAL_UART_Receive_DMA(&huart1,(uint8_t*)HardInt_receive_str,25);
//    __HAL_UART_ENABLE_IT(&huart1,UART_IT_IDLE);

    // PWM Start
//    HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);

    // sys delay
    delay_init();
    // wait
    // delay_ms(1000);

    // power
//    HWInterface.Power.Init();

//    // key
//    Key_Port_Init();

    // sensors
//    uint8_t num = 3;
//    while(num && HWInterface.AHT21.ConnectionError)
//    {
//      num--;
//      HWInterface.AHT21.ConnectionError = HWInterface.AHT21.Init();
//    }

//    num = 3;
//    while(num && HWInterface.Ecompass.ConnectionError)
//    {
//      num--;
//      HWInterface.Ecompass.ConnectionError = HWInterface.Ecompass.Init();
//    }
//    if(!HWInterface.Ecompass.ConnectionError)
//      HWInterface.Ecompass.Sleep();

//    num = 3;
//    while(num && HWInterface.Barometer.ConnectionError)
//    {
//      num--;
//      HWInterface.Barometer.ConnectionError = HWInterface.Barometer.Init();
//    }

//    num = 3;
//    while(num && HWInterface.IMU.ConnectionError)
//    {
//      num--;
//      HWInterface.IMU.ConnectionError = HWInterface.IMU.Init();
//      // Sensor_MPU_Erro = MPU_Init();
//    }

//    num = 3;
//    while(num && HWInterface.HR_meter.ConnectionError)
//    {
//      num--;
//      HWInterface.HR_meter.ConnectionError = HWInterface.HR_meter.Init();
//    }
//    if(!HWInterface.HR_meter.ConnectionError)
//      HWInterface.HR_meter.Sleep();


    // EEPROM
//    EEPROM_Init();
//    if(!EEPROM_Check())
//    {
//      uint8_t recbuf[3];
//      SettingGet(recbuf,0x10,2);
//      if((recbuf[0]!=0 && recbuf[0]!=1) || (recbuf[1]!=0 && recbuf[1]!=1))
//      {
//        HWInterface.IMU.wrist_is_enabled = 0;
//        ui_APPSy_EN = 0;
//      }
//      else
//      {
//        HWInterface.IMU.wrist_is_enabled = recbuf[0];
//        ui_APPSy_EN = recbuf[1];
//      }

//      RTC_DateTypeDef nowdate;
//      HAL_RTC_GetDate(&hrtc,&nowdate,RTC_FORMAT_BIN);

//      SettingGet(recbuf,0x20,3);
//      if(recbuf[0] == nowdate.Date)
//      {
//        uint16_t steps=0;
//        steps = recbuf[1]&0x00ff;
//        steps = steps<<8 | recbuf[2];
//        if(!HWInterface.IMU.ConnectionError)
//          dmp_set_pedometer_step_count((unsigned long)steps);
//      }
//    }


//    // BLE
//    KT6328_GPIO_Init();
//    KT6328_Disable();

    //set the KT6328 BautRate 9600
    //default is 115200
    //printf("AT+CT01\r\n");

    // touch
    CST816_GPIO_Init();
    CST816_RESET();

    // lcd
    TFT_LCD_Init();
    LCD_Fill(0,0, LCD_W, LCD_H, BLACK);
    delay_ms(10);
//    LCD_Set_Light(50);
    LCD_ShowString(72,LCD_H/2,(uint8_t*)"Welcome!", WHITE, BLACK, 24, 0);//12*6,16*8,24*12,32*16
    uint8_t lcd_buf_str[17];
    sprintf(lcd_buf_str, "OV-Watch V%d.%d.%d", watch_version_major(), watch_version_minor(), watch_version_patch());
    LCD_ShowString(34, LCD_H/2+48, (uint8_t*)lcd_buf_str, WHITE, BLACK, 24, 0);
    delay_ms(1000);
    LCD_Fill(0, LCD_H/2-24, LCD_W, LCD_H/2+49, BLACK);


    // ui
    // LVGL init
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();
//    ui_init();
//    {
//        lv_obj_t * sw = lv_switch_create(lv_scr_act());
//        lv_obj_center(sw);    
//    
//    }

    
    xTaskResumeAll();
		vTaskDelete(NULL);
		osDelay(500);
	}
}

















