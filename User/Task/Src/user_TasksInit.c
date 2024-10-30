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
  .priority = (osPriority_t) osPriorityHigh3,  // ���������е�������ȼ�����Ϊ��Ҫ��ʼ����������������
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
        �������ڻ�ȡ��ǰδ�����ʾ���ķǻʱ�䡣���ʱ��
        ͨ�������ж�һ����ʾ���Ƿ���һ��ʱ����û�б�ʹ�û򽻻���
        �Ӷ���������ʵ���Զ����߻�ʡ�繦�ܡ�        
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
	Key_MessageQueue  = osMessageQueueNew(1, 1, NULL);// ������Ϣ���У�����1 ����С1
	Idle_MessageQueue = osMessageQueueNew(1, 1, NULL);// ������Ϣ���У�����1 ����С1
	Stop_MessageQueue = osMessageQueueNew(1, 1, NULL);// ֹͣ��Ϣ���У�����1 ����С1
	IdleBreak_MessageQueue = osMessageQueueNew(1, 1, NULL);// �����ж���Ϣ���У�����1 ����С1
	HomeUpdata_MessageQueue = osMessageQueueNew(1, 1, NULL);// ��ҳ�������Ϣ���У�����1 ����С1
	DataSave_MessageQueue = osMessageQueueNew(2, 1, NULL);// ���ݱ�����Ϣ���У�����2 ����С1    
    
    /*add threads*/
    /*HardwareInitTaskHandle Ӳ�������ʼ��������RTC�����ڣ����ִ������������ȵ�*/
    HardwareInitTaskHandle  = osThreadNew(HardwareInitTask, NULL, &HardwareInitTask_attributes);
    
    /*LCD��Ļˢ�º���*/
    LvHandlerTaskHandle     = osThreadNew(LvHandlerTask, NULL, &LvHandlerTask_attributes);
    
    /*���Ź�ιʳ����*/
//    WDOGFeedTaskHandle   = osThreadNew(WDOGFeedTask, NULL, &WDOGFeedTask_attributes);
    
    LVGLStudyTaskHandle   = osThreadNew(TestStudyLVGLTask, NULL, &TestStudyLVGLTask_attributes);
    
    // ��������
//	IdleEnterTaskHandle  = osThreadNew(IdleEnterTask, NULL, &IdleEnterTask_attributes);
    // ��������
//	StopEnterTaskHandle  = osThreadNew(StopEnterTask, NULL, &StopEnterTask_attributes);
    // ����
//	KeyTaskHandle 			 = osThreadNew(KeyTask, NULL, &KeyTask_attributes);
    // ��Ļ
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












