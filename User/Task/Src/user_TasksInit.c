#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

#include "user_HardwareInitTask.h"

#include "lvgl.h"

#include "ui.h"
#include "CST816.h"

// Hardwares initialization
osThreadId_t HardwareInitTaskHandle;
const osThreadAttr_t HardwareInitTask_attributes = {
  .name = "HardwareInitTask",
  .stack_size = 128 * 10,
  .priority = (osPriority_t) osPriorityHigh3,  // 所有任务中的最高优先级，因为它要初始化创建其它的任务
};

// lvgl initialization
osThreadId_t LvHandlerTaskHandle;
const osThreadAttr_t LvHandlerTask_attributes = {
  .name = "LvHandlerTask",
  .stack_size = 128 * 24,
  .priority = (osPriority_t) osPriorityLow,  // 
};

//WDOG Feed task
osThreadId_t WDOGFeedTaskHandle;
const osThreadAttr_t WDOGFeedTask_attributes = {
  .name = "WDOGFeedTask",
  .stack_size = 128 * 1,
  .priority = (osPriority_t) osPriorityHigh2,
};



osThreadId_t LVGLStudyTaskHandle;
const osThreadAttr_t TestStudyLVGLTask_attributes = {
  .name = "TestStudyLVGLTask",
  .stack_size = 128 * 10,
  .priority = (osPriority_t) osPriorityLow1,
};







/* Message queues ------------------------------------------------------------*/
//Key message
osMessageQueueId_t Key_MessageQueue;
osMessageQueueId_t Idle_MessageQueue;
osMessageQueueId_t Stop_MessageQueue;
osMessageQueueId_t IdleBreak_MessageQueue;
osMessageQueueId_t HomeUpdata_MessageQueue;
osMessageQueueId_t DataSave_MessageQueue;





void WDOGFeedTask(void *argument);


/**
  * @brief  LVGL Handler task, to run the lvgl
  * @param  argument: Not used
  * @retval None
  */
void LvHandlerTask(void *argument)
{
//	uint8_t IdleBreakstr=0;
    while(1)
    {
        /*
        函数用于获取当前未活动的显示器的非活动时间。这个时间
        通常用于判断一个显示器是否在一定时间内没有被使用或交互，
        从而可以用于实现自动休眠或省电功能。        
        */
//		if(lv_disp_get_inactive_time(NULL)<1000)
//		{
			//Idle time break, set to 0
//			osMessageQueuePut(IdleBreak_MessageQueue, &IdleBreakstr, 0, 0);
//		}
//        Test_study_swtich();
        lv_task_handler();
        osDelay(1);
    }
}


void TestStudyLVGLTask(void *argument)
{
    static char myflag = 0;
    while(1)
    {
        if (myflag == 0)
        {
            myflag = 1;  
//            Test_study_swtich();
            Test_study_checkbox();
        }
        osDelay(2000);
    }
}



void vUser_Tasks_Init(void)
{
    
    /* add queues */
	Key_MessageQueue  = osMessageQueueNew(1, 1, NULL);// 按键消息队列，长度1 ，大小1
	Idle_MessageQueue = osMessageQueueNew(1, 1, NULL);// 空闲消息队列，长度1 ，大小1
	Stop_MessageQueue = osMessageQueueNew(1, 1, NULL);// 停止消息队列，长度1 ，大小1
	IdleBreak_MessageQueue = osMessageQueueNew(1, 1, NULL);// 空闲中断消息队列，长度1 ，大小1
	HomeUpdata_MessageQueue = osMessageQueueNew(1, 1, NULL);// 主页面更新消息队列，长度1 ，大小1
	DataSave_MessageQueue = osMessageQueueNew(2, 1, NULL);// 数据保存消息队列，长度2 ，大小1    
    
    /*add threads*/
    /*HardwareInitTaskHandle 硬件任务初始化，包含RTC，串口，各种传感器，蓝牙等等*/
    HardwareInitTaskHandle  = osThreadNew(HardwareInitTask, NULL, &HardwareInitTask_attributes);
    
    /*LCD屏幕刷新函数*/
    LvHandlerTaskHandle     = osThreadNew(LvHandlerTask, NULL, &LvHandlerTask_attributes);
    
    /*看门狗喂食函数*/
//    WDOGFeedTaskHandle   = osThreadNew(WDOGFeedTask, NULL, &WDOGFeedTask_attributes);
    
    LVGLStudyTaskHandle   = osThreadNew(TestStudyLVGLTask, NULL, &TestStudyLVGLTask_attributes);
    
    // 空闲任务
//	IdleEnterTaskHandle  = osThreadNew(IdleEnterTask, NULL, &IdleEnterTask_attributes);
    // 待机任务
//	StopEnterTaskHandle  = osThreadNew(StopEnterTask, NULL, &StopEnterTask_attributes);
    // 按键
//	KeyTaskHandle 			 = osThreadNew(KeyTask, NULL, &KeyTask_attributes);
    // 屏幕
//	ScrRenewTaskHandle   = osThreadNew(ScrRenewTask, NULL, &ScrRenewTask_attributes);    
}




















void vTickTaskHook(void)
{
    lv_tick_inc(1);
}







void WDOGFeedTask(void *argument)
{
	//owdg
//	WDOG_Port_Init();
  while(1)
  {
//		WDOG_Feed();
//		WDOG_Enable();
    osDelay(100);
  }
}












