/*************** (C) COPYRIGHT  杭州中深 *************************************
 * 文件名  ：main.c
 * 描述    ：无功补偿控制器
 * 实验平台：JKGX1
 * 库版本  ：V2.1.0
 * 作者    ：莫易  QQ：29577332
 * 博客    ：
 * 修改时间 ：2019-03-30
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "main.h"

/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* 全局变量定义 */


SRAM    SM;     // 配置文件
DRAM    DM;     // 不需要初始化的，或初始化为0的变量
unsigned char ReloadIWdog;  // 数值必须在0x55 和 0xAA,之间变化,其他数字会引起复位


//    uint8_t Run;                  // 任务运行标志: 0 不运行 1运行
//    uint8_t Stop;                 // 任务关闭标志: 0 正常 1 关闭
//    uint16_t Timer;                // 计时器 只是计时器，可以赋一个初值，初值用来避免启动的时间
//    uint16_t ItvTime;              // 任务间隔时间
//    void (*TaskHook)(void);     // 需要运行的任务函数
//本程序的最小任务间隔为10ms
TASK_COMPONENTS TaskComps[TASK_MAX] =
{
    {0,0,70,10,Start_Ad_Task},           // 开始ad采样
    {0,0,70,5,Compute_Task},             // 开始计算
    {0,0,10,100,Config_Task},            // 根据定义对参数填充,并根据计算结果判定各种状态
    {0,0,4,100,Key_Task},                 // 按键采集和处理     
    {0,0,6,100,Cap_Task},                 // 根据状态和ad结果，判定电容的投切并执行
//    {0,0,8,10,IWDG_ReloadCounter},     // 喂狗
//    {0,0,8,10,RunTestLed_Task},          // 运行测试灯
};


/*******************************************************************************
 * 名称: TaskProcess
 * 功能: 任务处理
 * 形参: 无
 * 返回: 无
 * 说明: 1 按顺序处理各个定时循环的任务
 ******************************************************************************/
void TaskProcess(void)
{
    static uint8_t  i;                        // 注意 i必须为静态,否则会造成 i始终为0
    for(i=0; i<TASK_MAX; i++)               // 逐个任务处理
    {
        if(TaskComps[i].Run)                // 可以运行
        {
            TaskComps[i].TaskHook();        // 运行任务
            TaskComps[i].Run = FALSE;       // 标志清理 
        }
    }
}

/*******************************************************************************
 * 名称: TaskRemarks
 * 功能: 任务标志处理
 * 形参: 无
 * 返回: 无
 * 说明: 1 专门处理任务的标志位
         2 本函数 每个时间颗粒执行1次
 ******************************************************************************/
void TaskRemarks(void)
{
    static INT8U i;
    for(i=0;i<TASK_MAX;i++)                 // 逐个任务处理
    {
        if((TaskComps[i].Timer)&&(FALSE == TaskComps[i].Stop))              // 时间不为0,且任务没有关闭
        {
            TaskComps[i].Timer--;           // 减去一个节拍
            if(0 == TaskComps[i].Timer)     // 时间减完了
            {
                TaskComps[i].Timer = TaskComps[i].ItvTime;            // 恢复计时器值 从新下一次
                TaskComps[i].Run = TRUE;    // 任务可以运行
            }
        }
    }
}


/*******************************************************************************
 * 名称: Init_SysData
 * 功能: 初始化sm 参数
 * 形参: 无
 * 返回: 无
 * 说明: 1
 ******************************************************************************/
void Init_SysData(void)
{
    unsigned char i;
    unsigned char *pSM;
    unsigned int addr = 0x4000;
    if(TRUE == CheckSysEePara())
    {
        pSM = (unsigned char *)&SM.sConfig;
        for(i = 0; i < sizeof(SM.sConfig); i++)
        {
            *pSM = FLASH_ReadByte(addr);
            addr++;
            pSM++;
        }
    }
    else
    {
        SM.sConfig.c3CupNumber = 10;
        SM.sConfig.cCupDelayTime = 20;
        SM.sConfig.cLowILimit = 2;
        SM.sConfig.cPfLimit = 95;
        SM.sConfig.wOverVoltage = 20;
        SM.sConfig.XiaoZun1 = 400;
        SM.sConfig.XiaoZun2 = 630;
        SM.sConfig.XiaoZun3 = 80;

        DM.cSysFlg |= F_FlashNew;
    }
}



void main(void)
{
    /* 设置内部8M晶振为系统时钟 1 */
    SystemClock_Init(HSI_Clock);
//    IWDG_Conf();	
    NullIO_Init();
    Tim1_Init();
    Init_SysData();
    ADC_Init();
    AssistMod_Init();
    
    ReloadIWdog = 0x55;
    enableInterrupts();

    #ifdef debugled
    DM.sElecPara.Cos = 97;
    #endif
    
    DM.sDspCtr.PagePtr = 0x1001;
    DM.sStateSet.cAutoState = AUTOSTATE;    // 默认自动
    delay_ms(100);

    Selfdetect();
    AutoAdjust();
   
    while (1)
    {
        TaskProcess();
        if(ReloadIWdog == 0x55)
        {
//            IWDG_ReloadCounter();
            ReloadIWdog = 0xAA;
        }
        if(DM.sRelayTime.cSecChange)
        {
            DM.sRelayTime.cSecChange = 0;
            if((DM.cSysFlg & F_FlashNew) && (DM.sDspCtr.PagePtr == 0x1001))         // 只有在主显示菜单的时候处理
            {
                disableInterrupts();
                SaveFlash();
//                IWDG_Conf();
                DM.cSysFlg &= (~F_FlashNew);                
                enableInterrupts();
//                IWDG_ReloadCounter();
            }
        }
    }
}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(u8 *file, u32 line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}
#endif

/*************** (C) COPYRIGHT 杭州中深电力技术有限公司 *****END OF FILE****/
