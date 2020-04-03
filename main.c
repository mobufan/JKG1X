/*************** (C) COPYRIGHT  �������� *************************************
 * �ļ���  ��main.c
 * ����    ���޹�����������
 * ʵ��ƽ̨��JKGX1
 * ��汾  ��V2.1.0
 * ����    ��Ī��  QQ��29577332
 * ����    ��
 * �޸�ʱ�� ��2019-03-30
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "main.h"

/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* ȫ�ֱ������� */


SRAM    SM;     // �����ļ�
DRAM    DM;     // ����Ҫ��ʼ���ģ����ʼ��Ϊ0�ı���
unsigned char ReloadIWdog;  // ��ֵ������0x55 �� 0xAA,֮��仯,�������ֻ�����λ


//    uint8_t Run;                  // �������б�־: 0 ������ 1����
//    uint8_t Stop;                 // ����رձ�־: 0 ���� 1 �ر�
//    uint16_t Timer;                // ��ʱ�� ֻ�Ǽ�ʱ�������Ը�һ����ֵ����ֵ��������������ʱ��
//    uint16_t ItvTime;              // ������ʱ��
//    void (*TaskHook)(void);     // ��Ҫ���е�������
//���������С������Ϊ10ms
TASK_COMPONENTS TaskComps[TASK_MAX] =
{
    {0,0,70,10,Start_Ad_Task},           // ��ʼad����
    {0,0,70,5,Compute_Task},             // ��ʼ����
    {0,0,10,100,Config_Task},            // ���ݶ���Բ������,�����ݼ������ж�����״̬
    {0,0,4,100,Key_Task},                 // �����ɼ��ʹ���     
    {0,0,6,100,Cap_Task},                 // ����״̬��ad������ж����ݵ�Ͷ�в�ִ��
//    {0,0,8,10,IWDG_ReloadCounter},     // ι��
//    {0,0,8,10,RunTestLed_Task},          // ���в��Ե�
};


/*******************************************************************************
 * ����: TaskProcess
 * ����: ������
 * �β�: ��
 * ����: ��
 * ˵��: 1 ��˳���������ʱѭ��������
 ******************************************************************************/
void TaskProcess(void)
{
    static uint8_t  i;                        // ע�� i����Ϊ��̬,�������� iʼ��Ϊ0
    for(i=0; i<TASK_MAX; i++)               // ���������
    {
        if(TaskComps[i].Run)                // ��������
        {
            TaskComps[i].TaskHook();        // ��������
            TaskComps[i].Run = FALSE;       // ��־���� 
        }
    }
}

/*******************************************************************************
 * ����: TaskRemarks
 * ����: �����־����
 * �β�: ��
 * ����: ��
 * ˵��: 1 ר�Ŵ�������ı�־λ
         2 ������ ÿ��ʱ�����ִ��1��
 ******************************************************************************/
void TaskRemarks(void)
{
    static INT8U i;
    for(i=0;i<TASK_MAX;i++)                 // ���������
    {
        if((TaskComps[i].Timer)&&(FALSE == TaskComps[i].Stop))              // ʱ�䲻Ϊ0,������û�йر�
        {
            TaskComps[i].Timer--;           // ��ȥһ������
            if(0 == TaskComps[i].Timer)     // ʱ�������
            {
                TaskComps[i].Timer = TaskComps[i].ItvTime;            // �ָ���ʱ��ֵ ������һ��
                TaskComps[i].Run = TRUE;    // �����������
            }
        }
    }
}


/*******************************************************************************
 * ����: Init_SysData
 * ����: ��ʼ��sm ����
 * �β�: ��
 * ����: ��
 * ˵��: 1
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
    /* �����ڲ�8M����Ϊϵͳʱ�� 1 */
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
    DM.sStateSet.cAutoState = AUTOSTATE;    // Ĭ���Զ�
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
            if((DM.cSysFlg & F_FlashNew) && (DM.sDspCtr.PagePtr == 0x1001))         // ֻ��������ʾ�˵���ʱ����
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

/*************** (C) COPYRIGHT ������������������޹�˾ *****END OF FILE****/
